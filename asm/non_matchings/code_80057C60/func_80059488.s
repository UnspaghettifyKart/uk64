glabel func_80059488
/* 05A088 80059488 3C0E800E */  lui   $t6, %hi(gModeSelection) # $t6, 0x800e
/* 05A08C 8005948C 8DCEC53C */  lw    $t6, %lo(gModeSelection)($t6)
/* 05A090 80059490 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 05A094 80059494 24010003 */  li    $at, 3
/* 05A098 80059498 AFBF0014 */  sw    $ra, 0x14($sp)
/* 05A09C 8005949C 11C1000E */  beq   $t6, $at, .L800594D8
/* 05A0A0 800594A0 AFA40018 */   sw    $a0, 0x18($sp)
/* 05A0A4 800594A4 3C188016 */  lui   $t8, %hi(D_80165800)
/* 05A0A8 800594A8 0304C021 */  addu  $t8, $t8, $a0
/* 05A0AC 800594AC 83185800 */  lb    $t8, %lo(D_80165800)($t8)
/* 05A0B0 800594B0 3C198019 */  lui   $t9, %hi(D_8018D188) # $t9, 0x8019
/* 05A0B4 800594B4 17000008 */  bnez  $t8, .L800594D8
/* 05A0B8 800594B8 00000000 */   nop   
/* 05A0BC 800594BC 8F39D188 */  lw    $t9, %lo(D_8018D188)($t9)
/* 05A0C0 800594C0 13200005 */  beqz  $t9, .L800594D8
/* 05A0C4 800594C4 00000000 */   nop   
/* 05A0C8 800594C8 0C013E9E */  jal   func_8004FA78
/* 05A0CC 800594CC 00000000 */   nop   
/* 05A0D0 800594D0 0C0139E3 */  jal   func_8004E78C
/* 05A0D4 800594D4 8FA40018 */   lw    $a0, 0x18($sp)
.L800594D8:
/* 05A0D8 800594D8 0C01398E */  jal   func_8004E638
/* 05A0DC 800594DC 8FA40018 */   lw    $a0, 0x18($sp)
/* 05A0E0 800594E0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 05A0E4 800594E4 27BD0018 */  addiu $sp, $sp, 0x18
/* 05A0E8 800594E8 03E00008 */  jr    $ra
/* 05A0EC 800594EC 00000000 */   nop   