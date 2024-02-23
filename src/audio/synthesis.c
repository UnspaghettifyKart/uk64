#include <ultra64.h>
#include <macros.h>
#include "audio/synthesis.h"
#include "audio/heap.h"
#include "audio/data.h"
#include "audio/load.h"
#include "audio/seqplayer.h"
#include "audio/internal.h"
//#include "audio/external.h"
#include "PR/abi.h"

#define aSetLoadBufferPair(pkt, c, off)                                                                \
    aSetBuffer(pkt, 0, c + DMEM_ADDR_WET_LEFT_CH, 0, DEFAULT_LEN_1CH - c);                             \
    aLoadBuffer(pkt, VIRTUAL_TO_PHYSICAL2(gSynthesisReverb.ringBuffer.left + (off)));                  \
    aSetBuffer(pkt, 0, c + DMEM_ADDR_WET_RIGHT_CH, 0, DEFAULT_LEN_1CH - c);                            \
    aLoadBuffer(pkt, VIRTUAL_TO_PHYSICAL2(gSynthesisReverb.ringBuffer.right + (off)))

#define aSetSaveBufferPair(pkt, c, d, off)                                                             \
    aSetBuffer(pkt, 0, 0, c + DMEM_ADDR_WET_LEFT_CH, d);                                               \
    aSaveBuffer(pkt, VIRTUAL_TO_PHYSICAL2(gSynthesisReverb.ringBuffer.left +  (off)));                 \
    aSetBuffer(pkt, 0, 0, c + DMEM_ADDR_WET_RIGHT_CH, d);                                              \
    aSaveBuffer(pkt, VIRTUAL_TO_PHYSICAL2(gSynthesisReverb.ringBuffer.right + (off)));

struct VolumeChange {
    u16 sourceLeft;
    u16 sourceRight;
    u16 targetLeft;
    u16 targetRight;
};

u64 *process_envelope(u64 *cmd, struct NoteSubEu *noteSubEu, struct NoteSynthesisState *synthesisState, s32 nSamples, u16 inBuf, s32 headsetPanSettings, u32 flags);

struct SynthesisReverb gSynthesisReverbs[4];
u8 sAudioSynthesisPad[0x10];

// s16 gVolume;
// s8 gUseReverb;
// s8 gNumSynthesisReverbs;
// struct NoteSubEu *gNoteSubsEu;

//f32 gLeftVolRampings;
//f32 gRightVolRampings[3][1024];
//f32 *gCurrentLeftVolRamping; // Points to any of the three left buffers above
//f32 *gCurrentRightVolRamping; // Points to any of the three right buffers above

/**
 * Given that (almost) all of these are format strings, it is highly likely
 * that they are meant to be used in some sort of printf variant. But I don't
 * care to try and figure out which function gets which string(s)
 * So I've place them all here instead.
**/
char synthesisAudioString0[] = "Terminate-Canceled Channel %d,Phase %d\n";
char synthesisAudioString1[] = "Copy %d\n";
char synthesisAudioString2[] = "%d->%d\n";
char synthesisAudioString3[] = "pitch %x: delaybytes %d : olddelay %d\n";
char synthesisAudioString4[] = "cont %x: delaybytes %d : olddelay %d\n";

// Equivalent functionality as the US/JP version,
// just that the reverb structure is chosen from an array with index
void prepare_reverb_ring_buffer(s32 chunkLen, u32 updateIndex, s32 reverbIndex) {
    struct ReverbRingBufferItem *item;
    struct SynthesisReverb *reverb = &gSynthesisReverbs[reverbIndex];
    s32 srcPos;
    s32 dstPos;
    s32 nSamples;
    s32 excessiveSamples;
    s32 UNUSED pad[3];
    if (reverb->downsampleRate != 1) {
        if (reverb->framesLeftToIgnore == 0) {
            // Now that the RSP has finished, downsample the samples produced two frames ago by skipping
            // samples.
            item = &reverb->items[reverb->curFrame][updateIndex];

            // Touches both left and right since they are adjacent in memory
            osInvalDCache(item->toDownsampleLeft, 0x300);

            for (srcPos = 0, dstPos = 0; dstPos < item->lengthA / 2;
                 srcPos += reverb->downsampleRate, dstPos++) {
                reverb->ringBuffer.left[item->startPos + dstPos] =
                    item->toDownsampleLeft[srcPos];
                reverb->ringBuffer.right[item->startPos + dstPos] =
                    item->toDownsampleRight[srcPos];
            }
            for (dstPos = 0; dstPos < item->lengthB / 2; srcPos += reverb->downsampleRate, dstPos++) {
                reverb->ringBuffer.left[dstPos] = item->toDownsampleLeft[srcPos];
                reverb->ringBuffer.right[dstPos] = item->toDownsampleRight[srcPos];
            }
        }
    }

    item = &reverb->items[reverb->curFrame][updateIndex];
    nSamples = chunkLen / reverb->downsampleRate;
    excessiveSamples = (nSamples + reverb->nextRingBufferPos) - reverb->bufSizePerChannel;
    if (excessiveSamples < 0) {
        // There is space in the ring buffer before it wraps around
        item->lengthA = nSamples * 2;
        item->lengthB = 0;
        item->startPos = (s32) reverb->nextRingBufferPos;
        reverb->nextRingBufferPos += nSamples;
    } else {
        // Ring buffer wrapped around
        item->lengthA = (nSamples - excessiveSamples) * 2;
        item->lengthB = excessiveSamples * 2;
        item->startPos = reverb->nextRingBufferPos;
        reverb->nextRingBufferPos = excessiveSamples;
    }
    // These fields are never read later
    item->numSamplesAfterDownsampling = nSamples;
    item->chunkLen = chunkLen;
}


