glabel func_80077EB8
/* 078AB8 80077EB8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 078ABC 80077EBC AFBF0014 */  sw    $ra, 0x14($sp)
/* 078AC0 80077EC0 AFA5001C */  sw    $a1, 0x1c($sp)
/* 078AC4 80077EC4 84CF0026 */  lh    $t7, 0x26($a2)
/* 078AC8 80077EC8 3C088019 */  lui   $t0, %hi(D_8018D210) # $t0, 0x8019
/* 078ACC 80077ECC 8508D210 */  lh    $t0, %lo(D_8018D210)($t0)
/* 078AD0 80077ED0 01E51023 */  subu  $v0, $t7, $a1
/* 078AD4 80077ED4 0002C400 */  sll   $t8, $v0, 0x10
/* 078AD8 80077ED8 0018CC03 */  sra   $t9, $t8, 0x10
/* 078ADC 80077EDC 0328082A */  slt   $at, $t9, $t0
/* 078AE0 80077EE0 10200006 */  beqz  $at, .L80077EFC
/* 078AE4 80077EE4 03201025 */   move  $v0, $t9
/* 078AE8 80077EE8 3C098019 */  lui   $t1, %hi(D_8018D208) # $t1, 0x8019
/* 078AEC 80077EEC 8529D208 */  lh    $t1, %lo(D_8018D208)($t1)
/* 078AF0 80077EF0 0139082A */  slt   $at, $t1, $t9
/* 078AF4 80077EF4 14200015 */  bnez  $at, .L80077F4C
/* 078AF8 80077EF8 00000000 */   nop   
.L80077EFC:
/* 078AFC 80077EFC 44823000 */  mtc1  $v0, $f6
/* 078B00 80077F00 3C0A8019 */  lui   $t2, %hi(D_8018D218) # $t2, 0x8019
/* 078B04 80077F04 854AD218 */  lh    $t2, %lo(D_8018D218)($t2)
/* 078B08 80077F08 46803220 */  cvt.s.w $f8, $f6
/* 078B0C 80077F0C 3C018019 */  lui   $at, %hi(D_8018D1E8) # $at, 0x8019
/* 078B10 80077F10 C424D1E8 */  lwc1  $f4, %lo(D_8018D1E8)($at)
/* 078B14 80077F14 448A8000 */  mtc1  $t2, $f16
/* 078B18 80077F18 000458C0 */  sll   $t3, $a0, 3
/* 078B1C 80077F1C 01645823 */  subu  $t3, $t3, $a0
/* 078B20 80077F20 46082282 */  mul.s $f10, $f4, $f8
/* 078B24 80077F24 000B5940 */  sll   $t3, $t3, 5
/* 078B28 80077F28 3C018016 */  lui   $at, %hi(D_80165C40)
/* 078B2C 80077F2C 002B0821 */  addu  $at, $at, $t3
/* 078B30 80077F30 24050010 */  li    $a1, 16
/* 078B34 80077F34 468084A0 */  cvt.s.w $f18, $f16
/* 078B38 80077F38 460A9180 */  add.s $f6, $f18, $f10
/* 078B3C 80077F3C 0C01C870 */  jal   func_800721C0
/* 078B40 80077F40 E4265C40 */   swc1  $f6, %lo(D_80165C40)($at)
/* 078B44 80077F44 10000004 */  b     .L80077F58
/* 078B48 80077F48 8FBF0014 */   lw    $ra, 0x14($sp)
.L80077F4C:
/* 078B4C 80077F4C 0C01C87A */  jal   func_800721E8
/* 078B50 80077F50 24050010 */   li    $a1, 16
/* 078B54 80077F54 8FBF0014 */  lw    $ra, 0x14($sp)
.L80077F58:
/* 078B58 80077F58 27BD0018 */  addiu $sp, $sp, 0x18
/* 078B5C 80077F5C 03E00008 */  jr    $ra
/* 078B60 80077F60 00000000 */   nop   