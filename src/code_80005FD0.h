#ifndef CODE_80005FD0_H
#define CODE_80005FD0_H

#include "vehicles.h"
#include "camera.h"
#include "waypoints.h"
#include "common_textures.h"

struct struct_801642D8 {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ s16 ffff;
    /* 0x4 */ s16 timer; // confirm?
    /* 0x6 */ s16 laps; // confirm?
    /* 0x8 */ s32 blank;
    /* 0xC */ s32 unkC;
};

struct unexpiredActors {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 actorIndex;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ // s16 compilerPadding;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ s32 unk18;
}; // size = 0x1C

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} Test; // size = 0x10

// Something related to CPU item usage
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 actorIndex;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} D_801642D8_entry; // size = 0x10

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
} UnkStruct_46D0;

typedef struct {
    s16 x;
    s16 z;
} PathNoY;

/* Function Prototypes */
s16  func_80005FD0(Vec3f, Vec3f);

s32  func_80006018(f32, f32, f32, f32, f32, f32, f32, f32);
void func_80006114(Vec3f, Vec3f, s16);
s32  func_800061DC(Vec3f, f32, s32);
void func_800065D0(s32, Player*);
void set_places(void);

void func_800070F4(void);
void func_800074D4(void);
s32  func_80007BF8(u16, u16, u16, u16, u16);
void func_80007D04(s32, Player*);
void func_80007FA4(s32, Player*, f32);

void func_80008424(s32, f32, Player*);
s32  func_800088D8(s32, s16, s16);
void func_80008DC0(s32);
s32  func_80008E58(s32, s32);
void func_80008F38(s32);

void func_80009000(s32);
void func_800090F0(s32, Player*);
f32  func_80009258(s32, f32, f32);
void func_8000929C(s32, Player*);
void func_800097E0(void);
void func_800098FC(s32, Player*);
void func_800099EC(s32, Player*);
void func_80009B60(s32);

void func_8000B140(s32);
s32  func_8000B7E4(s32, u16);
s32  func_8000B820(s32);
f32  func_8000B874(f32, f32, u16, s32);
void func_8000B95C(s32, u16, s32);
void func_8000BA14(u16, f32, f32, s16);
void func_8000BBD8(u16, f32, s16);
s16  func_8000BD94(f32, f32, f32, s32);

s16  func_8000C0BC(f32, f32, f32, u16, s32*);
s16  func_8000C884(f32, f32, f32, s16, s32, u16);
s16  func_8000C9DC(f32, f32, f32, s16, s32);
void func_8000CBA4(f32, f32, f32, s16*, s32);
void func_8000CBF8(f32, f32, f32, s16*, s32);
s16  func_8000CC88(f32, f32, f32, Player*, s32, s32*);
s16  func_8000CD24(f32, f32, f32, s16, Player*, s32, s32);

s16  func_8000D100(f32, f32, f32, s16);
s16  func_8000D24C(f32, f32, f32, s32*);
s16  func_8000D2B4(f32, f32, f32, s16, s32);
s16  func_8000D33C(f32, f32, f32, s16, s32);
f32  func_8000D3B8(s32);
void func_8000D438(s32, u16);
s16  func_8000D6D0(Vec3f, s16*, f32, f32, s16, s16);
s16  func_8000D940(Vec3f, s16*, f32, f32, s16);
s16  func_8000DBAC(Vec3f, s16*, f32);
void set_bomb_kart_spawn_positions(void);
void func_8000DF8C(s32);

s32  func_8000ED14(s32, s16);
s32  func_8000ED80(s32);
s32  func_8000EDC8(s32);
s32  func_8000EE10(s32);
void func_8000EE58(s32);
void func_8000EEDC(void);
void func_8000EF20(void);

void func_8000F0E0(void);
void func_8000F124(void);
void func_8000F2BC(TrackWaypoint*, size_t);
void func_8000F2DC(void);
void func_8000F628(void);

void func_800100F0(s32);
void func_80010218(s32);
f32  func_80010480(s32, u16);
void func_800107C4(s32);
s16  func_80010CB0(s32, s32);
void func_80010DBC(s32);
void func_80010E6C(s32);
f32  func_80010F40(f32, f32, f32, s32, s32);
f32  func_80010FA0(f32, f32, f32, s32, s32);

s32  func_80011014(TrackWaypoint *, TrackWaypoint *, s32, s32);
s32  process_path_data(TrackWaypoint*, TrackWaypoint*);
s32  func_8001168C(PathNoY*, TrackWaypoint*, s32);
void func_80011A5C(void);
void func_80011AB8(s32);
void func_80011AE4(s32);
void func_80011B14(s32, Player*);
void func_80011D48(s32, Player*);
void func_80011E38(s32);
void func_80011EC0(s32, Player*, s32, u16);