Acmd *synthesis_load_reverb_ring_buffer(Acmd *acmd, u16 addr, u16 srcOffset, s32 len, s32 reverbIndex) {
    aLoadBuffer(acmd++, VIRTUAL_TO_PHYSICAL2(&gSynthesisReverbs[reverbIndex].ringBuffer.left[srcOffset]), addr, len);
    aLoadBuffer(acmd++, VIRTUAL_TO_PHYSICAL2(&gSynthesisReverbs[reverbIndex].ringBuffer.right[srcOffset]), addr + 0x180, len);
    return acmd;
}

Acmd *synthesis_save_reverb_ring_buffer(Acmd *acmd, u16 addr, u16 destOffset, s32 len, s32 reverbIndex) {
    aSaveBuffer(acmd++, addr, VIRTUAL_TO_PHYSICAL2(&gSynthesisReverbs[reverbIndex].ringBuffer.left[destOffset]), len);
    aSaveBuffer(acmd++, addr + 0x180, VIRTUAL_TO_PHYSICAL2(&gSynthesisReverbs[reverbIndex].ringBuffer.right[destOffset]), len);
    return acmd;
}

void func_800B6FB4(s32 updateIndexStart, s32 noteIndex) {
    s32 i;

    for (i = updateIndexStart + 1; i < gAudioBufferParameters.updatesPerFrame; i++) {
        if (!gNoteSubsEu[gMaxSimultaneousNotes * i + noteIndex].needsInit) {
            gNoteSubsEu[gMaxSimultaneousNotes * i + noteIndex].enabled = FALSE;
        } else {
            break;
        }
    }
}

void synthesis_load_note_subs_eu(s32 updateIndex) {
    struct NoteSubEu *src;
    struct NoteSubEu *dest;
    s32 i;

    for (i = 0; i < gMaxSimultaneousNotes; i++) {
        src = &gNotes[i].noteSubEu;
        dest = &gNoteSubsEu[gMaxSimultaneousNotes * updateIndex + i];
        if (src->enabled) {
            *dest = *src;
            src->needsInit = FALSE;
        } else {
            dest->enabled = FALSE;
        }
    }
}

Acmd *synthesis_execute(Acmd *acmd, s32 *writtenCmds, s16 *aiBuf, s32 bufLen) {
    s32 i, j;
    u32 *aiBufPtr;
    Acmd *cmd = acmd;
    s32 chunkLen;

    for (i = gAudioBufferParameters.updatesPerFrame; i > 0; i--) {
        process_sequences(i - 1);
        synthesis_load_note_subs_eu(gAudioBufferParameters.updatesPerFrame - i);
    }
    aSegment(cmd++, 0, 0);
    aiBufPtr = (u32 *) aiBuf;
    for (i = gAudioBufferParameters.updatesPerFrame; i > 0; i--) {
        if (i == 1) {
            chunkLen = bufLen;
        } else {
            if (bufLen / i >= gAudioBufferParameters.samplesPerUpdateMax) {
                chunkLen = gAudioBufferParameters.samplesPerUpdateMax;
            } else if (bufLen / i <= gAudioBufferParameters.samplesPerUpdateMin) {
                chunkLen = gAudioBufferParameters.samplesPerUpdateMin;
            } else {
                chunkLen = gAudioBufferParameters.samplesPerUpdate;
            }
        }
        for (j = 0; j < gNumSynthesisReverbs; j++) {
            if (gSynthesisReverbs[j].useReverb != 0) {
                prepare_reverb_ring_buffer(chunkLen, gAudioBufferParameters.updatesPerFrame - i, j);
            }
        }
        cmd = synthesis_do_one_audio_update((s16 *) aiBufPtr, chunkLen, cmd, gAudioBufferParameters.updatesPerFrame - i);
        bufLen -= chunkLen;
        aiBufPtr += chunkLen;
    }

    for (j = 0; j < gNumSynthesisReverbs; j++) {
        if (gSynthesisReverbs[j].framesLeftToIgnore != 0) {
            gSynthesisReverbs[j].framesLeftToIgnore--;
        }
        gSynthesisReverbs[j].curFrame ^= 1;
    }
    *writtenCmds = cmd - acmd;
    return cmd;
}

