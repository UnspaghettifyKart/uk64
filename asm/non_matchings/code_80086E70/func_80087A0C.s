glabel func_80087A0C
/* 08860C 80087A0C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 088610 80087A10 AFBF001C */  sw    $ra, 0x1c($sp)
/* 088614 80087A14 AFB00018 */  sw    $s0, 0x18($sp)
/* 088618 80087A18 AFA5003C */  sw    $a1, 0x3c($sp)
/* 08861C 80087A1C 00808025 */  move  $s0, $a0
/* 088620 80087A20 AFA60040 */  sw    $a2, 0x40($sp)
/* 088624 80087A24 AFA70044 */  sw    $a3, 0x44($sp)
/* 088628 80087A28 AFA0002C */  sw    $zero, 0x2c($sp)
/* 08862C 80087A2C 0C01C89C */  jal   func_80072270
/* 088630 80087A30 24050008 */   li    $a1, 8
/* 088634 80087A34 1040003A */  beqz  $v0, .L80087B20
/* 088638 80087A38 02002025 */   move  $a0, $s0
/* 08863C 80087A3C 0C01C870 */  jal   func_800721C0
/* 088640 80087A40 24050008 */   li    $a1, 8
/* 088644 80087A44 87AE0042 */  lh    $t6, 0x42($sp)
/* 088648 80087A48 87AF003E */  lh    $t7, 0x3e($sp)
/* 08864C 80087A4C 87A8004A */  lh    $t0, 0x4a($sp)
/* 088650 80087A50 87A90046 */  lh    $t1, 0x46($sp)
/* 088654 80087A54 01CF1023 */  subu  $v0, $t6, $t7
/* 088658 80087A58 0002C400 */  sll   $t8, $v0, 0x10
/* 08865C 80087A5C 00181403 */  sra   $v0, $t8, 0x10
/* 088660 80087A60 00420019 */  multu $v0, $v0
/* 088664 80087A64 01092023 */  subu  $a0, $t0, $t1
/* 088668 80087A68 00045400 */  sll   $t2, $a0, 0x10
/* 08866C 80087A6C 000A2403 */  sra   $a0, $t2, 0x10
/* 088670 80087A70 AFA40024 */  sw    $a0, 0x24($sp)
/* 088674 80087A74 AFA20028 */  sw    $v0, 0x28($sp)
/* 088678 80087A78 00006012 */  mflo  $t4
/* 08867C 80087A7C 00000000 */  nop   
/* 088680 80087A80 00000000 */  nop   
/* 088684 80087A84 00840019 */  multu $a0, $a0
/* 088688 80087A88 00006812 */  mflo  $t5
/* 08868C 80087A8C 018D7021 */  addu  $t6, $t4, $t5
/* 088690 80087A90 448E2000 */  mtc1  $t6, $f4
/* 088694 80087A94 0C033850 */  jal   sqrtf
/* 088698 80087A98 46802320 */   cvt.s.w $f12, $f4
/* 08869C 80087A9C 4600048D */  trunc.w.s $f18, $f0
/* 0886A0 80087AA0 8FA20028 */  lw    $v0, 0x28($sp)
/* 0886A4 80087AA4 8FA40024 */  lw    $a0, 0x24($sp)
/* 0886A8 80087AA8 44808000 */  mtc1  $zero, $f16
/* 0886AC 80087AAC 44189000 */  mfc1  $t8, $f18
/* 0886B0 80087AB0 44829000 */  mtc1  $v0, $f18
/* 0886B4 80087AB4 44845000 */  mtc1  $a0, $f10
/* 0886B8 80087AB8 0010C8C0 */  sll   $t9, $s0, 3
/* 0886BC 80087ABC 46809320 */  cvt.s.w $f12, $f18
/* 0886C0 80087AC0 0330C823 */  subu  $t9, $t9, $s0
/* 0886C4 80087AC4 3C088016 */  lui   $t0, %hi(D_80165C18) # $t0, 0x8016
/* 0886C8 80087AC8 0019C940 */  sll   $t9, $t9, 5
/* 0886CC 80087ACC 25085C18 */  addiu $t0, %lo(D_80165C18) # addiu $t0, $t0, 0x5c18
/* 0886D0 80087AD0 468053A0 */  cvt.s.w $f14, $f10
/* 0886D4 80087AD4 03281821 */  addu  $v1, $t9, $t0
/* 0886D8 80087AD8 A7B80036 */  sh    $t8, 0x36($sp)
/* 0886DC 80087ADC E4700014 */  swc1  $f16, 0x14($v1)
/* 0886E0 80087AE0 0C0ADE0C */  jal   func_802B7830
/* 0886E4 80087AE4 AFA30020 */   sw    $v1, 0x20($sp)
/* 0886E8 80087AE8 8FA30020 */  lw    $v1, 0x20($sp)
/* 0886EC 80087AEC 02002025 */  move  $a0, $s0
/* 0886F0 80087AF0 0C021D47 */  jal   func_8008751C
/* 0886F4 80087AF4 A46200C0 */   sh    $v0, 0xc0($v1)
/* 0886F8 80087AF8 87A90036 */  lh    $t1, 0x36($sp)
/* 0886FC 80087AFC 8FA30020 */  lw    $v1, 0x20($sp)
/* 088700 80087B00 44899000 */  mtc1  $t1, $f18
/* 088704 80087B04 C4660034 */  lwc1  $f6, 0x34($v1)
/* 088708 80087B08 46809120 */  cvt.s.w $f4, $f18
/* 08870C 80087B0C 46062203 */  div.s $f8, $f4, $f6
/* 088710 80087B10 4600428D */  trunc.w.s $f10, $f8
/* 088714 80087B14 440B5000 */  mfc1  $t3, $f10
/* 088718 80087B18 00000000 */  nop   
/* 08871C 80087B1C A46B00B0 */  sh    $t3, 0xb0($v1)
.L80087B20:
/* 088720 80087B20 001060C0 */  sll   $t4, $s0, 3
/* 088724 80087B24 01906023 */  subu  $t4, $t4, $s0
/* 088728 80087B28 3C0D8016 */  lui   $t5, %hi(D_80165C18) # $t5, 0x8016
/* 08872C 80087B2C 25AD5C18 */  addiu $t5, %lo(D_80165C18) # addiu $t5, $t5, 0x5c18
/* 088730 80087B30 000C6140 */  sll   $t4, $t4, 5
/* 088734 80087B34 018D1821 */  addu  $v1, $t4, $t5
/* 088738 80087B38 846E00B0 */  lh    $t6, 0xb0($v1)
/* 08873C 80087B3C 02002025 */  move  $a0, $s0
/* 088740 80087B40 25CFFFFF */  addiu $t7, $t6, -1
/* 088744 80087B44 A46F00B0 */  sh    $t7, 0xb0($v1)
/* 088748 80087B48 847800B0 */  lh    $t8, 0xb0($v1)
/* 08874C 80087B4C 07010006 */  bgez  $t8, .L80087B68
/* 088750 80087B50 00000000 */   nop   
/* 088754 80087B54 0C01C87A */  jal   func_800721E8
/* 088758 80087B58 24050008 */   li    $a1, 8
/* 08875C 80087B5C 24190001 */  li    $t9, 1
/* 088760 80087B60 10000003 */  b     .L80087B70
/* 088764 80087B64 AFB9002C */   sw    $t9, 0x2c($sp)
.L80087B68:
/* 088768 80087B68 0C021DD7 */  jal   func_8008775C
/* 08876C 80087B6C 02002025 */   move  $a0, $s0
.L80087B70:
/* 088770 80087B70 8FBF001C */  lw    $ra, 0x1c($sp)
/* 088774 80087B74 8FA2002C */  lw    $v0, 0x2c($sp)
/* 088778 80087B78 8FB00018 */  lw    $s0, 0x18($sp)
/* 08877C 80087B7C 03E00008 */  jr    $ra
/* 088780 80087B80 27BD0038 */   addiu $sp, $sp, 0x38