void func_800120C8(void);
void func_80012190(void);
void func_80012220(VehicleStuff*);
void init_course_vehicles(void);
void func_80012780(TrainCarStuff*, s16*, u16);
void func_800127E0(void);
void func_80012A48(TrainCarStuff*, s16);
void func_80012AC0(void);
void func_80012DC0(s32, Player*);

void func_80013054(void);
void func_800131DC(s32);
void func_800132F4(void);
void func_800133C4(void);
void func_80013854(Player*);
void func_800139E4(f32, f32, s32, s32, VehicleStuff*, TrackWaypoint*);
f32  func_80013C74(s16, s16);
void func_80013D20(VehicleStuff*);
void func_80013F7C(s32, Player*, VehicleStuff*, f32, f32, s32, u32);

f32  func_800145A8(s16, f32, s16);
void func_800146B8(s32, s32, VehicleStuff*);
void func_800147E0(void);
void func_8001487C(void);
void func_800148C4(s32, Player*);
void func_8001490C(s32);
void func_80014934(void);
void func_800149D0(void);
void func_80014A18(s32, Player*);
void func_80014A60(s32);
void func_80014A88(void);
void func_80014B24(void);
void func_80014B6C(s32, Player*);
void func_80014BB4(s32);
void func_80014BDC(void);
void func_80014C78(void);
void func_80014CC0(s32, Player*);
void func_80014D08(s32);
void func_80014D30(s32, s32);
void func_80014DE4(s32);
f32  func_80014EE4(f32, s32);

void func_800151A4(Camera*, s32);
void func_8001530C(void);
void func_80015314(s32, f32, s32);
void func_80015390(Camera*, Player*, s32);
void func_80015544(s32, f32, s32, s32);
void func_8001577C(Camera*, UNUSED Player*, s32, s32);
void func_80015A9C(s32, f32, s32, s16);

void func_800162CC(s32, f32, s32, s16);
void func_80016C3C(s32, f32, s32);

void func_80017720(s32, f32, s32, s16);
void func_80017F10(s32, f32, s32, s16);

void func_80018718(s32, f32, s32, s16);

void func_80019118(s32, f32, s32, s16);
void func_8001933C(Camera*, UNUSED Player*, s32, s32);
void func_8001968C(void);
void func_8001969C(s32, f32, s32, s16);
void func_80019760(Camera*, UNUSED Player*, s32, s32);
void func_80019890(s32, s32);
void func_80019B50(s32, u16);
void func_80019C50(s32);
void func_80019D2C(Camera*, Player*, s32);
void func_80019DE4(void);
void func_80019DF4(void);
void func_80019E58(void);
void func_80019ED0(void);
void func_80019FB4(s32);

void func_8001A0A4(u16*, Camera*, Player*, s8, s32);
void func_8001A0DC(u16*, Camera*, Player*, s8, s32);
void func_8001A124(s32, s32);
s32  func_8001A310(s32, s32);
void func_8001A348(s32, f32, s32);
void func_8001A3D8(s32, f32, s32);
void func_8001A450(s32, s32, s32);
void func_8001A518(s32, s32, s32);
void func_8001A588(u16*, Camera*, Player*, s8, s32);
void func_8001AAAC(s16, s16, s16);
void func_8001AB00(void);
void cpu_decisions_branch_item(s32, s16*, s32);
void func_8001ABE0(s32, D_801642D8_entry*);
void func_8001ABEC(struct struct_801642D8*);
void cpu_use_item_strategy(s32);

void func_8001BE78(void);

void func_8001C05C(void);
void func_8001C14C(void);
void func_8001C3C4(s32);
void func_8001C42C(void);

/* This is where I'd put my static data, if I had any */

extern UnkCommonTextureStruct0 *D_800DC720[];
// Suspected to be the "width" of each waypoint. See data_0DD0A0_1.s
extern f32 D_800DCA4C[];
extern s16 D_800DCA20[];

struct _struct_D_800DD9D0_0x10 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ char padA[6];
};  // size 0x10

extern uintptr_t gCoursePathTable[20][4];
extern uintptr_t D_800DC8D0[20][4];
// An array of 21 items. The final element is for podium ceremony.
extern struct _struct_D_800DD9D0_0x10 D_800DD9D0[];