Acmd *synthesis_resample_and_mix_reverb(Acmd *acmd, s32 bufLen, s16 reverbIndex, s16 updateIndex) {
    struct ReverbRingBufferItem *item;
    s16 startPad;
    s16 paddedLengthA;

    item = &gSynthesisReverbs[reverbIndex].items[gSynthesisReverbs[reverbIndex].curFrame][updateIndex];
    aClearBuffer(acmd++, 0x840, 0x300);
    if (gSynthesisReverbs[reverbIndex].downsampleRate == 1) {

        acmd = synthesis_load_reverb_ring_buffer(acmd, 0x840, item->startPos, item->lengthA, reverbIndex);
        if (item->lengthB != 0) {
            acmd = synthesis_load_reverb_ring_buffer(acmd, item->lengthA + 0x840, 0U, item->lengthB, reverbIndex);
        }

        aMix(acmd++, 0x7fff, 0x840, 0x540, 0x300);
        aMix(acmd++, 0x8000 + gSynthesisReverbs[reverbIndex].reverbGain, 0x840, 0x840, 0x300);
    } else {
        startPad = (item->startPos % 8U) * 2;
        paddedLengthA = ALIGN(startPad + item->lengthA, 4);

        acmd = synthesis_load_reverb_ring_buffer(acmd, 0x0020, item->startPos - (startPad / 2), 0x00000180, reverbIndex);
        if (item->lengthB != 0) {
            acmd = synthesis_load_reverb_ring_buffer(acmd, paddedLengthA + 0x20, 0, 0x180 - paddedLengthA, reverbIndex);
        }

        aSetBuffer(acmd++, 0, 0x20 + startPad, 0x840, bufLen * 2);
        aResample(acmd++, gSynthesisReverbs[reverbIndex].resampleFlags, gSynthesisReverbs[reverbIndex].resampleRate, VIRTUAL_TO_PHYSICAL2(gSynthesisReverbs[reverbIndex].resampleStateLeft));
        aSetBuffer(acmd++, 0, 0x1A0 + startPad, 0x9C0, bufLen * 2);
        aResample(acmd++, gSynthesisReverbs[reverbIndex].resampleFlags, gSynthesisReverbs[reverbIndex].resampleRate, VIRTUAL_TO_PHYSICAL2(gSynthesisReverbs[reverbIndex].resampleStateRight));
        aMix(acmd++, 0x7fff, 0x840, 0x540, 0x300);
        aMix(acmd++, 0x8000 + gSynthesisReverbs[reverbIndex].reverbGain, 0x840, 0x840, 0x300);
    }
    return acmd;
}

Acmd *synthesis_save_reverb_samples(Acmd *acmd, s16 reverbIndex, s16 updateIndex) {
    struct ReverbRingBufferItem *item;

    item = &gSynthesisReverbs[reverbIndex].items[gSynthesisReverbs[reverbIndex].curFrame][updateIndex];
    if (gSynthesisReverbs[reverbIndex].useReverb != 0) {
        switch (gSynthesisReverbs[reverbIndex].downsampleRate) {
            case 1:
                acmd = synthesis_save_reverb_ring_buffer(acmd, 0x840, item->startPos, item->lengthA, reverbIndex);
                if (item->lengthB != 0) {
                    acmd = synthesis_save_reverb_ring_buffer(acmd, 0x840 + item->lengthA, 0, item->lengthB, reverbIndex);
                }
                break;
            default:
                aSaveBuffer(acmd++, 0x840, VIRTUAL_TO_PHYSICAL2(gSynthesisReverbs[reverbIndex].items[gSynthesisReverbs[reverbIndex].curFrame][updateIndex].toDownsampleLeft), 0x300);
                gSynthesisReverbs[reverbIndex].resampleFlags = 0;
                break;
        }
    }
    return acmd;
}

