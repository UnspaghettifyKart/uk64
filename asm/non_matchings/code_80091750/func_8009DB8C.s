glabel func_8009DB8C
/* 09E78C 8009DB8C 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 09E790 8009DB90 AFB50040 */  sw    $s5, 0x40($sp)
/* 09E794 8009DB94 3C158019 */  lui   $s5, %hi(D_8018E7D0) # $s5, 0x8019
/* 09E798 8009DB98 26B5E7D0 */  addiu $s5, %lo(D_8018E7D0) # addiu $s5, $s5, -0x1830
/* 09E79C 8009DB9C 8EAE0010 */  lw    $t6, 0x10($s5)
/* 09E7A0 8009DBA0 3C028019 */  lui   $v0, %hi(D_8018E7C8) # $v0, 0x8019
/* 09E7A4 8009DBA4 AFBF0044 */  sw    $ra, 0x44($sp)
/* 09E7A8 8009DBA8 25CF0001 */  addiu $t7, $t6, 1
/* 09E7AC 8009DBAC AEAF0010 */  sw    $t7, 0x10($s5)
/* 09E7B0 8009DBB0 8C42E7C8 */  lw    $v0, %lo(D_8018E7C8)($v0)
/* 09E7B4 8009DBB4 AFB4003C */  sw    $s4, 0x3c($sp)
/* 09E7B8 8009DBB8 AFB30038 */  sw    $s3, 0x38($sp)
/* 09E7BC 8009DBBC 01E2082B */  sltu  $at, $t7, $v0
/* 09E7C0 8009DBC0 AFB20034 */  sw    $s2, 0x34($sp)
/* 09E7C4 8009DBC4 AFB10030 */  sw    $s1, 0x30($sp)
/* 09E7C8 8009DBC8 AFB0002C */  sw    $s0, 0x2c($sp)
/* 09E7CC 8009DBCC 1420001B */  bnez  $at, .L8009DC3C
/* 09E7D0 8009DBD0 01E01825 */   move  $v1, $t7
/* 09E7D4 8009DBD4 14620015 */  bne   $v1, $v0, .L8009DC2C
/* 09E7D8 8009DBD8 00008025 */   move  $s0, $zero
/* 09E7DC 8009DBDC 3C128019 */  lui   $s2, %hi(D_8018D9B8) # $s2, 0x8019
/* 09E7E0 8009DBE0 2652D9B8 */  addiu $s2, %lo(D_8018D9B8) # addiu $s2, $s2, -0x2648
/* 09E7E4 8009DBE4 24110001 */  li    $s1, 1
/* 09E7E8 8009DBE8 240704B0 */  li    $a3, 1200
.L8009DBEC:
/* 09E7EC 8009DBEC 8E580000 */  lw    $t8, ($s2)
/* 09E7F0 8009DBF0 0310C821 */  addu  $t9, $t8, $s0
/* 09E7F4 8009DBF4 A3310000 */  sb    $s1, ($t9)
/* 09E7F8 8009DBF8 8E4B0000 */  lw    $t3, ($s2)
/* 09E7FC 8009DBFC 01706021 */  addu  $t4, $t3, $s0
/* 09E800 8009DC00 A1910001 */  sb    $s1, 1($t4)
/* 09E804 8009DC04 8E4D0000 */  lw    $t5, ($s2)
/* 09E808 8009DC08 01B07021 */  addu  $t6, $t5, $s0
/* 09E80C 8009DC0C A1D10002 */  sb    $s1, 2($t6)
/* 09E810 8009DC10 8E4F0000 */  lw    $t7, ($s2)
/* 09E814 8009DC14 01F0C021 */  addu  $t8, $t7, $s0
/* 09E818 8009DC18 26100004 */  addiu $s0, $s0, 4
/* 09E81C 8009DC1C 1607FFF3 */  bne   $s0, $a3, .L8009DBEC
/* 09E820 8009DC20 A3110003 */   sb    $s1, 3($t8)
/* 09E824 8009DC24 10000038 */  b     .L8009DD08
/* 09E828 8009DC28 00008025 */   move  $s0, $zero
.L8009DC2C:
/* 09E82C 8009DC2C 0C027399 */  jal   func_8009CE64
/* 09E830 8009DC30 24040004 */   li    $a0, 4
/* 09E834 8009DC34 10000034 */  b     .L8009DD08
/* 09E838 8009DC38 00008025 */   move  $s0, $zero
.L8009DC3C:
/* 09E83C 8009DC3C 241404B0 */  li    $s4, 1200
/* 09E840 8009DC40 0282001B */  divu  $zero, $s4, $v0
/* 09E844 8009DC44 0000C812 */  mflo  $t9
/* 09E848 8009DC48 00008025 */  move  $s0, $zero
/* 09E84C 8009DC4C 00009825 */  move  $s3, $zero
/* 09E850 8009DC50 14400002 */  bnez  $v0, .L8009DC5C
/* 09E854 8009DC54 00000000 */   nop   
/* 09E858 8009DC58 0007000D */  break 7
.L8009DC5C:
/* 09E85C 8009DC5C 3C128019 */  lui   $s2, %hi(D_8018D9B8) # $s2, 0x8019
/* 09E860 8009DC60 13200029 */  beqz  $t9, .L8009DD08
/* 09E864 8009DC64 24110001 */   li    $s1, 1
/* 09E868 8009DC68 2652D9B8 */  addiu $s2, %lo(D_8018D9B8) # addiu $s2, $s2, -0x2648
/* 09E86C 8009DC6C 8E4B0000 */  lw    $t3, ($s2)
.L8009DC70:
/* 09E870 8009DC70 01706021 */  addu  $t4, $t3, $s0
/* 09E874 8009DC74 918D0000 */  lbu   $t5, ($t4)
/* 09E878 8009DC78 15A00012 */  bnez  $t5, .L8009DCC4
/* 09E87C 8009DC7C 00000000 */   nop   
/* 09E880 8009DC80 8EAE0010 */  lw    $t6, 0x10($s5)
/* 09E884 8009DC84 028E7823 */  subu  $t7, $s4, $t6
/* 09E888 8009DC88 01E2001B */  divu  $zero, $t7, $v0
/* 09E88C 8009DC8C 00002012 */  mflo  $a0
/* 09E890 8009DC90 3098FFFF */  andi  $t8, $a0, 0xffff
/* 09E894 8009DC94 14400002 */  bnez  $v0, .L8009DCA0
/* 09E898 8009DC98 00000000 */   nop   
/* 09E89C 8009DC9C 0007000D */  break 7
.L8009DCA0:
/* 09E8A0 8009DCA0 03002025 */  move  $a0, $t8
/* 09E8A4 8009DCA4 0C0ADF8D */  jal   random_int
/* 09E8A8 8009DCA8 00000000 */   nop   
/* 09E8AC 8009DCAC 14400005 */  bnez  $v0, .L8009DCC4
/* 09E8B0 8009DCB0 00000000 */   nop   
/* 09E8B4 8009DCB4 8E590000 */  lw    $t9, ($s2)
/* 09E8B8 8009DCB8 26730001 */  addiu $s3, $s3, 1
/* 09E8BC 8009DCBC 03305821 */  addu  $t3, $t9, $s0
/* 09E8C0 8009DCC0 A1710000 */  sb    $s1, ($t3)
.L8009DCC4:
/* 09E8C4 8009DCC4 3C028019 */  lui   $v0, %hi(D_8018E7C8) # $v0, 0x8019
/* 09E8C8 8009DCC8 8C42E7C8 */  lw    $v0, %lo(D_8018E7C8)($v0)
/* 09E8CC 8009DCCC 240C04B0 */  li    $t4, 1200
/* 09E8D0 8009DCD0 26100001 */  addiu $s0, $s0, 1
/* 09E8D4 8009DCD4 0182001B */  divu  $zero, $t4, $v0
/* 09E8D8 8009DCD8 00001812 */  mflo  $v1
/* 09E8DC 8009DCDC 2A0104B0 */  slti  $at, $s0, 0x4b0
/* 09E8E0 8009DCE0 14400002 */  bnez  $v0, .L8009DCEC
/* 09E8E4 8009DCE4 00000000 */   nop   
/* 09E8E8 8009DCE8 0007000D */  break 7
.L8009DCEC:
/* 09E8EC 8009DCEC 54200003 */  bnel  $at, $zero, .L8009DCFC
/* 09E8F0 8009DCF0 0263082B */   sltu  $at, $s3, $v1
/* 09E8F4 8009DCF4 00008025 */  move  $s0, $zero
/* 09E8F8 8009DCF8 0263082B */  sltu  $at, $s3, $v1
.L8009DCFC:
/* 09E8FC 8009DCFC 5420FFDC */  bnel  $at, $zero, .L8009DC70
/* 09E900 8009DD00 8E4B0000 */   lw    $t3, ($s2)
/* 09E904 8009DD04 00008025 */  move  $s0, $zero
.L8009DD08:
/* 09E908 8009DD08 3C118015 */  lui   $s1, %hi(gDisplayListHead) # $s1, 0x8015
/* 09E90C 8009DD0C 26310298 */  addiu $s1, %lo(gDisplayListHead) # addiu $s1, $s1, 0x298
/* 09E910 8009DD10 8E220000 */  lw    $v0, ($s1)
/* 09E914 8009DD14 3C09E700 */  lui   $t1, 0xe700
/* 09E918 8009DD18 3C0FB900 */  lui   $t7, (0xB900031D >> 16) # lui $t7, 0xb900
/* 09E91C 8009DD1C 244D0008 */  addiu $t5, $v0, 8
/* 09E920 8009DD20 AE2D0000 */  sw    $t5, ($s1)
/* 09E924 8009DD24 AC400004 */  sw    $zero, 4($v0)
/* 09E928 8009DD28 AC490000 */  sw    $t1, ($v0)
/* 09E92C 8009DD2C 8E230000 */  lw    $v1, ($s1)
/* 09E930 8009DD30 3C180050 */  lui   $t8, (0x00504240 >> 16) # lui $t8, 0x50
/* 09E934 8009DD34 37184240 */  ori   $t8, (0x00504240 & 0xFFFF) # ori $t8, $t8, 0x4240
/* 09E938 8009DD38 246E0008 */  addiu $t6, $v1, 8
/* 09E93C 8009DD3C AE2E0000 */  sw    $t6, ($s1)
/* 09E940 8009DD40 35EF031D */  ori   $t7, (0xB900031D & 0xFFFF) # ori $t7, $t7, 0x31d
/* 09E944 8009DD44 AC6F0000 */  sw    $t7, ($v1)
/* 09E948 8009DD48 AC780004 */  sw    $t8, 4($v1)
/* 09E94C 8009DD4C 8E240000 */  lw    $a0, ($s1)
/* 09E950 8009DD50 240A00FF */  li    $t2, 255
/* 09E954 8009DD54 3C0BFA00 */  lui   $t3, 0xfa00
/* 09E958 8009DD58 24990008 */  addiu $t9, $a0, 8
/* 09E95C 8009DD5C AE390000 */  sw    $t9, ($s1)
/* 09E960 8009DD60 AC8A0004 */  sw    $t2, 4($a0)
/* 09E964 8009DD64 AC8B0000 */  sw    $t3, ($a0)
/* 09E968 8009DD68 8E250000 */  lw    $a1, ($s1)
/* 09E96C 8009DD6C 3C0EFFFD */  lui   $t6, (0xFFFDF6FB >> 16) # lui $t6, 0xfffd
/* 09E970 8009DD70 3C0DFCFF */  lui   $t5, (0xFCFFFFFF >> 16) # lui $t5, 0xfcff
/* 09E974 8009DD74 24AC0008 */  addiu $t4, $a1, 8
/* 09E978 8009DD78 AE2C0000 */  sw    $t4, ($s1)
/* 09E97C 8009DD7C 3C128019 */  lui   $s2, %hi(D_8018D9B8) # $s2, 0x8019
/* 09E980 8009DD80 35ADFFFF */  ori   $t5, (0xFCFFFFFF & 0xFFFF) # ori $t5, $t5, 0xffff
/* 09E984 8009DD84 35CEF6FB */  ori   $t6, (0xFFFDF6FB & 0xFFFF) # ori $t6, $t6, 0xf6fb
/* 09E988 8009DD88 2652D9B8 */  addiu $s2, %lo(D_8018D9B8) # addiu $s2, $s2, -0x2648
/* 09E98C 8009DD8C 240704B0 */  li    $a3, 1200
/* 09E990 8009DD90 3C08F600 */  lui   $t0, 0xf600
/* 09E994 8009DD94 24060028 */  li    $a2, 40
/* 09E998 8009DD98 ACAE0004 */  sw    $t6, 4($a1)
/* 09E99C 8009DD9C ACAD0000 */  sw    $t5, ($a1)
/* 09E9A0 8009DDA0 8E4F0000 */  lw    $t7, ($s2)
.L8009DDA4:
/* 09E9A4 8009DDA4 01F0C021 */  addu  $t8, $t7, $s0
/* 09E9A8 8009DDA8 93190000 */  lbu   $t9, ($t8)
/* 09E9AC 8009DDAC 53200025 */  beql  $t9, $zero, .L8009DE44
/* 09E9B0 8009DDB0 26100001 */   addiu $s0, $s0, 1
/* 09E9B4 8009DDB4 0206001A */  div   $zero, $s0, $a2
/* 09E9B8 8009DDB8 8E250000 */  lw    $a1, ($s1)
/* 09E9BC 8009DDBC 00001010 */  mfhi  $v0
/* 09E9C0 8009DDC0 000260C0 */  sll   $t4, $v0, 3
/* 09E9C4 8009DDC4 00001812 */  mflo  $v1
/* 09E9C8 8009DDC8 24AB0008 */  addiu $t3, $a1, 8
/* 09E9CC 8009DDCC AE2B0000 */  sw    $t3, ($s1)
/* 09E9D0 8009DDD0 000368C0 */  sll   $t5, $v1, 3
/* 09E9D4 8009DDD4 258E0008 */  addiu $t6, $t4, 8
/* 09E9D8 8009DDD8 31CF03FF */  andi  $t7, $t6, 0x3ff
/* 09E9DC 8009DDDC 25AB0008 */  addiu $t3, $t5, 8
/* 09E9E0 8009DDE0 01801025 */  move  $v0, $t4
/* 09E9E4 8009DDE4 316C03FF */  andi  $t4, $t3, 0x3ff
/* 09E9E8 8009DDE8 000FC380 */  sll   $t8, $t7, 0xe
/* 09E9EC 8009DDEC 01A01825 */  move  $v1, $t5
/* 09E9F0 8009DDF0 000C6880 */  sll   $t5, $t4, 2
/* 09E9F4 8009DDF4 0308C825 */  or    $t9, $t8, $t0
/* 09E9F8 8009DDF8 306B03FF */  andi  $t3, $v1, 0x3ff
/* 09E9FC 8009DDFC 304F03FF */  andi  $t7, $v0, 0x3ff
/* 09EA00 8009DE00 000FC380 */  sll   $t8, $t7, 0xe
/* 09EA04 8009DE04 000B6080 */  sll   $t4, $t3, 2
/* 09EA08 8009DE08 032D7025 */  or    $t6, $t9, $t5
/* 09EA0C 8009DE0C 00A02025 */  move  $a0, $a1
/* 09EA10 8009DE10 030CC825 */  or    $t9, $t8, $t4
/* 09EA14 8009DE14 AC990004 */  sw    $t9, 4($a0)
/* 09EA18 8009DE18 AC8E0000 */  sw    $t6, ($a0)
/* 09EA1C 8009DE1C 14C00002 */  bnez  $a2, .L8009DE28
/* 09EA20 8009DE20 00000000 */   nop   
/* 09EA24 8009DE24 0007000D */  break 7
.L8009DE28:
/* 09EA28 8009DE28 2401FFFF */  li    $at, -1
/* 09EA2C 8009DE2C 14C10004 */  bne   $a2, $at, .L8009DE40
/* 09EA30 8009DE30 3C018000 */   lui   $at, 0x8000
/* 09EA34 8009DE34 16010002 */  bne   $s0, $at, .L8009DE40
/* 09EA38 8009DE38 00000000 */   nop   
/* 09EA3C 8009DE3C 0006000D */  break 6
.L8009DE40:
/* 09EA40 8009DE40 26100001 */  addiu $s0, $s0, 1
.L8009DE44:
/* 09EA44 8009DE44 5607FFD7 */  bnel  $s0, $a3, .L8009DDA4
/* 09EA48 8009DE48 8E4F0000 */   lw    $t7, ($s2)
/* 09EA4C 8009DE4C 8E250000 */  lw    $a1, ($s1)
/* 09EA50 8009DE50 3C0B8019 */  lui   $t3, %hi(D_8018E7C8) # $t3, 0x8019
/* 09EA54 8009DE54 00003025 */  move  $a2, $zero
/* 09EA58 8009DE58 24AD0008 */  addiu $t5, $a1, 8
/* 09EA5C 8009DE5C AE2D0000 */  sw    $t5, ($s1)
/* 09EA60 8009DE60 ACA00004 */  sw    $zero, 4($a1)
/* 09EA64 8009DE64 ACA90000 */  sw    $t1, ($a1)
/* 09EA68 8009DE68 8EAE0010 */  lw    $t6, 0x10($s5)
/* 09EA6C 8009DE6C 8D6BE7C8 */  lw    $t3, %lo(D_8018E7C8)($t3)
/* 09EA70 8009DE70 00A01025 */  move  $v0, $a1
/* 09EA74 8009DE74 01CA0019 */  multu $t6, $t2
/* 09EA78 8009DE78 00002825 */  move  $a1, $zero
/* 09EA7C 8009DE7C 24070140 */  li    $a3, 320
/* 09EA80 8009DE80 241800F0 */  li    $t8, 240
/* 09EA84 8009DE84 00007812 */  mflo  $t7
/* 09EA88 8009DE88 00000000 */  nop   
/* 09EA8C 8009DE8C 00000000 */  nop   
/* 09EA90 8009DE90 01EB001B */  divu  $zero, $t7, $t3
/* 09EA94 8009DE94 00001812 */  mflo  $v1
/* 09EA98 8009DE98 28610100 */  slti  $at, $v1, 0x100
/* 09EA9C 8009DE9C 15600002 */  bnez  $t3, .L8009DEA8
/* 09EAA0 8009DEA0 00000000 */   nop   
/* 09EAA4 8009DEA4 0007000D */  break 7
.L8009DEA8:
/* 09EAA8 8009DEA8 54200003 */  bnel  $at, $zero, .L8009DEB8
/* 09EAAC 8009DEAC 8E240000 */   lw    $a0, ($s1)
/* 09EAB0 8009DEB0 240300FF */  li    $v1, 255
/* 09EAB4 8009DEB4 8E240000 */  lw    $a0, ($s1)
.L8009DEB8:
/* 09EAB8 8009DEB8 AFB80010 */  sw    $t8, 0x10($sp)
/* 09EABC 8009DEBC AFA00014 */  sw    $zero, 0x14($sp)
/* 09EAC0 8009DEC0 AFA00018 */  sw    $zero, 0x18($sp)
/* 09EAC4 8009DEC4 AFA0001C */  sw    $zero, 0x1c($sp)
/* 09EAC8 8009DEC8 0C02637E */  jal   draw_box
/* 09EACC 8009DECC AFA30020 */   sw    $v1, 0x20($sp)
/* 09EAD0 8009DED0 8FBF0044 */  lw    $ra, 0x44($sp)
/* 09EAD4 8009DED4 AE220000 */  sw    $v0, ($s1)
/* 09EAD8 8009DED8 8FB10030 */  lw    $s1, 0x30($sp)
/* 09EADC 8009DEDC 8FB0002C */  lw    $s0, 0x2c($sp)
/* 09EAE0 8009DEE0 8FB20034 */  lw    $s2, 0x34($sp)
/* 09EAE4 8009DEE4 8FB30038 */  lw    $s3, 0x38($sp)
/* 09EAE8 8009DEE8 8FB4003C */  lw    $s4, 0x3c($sp)
/* 09EAEC 8009DEEC 8FB50040 */  lw    $s5, 0x40($sp)
/* 09EAF0 8009DEF0 03E00008 */  jr    $ra
/* 09EAF4 8009DEF4 27BD0048 */   addiu $sp, $sp, 0x48