extern Collision D_80162E70;
extern s16 D_80162EB0; // Possibly a float.
extern s16 D_80162EB2; // possibly [3]
extern UnkCommonTextureStruct0 *D_80162EB8[];
extern s16 D_80162F10[];
extern s16 D_80162F50[];
extern Vec3f D_80162FA0;
extern Vec3f D_80162FB0;
extern Vec3f D_80162FC0;
extern s16 D_80162FCC;
extern s16 D_80162FD0;
extern f32 gCourseCompletionPercentByRank[]; // D_80162FD8
extern s16 D_80162FF8[];
extern s16 D_80163010[];
extern f32 D_80163028[];
extern s16 D_80163050[];
extern f32 D_80163068[];
extern f32 D_80163090[];
extern s32 D_801630B8[];
extern u16 D_801630E0;
extern s16 D_801630E2;
extern s16 D_801630E8[];
extern s16 D_801630FC;
extern s32 D_80163100[];
extern s32 D_80163128[];
extern s32 D_80163150[];
extern f32 D_80163178[];
extern f32 D_801631A0[];
extern s16 D_801631C8;
extern s32 D_801631CC;
extern TrackWaypoint *D_801631D0;
extern TrackWaypoint *D_801631D4;
extern s16 *D_801631D8;
extern u16 D_801631E0[];
extern u16 D_801631F8[];
extern f32 D_8016320C;
extern f32 D_80163210[];
extern s32 D_80163238;
extern u16 D_80163240[];
extern u16 D_80163258[];
extern u16 D_80163270[];
extern s32 D_80163288[];
// Exact pointer type unknown
extern UnkCommonTextureStruct0 *D_801632B0;
extern u16 D_801632B8[];
extern u16 D_801632D0[];
extern u16 D_801632E8[];
extern s16 D_80163300[];
extern u16 D_80163318[];
extern u16 D_80163330[];
extern u16 D_80163344[];
extern u16 D_80163348[];
extern u16 D_8016334C[];
extern u16 D_80163350[];
extern s32 D_80163368[];
extern s32 D_80163378;
extern s32 D_8016337C;
extern s16 D_80163380[];
extern s16 D_80163398[];
extern s16 D_801633B0[];
extern s16 D_801633C8[];
extern s16 D_801633E0[];
extern s16 D_801633F8[];
extern s16 D_80163410[];
extern f32 D_80163418[];
extern f32 D_80163428[];
extern f32 D_80163438[];
extern s32 D_80163448;
extern f32 D_8016344C;
extern f32 D_80163450[];
extern s16 D_80163478;
// 0 or 1, only 1 when when in extra (mirror) mode
extern s16 D_8016347A;
extern s16 D_8016347C;
extern s16 D_8016347E;
extern s32 D_80163480;
extern s32 D_80163484;
extern s32 D_80163488;
extern s16 D_8016348C;
extern s16 D_80163490[];
extern s16 D_801634A8[];
extern s16 D_801634C0[];
extern s16 D_801634D8[];
extern s16 D_801634EC;
extern s32 D_801634F0;
extern s32 D_801634F4;
extern Test D_801634F8[];
extern PathNoY *D_80163598;
extern s32 D_8016359C;
extern u16 isCrossingTriggeredByIndex[];
extern u16 D_801637BC[];
extern s32 D_80163DD8[];
extern struct unexpiredActors gUnexpiredActorsList[];
extern D_801642D8_entry D_801642D8[];
extern s16 D_80164358;
extern s16 D_8016435A;
extern s16 D_8016435C;
extern s16 gGPCurrentRacePlayerIdByRank[]; // D_80164360
extern s16 D_80164378[];
extern s32 gLapCountByPlayerId[]; // D_80164390
extern s32 gGPCurrentRaceRankByPlayerId[]; // D_801643B8
extern s32 D_801643E0[];
extern s32 D_80164408[];
extern u16 D_80164430;
extern u16 gNearestWaypointByPlayerId[];
extern s32 D_80164450[];
extern s16 D_80164478[];
extern s32 D_8016448C;
extern f32 D_80164498[];
extern f32 gLapCompletionPercentByPlayerId[]; // D_801644A8
extern f32 gCourseCompletionPercentByPlayerId[]; // D_801644D0
extern s16 D_801644F8[];
extern f32 D_80164510[];
extern s16 D_80164538[];
extern s32 D_801645D0[];
extern s32 D_801645E8[];
extern f32 D_801645F8[];
extern s32 D_80164608[];
extern f32 D_80164618[];
extern s32 D_80164628[];
extern f32 D_80164638[];
extern f32 D_80164648[];
extern f32 D_80164658[];
extern s16 D_80164670[];
extern s16 D_80164678[];
extern s16 D_80164680[];
extern f32 D_80164688[];
extern f32 D_80164698;
extern f32 D_8016469C;
extern f32 D_801646A0;
extern s16 D_801646C0[];
extern u32 D_801646C8;
extern u16 D_801646CC;
extern UnkStruct_46D0 D_801646D0[];

extern f32 D_800DCAA0[];


// See bss_80005FD0.s
extern f32 gCourseCompletionPercentByRank[NUM_PLAYERS];
extern s32 D_801643E0[];
extern s32 D_8016448C;
extern u16 D_801637BE;
extern u16 D_80163E2A;

extern Gfx D_0D0076F8[];

extern s32 D_800DDB20;

#endif