Acmd *synthesis_do_one_audio_update(s16 *aiBuf, s32 bufLen, Acmd *acmd, s32 updateIndex) {
    struct NoteSubEu *noteSubEu;
    u8 noteIndices[56];
    s32 temp;
    s32 i;
    s16 j;
    s16 notePos = 0;

    if (gNumSynthesisReverbs == 0) {
        for (i = 0; i < gMaxSimultaneousNotes; i++) {
            if (gNoteSubsEu[gMaxSimultaneousNotes * updateIndex + i].enabled) {
                noteIndices[notePos++] = i;
            }
        }
    } else {
        for (j = 0; j < gNumSynthesisReverbs; j++) {
            for (i = 0; i < gMaxSimultaneousNotes; i++) {
                noteSubEu = &gNoteSubsEu[gMaxSimultaneousNotes * updateIndex + i];
                if (noteSubEu->enabled && j == noteSubEu->reverbIndex) {
                    noteIndices[notePos++] = i;
                }
            }
        }

        for (i = 0; i < gMaxSimultaneousNotes; i++) {
            noteSubEu = &gNoteSubsEu[gMaxSimultaneousNotes * updateIndex + i];
            if (noteSubEu->enabled && noteSubEu->reverbIndex >= gNumSynthesisReverbs) {
                noteIndices[notePos++] = i;
            }
        }
    }
    aClearBuffer(acmd++, DMEM_ADDR_LEFT_CH, DEFAULT_LEN_2CH);
    i = 0;
    for (j = 0; j < gNumSynthesisReverbs; j++) {
        gUseReverb = gSynthesisReverbs[j].useReverb;
        if (gUseReverb != 0) {
            acmd = synthesis_resample_and_mix_reverb(acmd, bufLen, j, updateIndex);
        }
        for (; i < notePos; i++) {
            temp = updateIndex * gMaxSimultaneousNotes;
            if (j == gNoteSubsEu[temp + noteIndices[i]].reverbIndex) {
                acmd = synthesis_process_note(noteIndices[i],
                                     &gNoteSubsEu[temp + noteIndices[i]],
                                     &gNotes[noteIndices[i]].synthesisState,
                                     aiBuf, bufLen, acmd, updateIndex);
                continue;
            } else {
                break;
            }
        }
        if (gSynthesisReverbs[j].useReverb != 0) {
            acmd = synthesis_save_reverb_samples(acmd, j, updateIndex);
        }
    }
    for (; i < notePos; i++) {
        temp = updateIndex * gMaxSimultaneousNotes;
        if (IS_BANK_LOAD_COMPLETE(gNoteSubsEu[temp + noteIndices[i]].bankId) == TRUE) {
            acmd = synthesis_process_note(noteIndices[i],
                                 &gNoteSubsEu[temp + noteIndices[i]],
                                 &gNotes[noteIndices[i]].synthesisState,
                                 aiBuf, bufLen, acmd, updateIndex);
        } else {
            gAudioErrorFlags = (gNoteSubsEu[temp + noteIndices[i]].bankId + (i << 8)) + 0x10000000;
        }
    }

    temp = bufLen * 2;
    aSetBuffer(acmd++, 0, 0, DMEM_ADDR_TEMP, temp);
    aInterleave(acmd++, DMEM_ADDR_LEFT_CH, DMEM_ADDR_RIGHT_CH);
    aSaveBuffer(acmd++, DMEM_ADDR_TEMP, VIRTUAL_TO_PHYSICAL2(aiBuf), temp * 2);
    return acmd;
}

#ifdef MIPS_TO_C
//generated by m2c commit beb457dabfc7a01ec6540a5404a6a05097a13602 on Nov-01-2023
Acmd *synthesis_process_note(s32 noteIndex, struct NoteSubEu *noteSubEu, struct NoteSynthesisState *synthesisState, s16 *aiBuf, s32 bufLen, Acmd *acmd, s32 updateIndex) {
    void *sp130;
    void *sp12C;
    s32 *sp128;
    s32 sp11C;
    s32 sp118;
    s32 sp114;                                      /* compiler-managed */
    u16 sp112;
    s32 spFC;
    s32 spEC;
    u32 spE4;
    s32 spDC;
    s32 spD8;
    s32 spB0;
    s32 spAC;
    s32 spA0;                                       /* compiler-managed */
    u16 sp9E;
    struct Note *sp8C;
    u32 sp50;
    Acmd *temp_a0_2;
    Acmd *temp_s2;
    Acmd *temp_s2_2;
    Acmd *temp_s2_3;
    Acmd *temp_v0_2;
    Acmd *temp_v0_3;
    Acmd *temp_v0_4;
    Acmd *temp_v0_5;
    Acmd *temp_v0_6;
    Acmd *temp_v0_8;
    Acmd *var_s2;
    Acmd *var_s2_2;
    s16 var_t1;
    s32 *temp_a2_2;
    s32 temp_a0;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t9_2;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_fp;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_t0;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_v1;
    u16 temp_t7;
    u16 temp_v0;
    u32 temp_a1_3;
    u32 temp_s0;
    u32 temp_t7_3;
    u32 var_s0;
    u32 var_t5;
    u32 var_t6;
    u32 var_v1_2;
    u32 var_v1_3;
    void *temp_a1;
    void *temp_t7_2;
    void *temp_t9;
    void *var_a0_2;

    sp128 = NULL;
    sp8C = &gNotes[noteIndex];
    var_v1 = 0;
    if (((u32) (noteSubEu->unk0 * 2) >> 0x1F) == 1) {
        var_v1 = 1;
        synthesisState->restart = 0;
        synthesisState->samplePosInt = 0;
        synthesisState->samplePosFrac = 0;
        synthesisState->curVolLeft = 0;
        synthesisState->curVolRight = 0;
        synthesisState->prevHeadsetPanRight = 0;
        synthesisState->prevHeadsetPanLeft = 0;
    }
    temp_t7 = noteSubEu->resamplingRateFixedPoint;
    sp112 = temp_t7;
    spB0 = ((u16) noteSubEu->unk0 & 1) + 1;
    temp_v0 = (temp_t7 * bufLen * 2) + synthesisState->samplePosFrac;
    synthesisState->samplePosFrac = temp_v0;
    temp_s0 = temp_v0 >> 0x10;
    var_a0 = noteSubEu->unk0;
    if (var_a0 & 0x20000) {
        temp_v0_2 = load_wave_samples(acmd, noteSubEu, synthesisState, (s32) temp_s0);
        temp_a2 = synthesisState->samplePosInt;
        sp9E = (temp_a2 * 2) + 0x1A0;
        synthesisState->samplePosInt = temp_a2 + temp_s0;
        var_a0 = noteSubEu->unk0;
        acmd = temp_v0_2;
    } else {
        temp_t7_2 = *noteSubEu->sound.samples;
        sp130 = temp_t7_2;
        temp_t9 = temp_t7_2->unk8;
        sp12C = temp_t9;
        spDC = temp_t9->unk4;
        spA0 = 0;
        spAC = 0;
        spEC = temp_t7_2->unk4;
        if (spB0 > 0) {
            sp50 = temp_v0 >> 0x10;
            sp114 = var_v1;
            var_s2_2 = acmd;
loop_6:
            temp_a1 = sp130->unkC;
            var_fp = 0;
            var_s4 = 0;
            temp_a2_2 = temp_a1 + 8;
            if (spB0 == 1) {
                var_t5 = sp50;
            } else {
                var_t5 = sp50;
                if (sp50 & 1) {
                    var_t5 = (sp50 & ~1) + (spAC * 2);
                }
            }
            if (sp128 != temp_a2_2) {
                temp_v0_3 = var_s2_2;
                var_s2_2 += 8;
                temp_v0_3->words.w0 = ((temp_a1->unk0 * 0x10 * temp_a1->unk4) & 0xFFFFFF) | 0x0B000000;
                temp_v0_3->words.w1 = (((u32) (noteSubEu->unk0 << 0xB) >> 0x1D) * 2) + temp_a2_2 + 0x80000000;
                var_a0 = noteSubEu->unk0;
                sp128 = temp_a2_2;
            }
            if (((u32) (var_a0 << 0xB) >> 0x1D) != 0) {
                sp128 = gUnknownData_800F6290;
            }
            if (var_t5 != 0) {
loop_15:
                temp_a2_3 = synthesisState->samplePosInt;
                temp_a0 = var_t5 - var_fp;
                var_s3 = temp_a2_3 & 0xF;
                var_t3 = 0;
                var_t4 = 0;
                temp_v1 = spDC - temp_a2_3;
                if ((var_s3 == 0) && (synthesisState->restart == 0)) {
                    var_s3 = 0x10;
                }
                temp_a1_2 = 0x10 - var_s3;
                var_s5 = temp_a1_2;
                if (temp_a0 < temp_v1) {
                    temp_t9_2 = (s32) ((temp_a0 - temp_a1_2) + 0xF) / 16;
                    var_s1 = temp_t9_2 * 0x10;
                    var_t0 = temp_t9_2;
                    var_s6 = (temp_a1_2 + var_s1) - temp_a0;
                } else {
                    var_s1 = temp_v1 - temp_a1_2;
                    var_s6 = 0;
                    if (var_s1 <= 0) {
                        var_s1 = 0;
                        var_s5 = temp_v1;
                    }
                    var_t0 = (s32) (var_s1 + 0xF) / 16;
                    if (sp12C->unk8 != 0) {
                        var_t4 = 1;
                    } else {
                        var_t3 = 1;
                    }
                }
                var_t2 = 0;
                if (var_t0 != 0) {
                    temp_t6 = (s32) ((temp_a2_3 - var_s3) + 0x10) / 16;
                    if (sp130->unk1 == 0x81) {
                        var_s0 = ((var_t0 * 9) + 0x1F) & ~0xF;
                        var_a0_2 = (temp_t6 * 9) + spEC;
                    } else {
                        spD8 = temp_a0;
                        sp11C = var_t3;
                        sp118 = var_t4;
                        spE4 = var_t5;
                        temp_a1_3 = ((var_t0 * 9) + 0x1F) & ~0xF;
                        var_s0 = temp_a1_3;
                        var_a0_2 = dma_sample_data((temp_t6 * 9) + spEC, temp_a1_3, sp114, &synthesisState->sampleDmaIndex);
                    }
                    var_t1 = 0x540 - var_s0;
                    var_t2 = (s32) var_a0_2 & 0xF;
                    var_s2_2->words.w1 = (var_a0_2 - var_t2) + 0x80000000;
                    var_s2_2->words.w0 = ((((s32) var_s0 >> 4) & 0xFF) << 0x10) | 0x14000000 | (var_t1 & 0xFFFF);
                    var_s2_2 += 8;
                } else {
                    var_s1 = 0;
                    var_t1 = 0x540 - (((var_t0 * 9) + 0x1F) & 0xFFF0);
                }
                temp_v0_4 = var_s2_2;
                if (synthesisState->restart != 0) {
                    temp_v0_4->words.w0 = 0x0F000000;
                    var_s2_2 += 8;
                    temp_v0_4->words.w1 = sp130->unk8 + 0x80000010;
                    sp114 = 2;
                    synthesisState->restart = 0;
                }
                if (var_fp == 0) {
                    var_a2 = var_s1 * 2;
                    var_s2_2->words.w1 = (var_a2 & 0xFFFF) | 0x01A00000;
                    var_s2_2->words.w0 = ((var_t1 + var_t2) & 0xFFFF) | 0x08000000;
                    temp_s2 = var_s2_2 + 8;
                    temp_s2->words.w0 = ((sp114 & 0xFF) << 0x10) | 0x01000000;
                    temp_s2->words.w1 = (u32) (synthesisState->synthesisBuffers + 0x80000000);
                    var_s2_2 = temp_s2 + 8;
                    spFC = var_s3 * 2;
                    var_a3 = (var_s1 + var_s5) - var_s6;
                } else {
                    temp_t8 = (var_s4 + 0x1F) & ~0xF;
                    var_s2_2->words.w0 = ((var_t1 + var_t2) & 0xFFFF) | 0x08000000;
                    var_a2 = var_s1 * 2;
                    var_s2_2->words.w1 = ((temp_t8 + 0x1A0) << 0x10) | (var_a2 & 0xFFFF);
                    temp_s2_2 = var_s2_2 + 8;
                    temp_s2_2->words.w0 = ((sp114 & 0xFF) << 0x10) | 0x01000000;
                    temp_s2_2->words.w1 = (u32) (synthesisState->synthesisBuffers + 0x80000000);
                    temp_s2_3 = temp_s2_2 + 8;
                    var_a3 = (var_s1 + var_s5) - var_s6;
                    temp_s2_3->words.w0 = ((temp_t8 + (var_s3 * 2) + 0x1A0) & 0xFFFFFF) | 0x0A000000;
                    temp_s2_3->words.w1 = ((var_s4 + 0x1A0) << 0x10) | ((var_a3 * 2) & 0xFFFF);
                    var_s2_2 = temp_s2_3 + 8;
                }
                var_fp += var_a3;
                if (sp114 != 1) {
                    sp114 = 0;
                    if ((sp114 ^ 2) != 0) {
                        if (var_s4 != 0) {
                            var_s4 += var_a3 * 2;
                        } else {
                            var_s4 = (var_s3 + var_a3) * 2;
                        }
                    } else {
                        var_s4 += var_a3 * 2;
                    }
                } else {
                    spFC = 0x00000020;
                    var_s4 = var_a2 + 0x20;
                    sp114 = 0;
                }
                if (var_t3 != 0) {
                    var_s2_2->words.w0 = ((var_s4 + 0x1A0) & 0xFFFFFF) | 0x02000000;
                    var_s2_2->words.w1 = (var_t5 - var_fp) * 2;
                    var_s2_2 += 8;
                    noteSubEu->unk0 = (s8) ((u8) noteSubEu->unk0 | 0x20);
                    sp8C->unkB0 = (u8) (sp8C->unkB0 | 0x20);
                    sp8C->unkB0 = (u8) (sp8C->unkB0 & 0xFF7F);
                    spE4 = var_t5;
                    func_800B6FB4(updateIndex, noteIndex);
                } else {
                    if (var_t4 != 0) {
                        synthesisState->restart = 1;
                        synthesisState->samplePosInt = sp12C->unk0;
                    } else {
                        synthesisState->samplePosInt += temp_a0;
                    }
                    if (var_fp != var_t5) {
                        goto loop_15;
                    }
                }
            }
            if (spB0 != 1) {
                if (spB0 != 2) {
                    var_a0 = noteSubEu->unk0;
                    var_t6 = (u32) (var_a0 * 4) >> 0x1F;
                    goto block_60;
                }
                if (spAC != 0) {
                    temp_v0_5 = var_s2_2;
                    if (spAC != 1) {
                        var_a0 = noteSubEu->unk0;
                        var_v1_2 = (u32) (var_a0 * 4) >> 0x1F;
                    } else {
                        var_s2_2 += 8;
                        temp_v0_5->words.w0 = ((((s32) var_t5 / 2) + 7) & 0xFFF8) | 0x11000000;
                        temp_v0_5->words.w1 = ((spFC + 0x1A0) << 0x10) | ((spA0 + 0x20) & 0xFFFF);
                        var_a0 = noteSubEu->unk0;
                        var_t6 = (u32) (var_a0 * 4) >> 0x1F;
                        goto block_60;
                    }
                } else {
                    temp_v0_6 = var_s2_2;
                    var_s2_2 += 8;
                    temp_v0_6->words.w0 = ((((s32) var_t5 / 2) + 7) & 0xFFF8) | 0x11000000;
                    temp_v0_6->words.w1 = ((spFC + 0x1A0) << 0x10) | 0x20;
                    spA0 = var_t5;
                    sp9E = 0x0020;
                    var_a0 = noteSubEu->unk0;
                    temp_t7_3 = (u32) (var_a0 * 4) >> 0x1F;
                    var_v1_2 = temp_t7_3;
                    if (temp_t7_3 != 0) {
                        var_s2_2->words.w1 = var_t5 + 0x10;
                        var_s2_2->words.w0 = ((var_t5 + 0x20) & 0xFFFFFF) | 0x02000000;
                        var_a0 = noteSubEu->unk0;
                        var_s2_2 += 8;
                        var_v1_2 = (u32) (var_a0 * 4) >> 0x1F;
                    }
                }
            } else {
                sp9E = spFC + 0x1A0;
                var_a0 = noteSubEu->unk0;
                var_t6 = (u32) (var_a0 * 4) >> 0x1F;
block_60:
                var_v1_2 = var_t6;
            }
            if (var_v1_2 != 0) {

            } else {
                temp_v0_7 = spAC + 1;
                spAC = temp_v0_7;
                if (temp_v0_7 != spB0) {
                    goto loop_6;
                }
            }
            acmd = var_s2_2;
        }
    }
    var_v1_3 = 0;
    if (((u32) (var_a0 * 2) >> 0x1F) == 1) {
        var_v1_3 = 1;
        noteSubEu->unk0 = (s8) ((u8) noteSubEu->unk0 & 0xFFBF);
    }
    temp_a2_4 = bufLen * 2;
    sp114 = var_v1_3;
    temp_a0_2 = final_resample(acmd, synthesisState, temp_a2_4, sp112, (u16) (s32) sp9E, var_v1_3);
    if ((noteSubEu->headsetPanRight != 0) || (synthesisState->prevHeadsetPanRight != 0)) {
        var_s0_2 = 1;
    } else if ((noteSubEu->headsetPanLeft != 0) || (var_s0_2 = 0, (synthesisState->prevHeadsetPanLeft != 0))) {
        var_s0_2 = 2;
    }
    temp_v0_8 = func_800B86A0(temp_a0_2, noteSubEu, synthesisState, bufLen, (u16) 0, var_s0_2, sp114);
    var_s2 = temp_v0_8;
    if ((u8) noteSubEu->unk0 & 1) {
        var_s2 = note_apply_headset_pan_effects(temp_v0_8, noteSubEu, synthesisState, temp_a2_4, (s32) sp114, var_s0_2);
    }
    return var_s2;
}
#else
GLOBAL_ASM("asm/non_matchings/audio/synthesis/synthesis_process_note.s")
#endif

Acmd *load_wave_samples(Acmd *acmd, struct NoteSubEu *noteSubEu, struct NoteSynthesisState *synthesisState, s32 nSamplesToLoad) {
    s32 a3;
    s32 repeats;
    aLoadBuffer(acmd++, VIRTUAL_TO_PHYSICAL2(noteSubEu->sound.samples), 0x1A0, 128);

    synthesisState->samplePosInt &= 0x3f;
    a3 = 64 - synthesisState->samplePosInt;
    if (a3 < nSamplesToLoad) {
        repeats = (nSamplesToLoad - a3 + 63) / 64;
        if (repeats != 0) {
            aDMEMMove2(acmd++, repeats, 0x1A0, 0x1A0 + 128, 128);
        }
    }
    return acmd;
}

Acmd *final_resample(Acmd *acmd, struct NoteSynthesisState *synthesisState, s32 count, u16 pitch, u16 dmemIn, u32 flags) {
    aSetBuffer(acmd++, /*flags*/ 0, dmemIn, /*dmemout*/ 0, count);
    aResample(acmd++, flags, pitch, VIRTUAL_TO_PHYSICAL2(synthesisState->synthesisBuffers->finalResampleState));
    return acmd;
}

#ifdef NON_MATCHING
// I wish I knew what was up with this function
// It doesn't quite match either the EU or Shindou versions
// of process_envelope.
// What's here appears to have the right "shape" based on
// the M2C output, but beyond that I can't really tell what's
// going on
Acmd *func_800B86A0(Acmd *cmd, struct NoteSubEu *note, struct NoteSynthesisState *synthesisState, s32 nSamples, u16 inBuf, s32 headsetPanSettings, UNUSED u32 flags) {
    u16 sourceRight;
    u16 sourceLeft;
    u16 targetLeft;
    u16 targetRight;
    s32 rampLeft;
    s32 rampRight;
    UNUSED s32 sourceReverbVol;
    UNUSED s16 rampReverb;
    UNUSED s32 reverbVolDiff = 0;

    sourceLeft = synthesisState->curVolLeft;
    sourceRight = synthesisState->curVolRight;
    targetLeft = note->targetVolLeft;
    targetRight = note->targetVolRight;
    targetLeft <<= 4;
    targetRight <<= 4;

    rampLeft  = (targetLeft  - sourceLeft)  / (nSamples >> 3);
    rampRight = (targetRight - sourceRight) / (nSamples >> 3);
    synthesisState->curVolLeft  = sourceLeft  + rampLeft  * (nSamples >> 3);
    synthesisState->curVolRight = sourceRight + rampRight * (nSamples >> 3);

    if (note->usesHeadsetPanEffects) {
        aClearBuffer(cmd++, DMEM_ADDR_NOTE_PAN_TEMP, DEFAULT_LEN_1CH);
        aEnvSetup1(cmd++, note->reverbVol, (((sourceLeft&0xFF) << 8) | (sourceRight&0xFF)), rampRight, rampLeft);
        aEnvSetup2(cmd++, sourceLeft, sourceRight);

        switch (headsetPanSettings) {
            case 1:
                aEnvMixer(cmd++,
                    inBuf, nSamples,
                    0,
                    note->stereoStrongRight, note->stereoStrongLeft,
                    DMEM_ADDR_NOTE_PAN_TEMP,
                    DMEM_ADDR_RIGHT_CH,
                    DMEM_ADDR_WET_LEFT_CH,
                    DMEM_ADDR_WET_RIGHT_CH);
                break;
            case 2:
                aEnvMixer(cmd++,
                    inBuf, nSamples,
                    0,
                    note->stereoStrongRight, note->stereoStrongLeft,
                    DMEM_ADDR_LEFT_CH,
                    DMEM_ADDR_NOTE_PAN_TEMP,
                    DMEM_ADDR_WET_LEFT_CH,
                    DMEM_ADDR_WET_RIGHT_CH);
                break;
            default:
                aEnvMixer(cmd++,
                    inBuf, nSamples,
                    0,
                    note->stereoStrongRight, note->stereoStrongLeft,
                    DMEM_ADDR_LEFT_CH,
                    DMEM_ADDR_RIGHT_CH,
                    DMEM_ADDR_WET_LEFT_CH,
                    DMEM_ADDR_WET_RIGHT_CH);
                break;
        }
    } else {
        aEnvSetup1(cmd++, note->reverbVol, (((sourceLeft&0xFF) << 8) | (sourceRight&0xFF)), rampLeft, rampRight);
        aEnvSetup2(cmd++, sourceLeft, sourceRight);
        aEnvMixer(cmd++,
                inBuf, nSamples,
                0,
                note->stereoStrongRight, note->stereoStrongLeft,
                DMEM_ADDR_LEFT_CH,
                DMEM_ADDR_RIGHT_CH,
                DMEM_ADDR_WET_LEFT_CH,
                DMEM_ADDR_WET_RIGHT_CH);
    }
    return cmd;
}
#else
GLOBAL_ASM("asm/non_matchings/audio/synthesis/func_800B86A0.s")
#endif

Acmd *note_apply_headset_pan_effects(Acmd *acmd, struct NoteSubEu *noteSubEu, struct NoteSynthesisState *note, s32 bufLen, s32 flags, s32 leftRight) {
    u16 dest;
    u16 pitch;
    u8 prevPanShift;
    u8 panShift;
    UNUSED u8 unkDebug;

    switch (leftRight) {
        case 1:
            dest = 0x540;
            panShift = noteSubEu->headsetPanRight;
            note->prevHeadsetPanLeft = 0;
            prevPanShift = note->prevHeadsetPanRight;
            note->prevHeadsetPanRight = panShift;
            break;
        case 2:
            dest = 0x6C0;
            panShift = noteSubEu->headsetPanLeft;
            note->prevHeadsetPanRight = 0;

            prevPanShift = note->prevHeadsetPanLeft;
            note->prevHeadsetPanLeft = panShift;
            break;
        default:
            return acmd;
    }

    if (flags != 1) { // A_INIT?
        // Slightly adjust the sample rate in order to fit a change in pan shift
        if (prevPanShift == 0) {
            // Kind of a hack that moves the first samples into the resample state
            aDMEMMove(acmd++, 0x0200, 0x0000, 8);
            aClearBuffer(acmd++, 8, 8); // Set pitch accumulator to 0 in the resample state
            aDMEMMove(acmd++, 0x0200, 0x0000 + 0x10,
                      0x10); // No idea, result seems to be overwritten later

            aSaveBuffer(acmd++, 0x0000, VIRTUAL_TO_PHYSICAL2(note->synthesisBuffers->panResampleState), sizeof(note->synthesisBuffers->panResampleState));

            pitch = (bufLen << 0xf) / (bufLen + panShift - prevPanShift + 8);
            if (pitch) {}
            aSetBuffer(acmd++, 0, 0x0200 + 8, 0x0000, panShift + bufLen - prevPanShift);
            aResample(acmd++, 0, pitch, VIRTUAL_TO_PHYSICAL2(note->synthesisBuffers->panResampleState));
        } else {
            if (panShift == 0) {
                pitch = (bufLen << 0xf) / (bufLen - prevPanShift - 4);
            } else {
                pitch = (bufLen << 0xf) / (bufLen + panShift - prevPanShift);
            }

            if (1) {}

            aSetBuffer(acmd++, 0, 0x0200, 0x0000, bufLen + panShift - prevPanShift);
            aResample(acmd++, 0, pitch, VIRTUAL_TO_PHYSICAL2(note->synthesisBuffers->panResampleState));
        }

        if (prevPanShift != 0) {
            aLoadBuffer(acmd++, VIRTUAL_TO_PHYSICAL2(note->synthesisBuffers->panSamplesBuffer), 0x0200, prevPanShift);
            aDMEMMove(acmd++, 0x0000, 0x0200 + prevPanShift, panShift + bufLen - prevPanShift);
        } else {
            aDMEMMove(acmd++, 0x0000, 0x0200, panShift + bufLen - prevPanShift);
        }
    } else {
        // Just shift right
        aDMEMMove(acmd++, 0x0200, 0x0000, bufLen);
        aDMEMMove(acmd++, 0x0000, 0x0200 + panShift, bufLen);
        aClearBuffer(acmd++, 0x0200, panShift);
    }

    if (panShift) {
        // Save excessive samples for next iteration
        aSaveBuffer(acmd++, 0x0200 + bufLen, VIRTUAL_TO_PHYSICAL2(note->synthesisBuffers->panSamplesBuffer), panShift);
    }

    aMix(acmd++, /*gain*/ 0x7FFF, /*in*/ 0x0200, /*out*/ dest, ALIGN(bufLen, 5));

    return acmd;
}
