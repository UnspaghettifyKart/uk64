glabel func_80097274
/* 097E74 80097274 27BDFEF0 */  addiu $sp, $sp, -0x110
/* 097E78 80097278 AFB00018 */  sw    $s0, 0x18($sp)
/* 097E7C 8009727C AFBF003C */  sw    $ra, 0x3c($sp)
/* 097E80 80097280 AFBE0038 */  sw    $fp, 0x38($sp)
/* 097E84 80097284 AFB70034 */  sw    $s7, 0x34($sp)
/* 097E88 80097288 AFB60030 */  sw    $s6, 0x30($sp)
/* 097E8C 8009728C AFB5002C */  sw    $s5, 0x2c($sp)
/* 097E90 80097290 AFB40028 */  sw    $s4, 0x28($sp)
/* 097E94 80097294 AFB30024 */  sw    $s3, 0x24($sp)
/* 097E98 80097298 AFB20020 */  sw    $s2, 0x20($sp)
/* 097E9C 8009729C AFB1001C */  sw    $s1, 0x1c($sp)
/* 097EA0 800972A0 AFA50114 */  sw    $a1, 0x114($sp)
/* 097EA4 800972A4 AFA60118 */  sw    $a2, 0x118($sp)
/* 097EA8 800972A8 AFA7011C */  sw    $a3, 0x11c($sp)
/* 097EAC 800972AC 24900008 */  addiu $s0, $a0, 8
/* 097EB0 800972B0 3C0EE700 */  lui   $t6, 0xe700
/* 097EB4 800972B4 AC8E0000 */  sw    $t6, ($a0)
/* 097EB8 800972B8 02001825 */  move  $v1, $s0
/* 097EBC 800972BC 3C0FBA00 */  lui   $t7, (0xBA001402 >> 16) # lui $t7, 0xba00
/* 097EC0 800972C0 AC800004 */  sw    $zero, 4($a0)
/* 097EC4 800972C4 35EF1402 */  ori   $t7, (0xBA001402 & 0xFFFF) # ori $t7, $t7, 0x1402
/* 097EC8 800972C8 26100008 */  addiu $s0, $s0, 8
/* 097ECC 800972CC AC6F0000 */  sw    $t7, ($v1)
/* 097ED0 800972D0 3C180010 */  lui   $t8, %hi(D_000FFF00) # $t8, 0x10
/* 097ED4 800972D4 02004825 */  move  $t1, $s0
/* 097ED8 800972D8 AC780004 */  sw    $t8, 4($v1)
/* 097EDC 800972DC 3C19BA00 */  lui   $t9, (0xBA001001 >> 16) # lui $t9, 0xba00
/* 097EE0 800972E0 37391001 */  ori   $t9, (0xBA001001 & 0xFFFF) # ori $t9, $t9, 0x1001
/* 097EE4 800972E4 26100008 */  addiu $s0, $s0, 8
/* 097EE8 800972E8 AD390000 */  sw    $t9, ($t1)
/* 097EEC 800972EC AD200004 */  sw    $zero, 4($t1)
/* 097EF0 800972F0 02005025 */  move  $t2, $s0
/* 097EF4 800972F4 3C0EFA00 */  lui   $t6, 0xfa00
/* 097EF8 800972F8 AD4E0000 */  sw    $t6, ($t2)
/* 097EFC 800972FC 3C0F800E */  lui   $t7, %hi(gGlobalTimer) # $t7, 0x800e
/* 097F00 80097300 8DEFC54C */  lw    $t7, %lo(gGlobalTimer)($t7)
/* 097F04 80097304 26100008 */  addiu $s0, $s0, 8
/* 097F08 80097308 02006825 */  move  $t5, $s0
/* 097F0C 8009730C 3C0EFC25 */  lui   $t6, (0xFC2527FF >> 16) # lui $t6, 0xfc25
/* 097F10 80097310 35CE27FF */  ori   $t6, (0xFC2527FF & 0xFFFF) # ori $t6, $t6, 0x27ff
/* 097F14 80097314 00801025 */  move  $v0, $a0
/* 097F18 80097318 24080001 */  li    $t0, 1
/* 097F1C 8009731C 00005825 */  move  $t3, $zero
/* 097F20 80097320 00006025 */  move  $t4, $zero
/* 097F24 80097324 05E10004 */  bgez  $t7, .L80097338
/* 097F28 80097328 31F800FF */   andi  $t8, $t7, 0xff
/* 097F2C 8009732C 13000002 */  beqz  $t8, .L80097338
/* 097F30 80097330 00000000 */   nop   
/* 097F34 80097334 2718FF00 */  addiu $t8, %lo(D_000FFF00) # addiu $t8, $t8, -0x100
.L80097338:
/* 097F38 80097338 331900FF */  andi  $t9, $t8, 0xff
/* 097F3C 8009733C AD590004 */  sw    $t9, 4($t2)
/* 097F40 80097340 3C0F1FFC */  lui   $t7, (0x1FFC9238 >> 16) # lui $t7, 0x1ffc
/* 097F44 80097344 35EF9238 */  ori   $t7, (0x1FFC9238 & 0xFFFF) # ori $t7, $t7, 0x9238
/* 097F48 80097348 ADAF0004 */  sw    $t7, 4($t5)
/* 097F4C 8009734C ADAE0000 */  sw    $t6, ($t5)
/* 097F50 80097350 8FB8013C */  lw    $t8, 0x13c($sp)
/* 097F54 80097354 26100008 */  addiu $s0, $s0, 8
/* 097F58 80097358 8FA40140 */  lw    $a0, 0x140($sp)
/* 097F5C 8009735C 2F010002 */  sltiu $at, $t8, 2
/* 097F60 80097360 14200007 */  bnez  $at, .L80097380
/* 097F64 80097364 240F0400 */   li    $t7, 1024
/* 097F68 80097368 8FAE013C */  lw    $t6, 0x13c($sp)
.L8009736C:
/* 097F6C 8009736C 0008C840 */  sll   $t9, $t0, 1
/* 097F70 80097370 03204025 */  move  $t0, $t9
/* 097F74 80097374 032E082B */  sltu  $at, $t9, $t6
/* 097F78 80097378 5420FFFC */  bnel  $at, $zero, .L8009736C
/* 097F7C 8009737C 8FAE013C */   lw    $t6, 0x13c($sp)
.L80097380:
/* 097F80 80097380 01E8001A */  div   $zero, $t7, $t0
/* 097F84 80097384 15000002 */  bnez  $t0, .L80097390
/* 097F88 80097388 00000000 */   nop   
/* 097F8C 8009738C 0007000D */  break 7
.L80097390:
/* 097F90 80097390 2401FFFF */  li    $at, -1
/* 097F94 80097394 15010004 */  bne   $t0, $at, .L800973A8
/* 097F98 80097398 3C018000 */   lui   $at, 0x8000
/* 097F9C 8009739C 15E10002 */  bne   $t7, $at, .L800973A8
/* 097FA0 800973A0 00000000 */   nop   
/* 097FA4 800973A4 0006000D */  break 6
.L800973A8:
/* 097FA8 800973A8 00001012 */  mflo  $v0
/* 097FAC 800973AC AFA200F4 */  sw    $v0, 0xf4($sp)
/* 097FB0 800973B0 04410003 */  bgez  $v0, .L800973C0
/* 097FB4 800973B4 0002C043 */   sra   $t8, $v0, 1
/* 097FB8 800973B8 24410001 */  addiu $at, $v0, 1
/* 097FBC 800973BC 0001C043 */  sra   $t8, $at, 1
.L800973C0:
/* 097FC0 800973C0 0098082B */  sltu  $at, $a0, $t8
/* 097FC4 800973C4 1020000F */  beqz  $at, .L80097404
/* 097FC8 800973C8 8FA200F4 */   lw    $v0, 0xf4($sp)
/* 097FCC 800973CC 04410003 */  bgez  $v0, .L800973DC
/* 097FD0 800973D0 0002C843 */   sra   $t9, $v0, 1
/* 097FD4 800973D4 24410001 */  addiu $at, $v0, 1
/* 097FD8 800973D8 0001C843 */  sra   $t9, $at, 1
.L800973DC:
/* 097FDC 800973DC 03201025 */  move  $v0, $t9
/* 097FE0 800973E0 00401825 */  move  $v1, $v0
.L800973E4:
/* 097FE4 800973E4 04610003 */  bgez  $v1, .L800973F4
/* 097FE8 800973E8 00031043 */   sra   $v0, $v1, 1
/* 097FEC 800973EC 24610001 */  addiu $at, $v1, 1
/* 097FF0 800973F0 00011043 */  sra   $v0, $at, 1
.L800973F4:
/* 097FF4 800973F4 0082082B */  sltu  $at, $a0, $v0
/* 097FF8 800973F8 5420FFFA */  bnel  $at, $zero, .L800973E4
/* 097FFC 800973FC 00401825 */   move  $v1, $v0
/* 098000 80097400 AFA300F4 */  sw    $v1, 0xf4($sp)
.L80097404:
/* 098004 80097404 29010002 */  slti  $at, $t0, 2
/* 098008 80097408 14200009 */  bnez  $at, .L80097430
/* 09800C 8009740C 01001025 */   move  $v0, $t0
.L80097410:
/* 098010 80097410 04410003 */  bgez  $v0, .L80097420
/* 098014 80097414 00027043 */   sra   $t6, $v0, 1
/* 098018 80097418 24410001 */  addiu $at, $v0, 1
/* 09801C 8009741C 00017043 */  sra   $t6, $at, 1
.L80097420:
/* 098020 80097420 29C10002 */  slti  $at, $t6, 2
/* 098024 80097424 01C01025 */  move  $v0, $t6
/* 098028 80097428 1020FFF9 */  beqz  $at, .L80097410
/* 09802C 8009742C 256B0001 */   addiu $t3, $t3, 1
.L80097430:
/* 098030 80097430 8FA200F4 */  lw    $v0, 0xf4($sp)
/* 098034 80097434 8FA40130 */  lw    $a0, 0x130($sp)
/* 098038 80097438 8FB90120 */  lw    $t9, 0x120($sp)
/* 09803C 8009743C 28410002 */  slti  $at, $v0, 2
/* 098040 80097440 14200009 */  bnez  $at, .L80097468
/* 098044 80097444 8FAF0128 */   lw    $t7, 0x128($sp)
.L80097448:
/* 098048 80097448 04410003 */  bgez  $v0, .L80097458
/* 09804C 8009744C 0002C043 */   sra   $t8, $v0, 1
/* 098050 80097450 24410001 */  addiu $at, $v0, 1
/* 098054 80097454 0001C043 */  sra   $t8, $at, 1
.L80097458:
/* 098058 80097458 2B010002 */  slti  $at, $t8, 2
/* 09805C 8009745C 03001025 */  move  $v0, $t8
/* 098060 80097460 1020FFF9 */  beqz  $at, .L80097448
/* 098064 80097464 258C0001 */   addiu $t4, $t4, 1
.L80097468:
/* 098068 80097468 04810005 */  bgez  $a0, .L80097480
/* 09806C 8009746C 8FA20120 */   lw    $v0, 0x120($sp)
/* 098070 80097470 03247023 */  subu  $t6, $t9, $a0
/* 098074 80097474 AFAE0120 */  sw    $t6, 0x120($sp)
/* 098078 80097478 10000008 */  b     .L8009749C
/* 09807C 8009747C 00002025 */   move  $a0, $zero
.L80097480:
/* 098080 80097480 01E2C023 */  subu  $t8, $t7, $v0
/* 098084 80097484 0304C821 */  addu  $t9, $t8, $a0
/* 098088 80097488 2B210141 */  slti  $at, $t9, 0x141
/* 09808C 8009748C 14200003 */  bnez  $at, .L8009749C
/* 098090 80097490 00441823 */   subu  $v1, $v0, $a0
/* 098094 80097494 24630140 */  addiu $v1, $v1, 0x140
/* 098098 80097498 AFA30128 */  sw    $v1, 0x128($sp)
.L8009749C:
/* 09809C 8009749C 8FAE0134 */  lw    $t6, 0x134($sp)
/* 0980A0 800974A0 8FA30128 */  lw    $v1, 0x128($sp)
/* 0980A4 800974A4 8FA20124 */  lw    $v0, 0x124($sp)
/* 0980A8 800974A8 05C10005 */  bgez  $t6, .L800974C0
/* 0980AC 800974AC 8FAF012C */   lw    $t7, 0x12c($sp)
/* 0980B0 800974B0 8FA20124 */  lw    $v0, 0x124($sp)
/* 0980B4 800974B4 AFA00134 */  sw    $zero, 0x134($sp)
/* 0980B8 800974B8 10000009 */  b     .L800974E0
/* 0980BC 800974BC 004E1023 */   subu  $v0, $v0, $t6
.L800974C0:
/* 0980C0 800974C0 8FB90134 */  lw    $t9, 0x134($sp)
/* 0980C4 800974C4 01E2C023 */  subu  $t8, $t7, $v0
/* 0980C8 800974C8 03197021 */  addu  $t6, $t8, $t9
/* 0980CC 800974CC 29C100F1 */  slti  $at, $t6, 0xf1
/* 0980D0 800974D0 14200003 */  bnez  $at, .L800974E0
/* 0980D4 800974D4 00597823 */   subu  $t7, $v0, $t9
/* 0980D8 800974D8 25F800F0 */  addiu $t8, $t7, 0xf0
/* 0980DC 800974DC AFB8012C */  sw    $t8, 0x12c($sp)
.L800974E0:
/* 0980E0 800974E0 8FAE0120 */  lw    $t6, 0x120($sp)
/* 0980E4 800974E4 8FB9012C */  lw    $t9, 0x12c($sp)
/* 0980E8 800974E8 006E082A */  slt   $at, $v1, $t6
/* 0980EC 800974EC 50200004 */  beql  $at, $zero, .L80097500
/* 0980F0 800974F0 0322082A */   slt   $at, $t9, $v0
/* 0980F4 800974F4 1000013B */  b     .L800979E4
/* 0980F8 800974F8 02001025 */   move  $v0, $s0
/* 0980FC 800974FC 0322082A */  slt   $at, $t9, $v0
.L80097500:
/* 098100 80097500 50200004 */  beql  $at, $zero, .L80097514
/* 098104 80097504 8FAF012C */   lw    $t7, 0x12c($sp)
/* 098108 80097508 10000136 */  b     .L800979E4
/* 09810C 8009750C 02001025 */   move  $v0, $s0
/* 098110 80097510 8FAF012C */  lw    $t7, 0x12c($sp)
.L80097514:
/* 098114 80097514 AFA40104 */  sw    $a0, 0x104($sp)
/* 098118 80097518 00406825 */  move  $t5, $v0
/* 09811C 8009751C 004F082B */  sltu  $at, $v0, $t7
/* 098120 80097520 50200128 */  beql  $at, $zero, .L800979C4
/* 098124 80097524 26040008 */   addiu $a0, $s0, 8
/* 098128 80097528 AFA40130 */  sw    $a0, 0x130($sp)
/* 09812C 8009752C AFA800F8 */  sw    $t0, 0xf8($sp)
/* 098130 80097530 AFAB00F0 */  sw    $t3, 0xf0($sp)
/* 098134 80097534 AFAC00EC */  sw    $t4, 0xec($sp)
.L80097538:
/* 098138 80097538 8FB800F4 */  lw    $t8, 0xf4($sp)
/* 09813C 8009753C 8FB9012C */  lw    $t9, 0x12c($sp)
/* 098140 80097540 8FAF00F4 */  lw    $t7, 0xf4($sp)
/* 098144 80097544 030D7021 */  addu  $t6, $t8, $t5
/* 098148 80097548 032E082B */  sltu  $at, $t9, $t6
/* 09814C 8009754C 10200006 */  beqz  $at, .L80097568
/* 098150 80097550 AFAE0084 */   sw    $t6, 0x84($sp)
/* 098154 80097554 032D1023 */  subu  $v0, $t9, $t5
/* 098158 80097558 10400119 */  beqz  $v0, .L800979C0
/* 09815C 8009755C AFA200FC */   sw    $v0, 0xfc($sp)
/* 098160 80097560 10000003 */  b     .L80097570
/* 098164 80097564 8FB40120 */   lw    $s4, 0x120($sp)
.L80097568:
/* 098168 80097568 AFAF00FC */  sw    $t7, 0xfc($sp)
/* 09816C 8009756C 8FB40120 */  lw    $s4, 0x120($sp)
.L80097570:
/* 098170 80097570 8FB80120 */  lw    $t8, 0x120($sp)
/* 098174 80097574 0303082B */  sltu  $at, $t8, $v1
/* 098178 80097578 50200108 */  beql  $at, $zero, .L8009799C
/* 09817C 8009757C 8FB80104 */   lw    $t8, 0x104($sp)
/* 098180 80097580 AFA30128 */  sw    $v1, 0x128($sp)
.L80097584:
/* 098184 80097584 8FAE00F8 */  lw    $t6, 0xf8($sp)
/* 098188 80097588 8FA30128 */  lw    $v1, 0x128($sp)
/* 09818C 8009758C 8FA800FC */  lw    $t0, 0xfc($sp)
/* 098190 80097590 01D4C821 */  addu  $t9, $t6, $s4
/* 098194 80097594 0079082B */  sltu  $at, $v1, $t9
/* 098198 80097598 1020003A */  beqz  $at, .L80097684
/* 09819C 8009759C AFB90080 */   sw    $t9, 0x80($sp)
/* 0981A0 800975A0 00745823 */  subu  $t3, $v1, $s4
/* 0981A4 800975A4 116000FC */  beqz  $t3, .L80097998
/* 0981A8 800975A8 3C01FD00 */   lui   $at, 0xfd00
/* 0981AC 800975AC 83A40117 */  lb    $a0, 0x117($sp)
/* 0981B0 800975B0 8FA200EC */  lw    $v0, 0xec($sp)
/* 0981B4 800975B4 AFA30128 */  sw    $v1, 0x128($sp)
/* 0981B8 800975B8 308F0007 */  andi  $t7, $a0, 7
/* 0981BC 800975BC 000F2540 */  sll   $a0, $t7, 0x15
/* 0981C0 800975C0 8FAF013C */  lw    $t7, 0x13c($sp)
/* 0981C4 800975C4 00817025 */  or    $t6, $a0, $at
/* 0981C8 800975C8 3C010010 */  lui   $at, 0x10
/* 0981CC 800975CC 01C1C825 */  or    $t9, $t6, $at
/* 0981D0 800975D0 3C01F500 */  lui   $at, 0xf500
/* 0981D4 800975D4 25F8FFFF */  addiu $t8, $t7, -1
/* 0981D8 800975D8 8FA300F0 */  lw    $v1, 0xf0($sp)
/* 0981DC 800975DC 330E0FFF */  andi  $t6, $t8, 0xfff
/* 0981E0 800975E0 00813825 */  or    $a3, $a0, $at
/* 0981E4 800975E4 8FA800FC */  lw    $t0, 0xfc($sp)
/* 0981E8 800975E8 3C010010 */  lui   $at, 0x10
/* 0981EC 800975EC 00E17825 */  or    $t7, $a3, $at
/* 0981F0 800975F0 032E2825 */  or    $a1, $t9, $t6
/* 0981F4 800975F4 3058000F */  andi  $t8, $v0, 0xf
/* 0981F8 800975F8 8FA90134 */  lw    $t1, 0x134($sp)
/* 0981FC 800975FC 00181380 */  sll   $v0, $t8, 0xe
/* 098200 80097600 3C010700 */  lui   $at, 0x700
/* 098204 80097604 000D3080 */  sll   $a2, $t5, 2
/* 098208 80097608 306E000F */  andi  $t6, $v1, 0xf
/* 09820C 8009760C 000E1900 */  sll   $v1, $t6, 4
/* 098210 80097610 30D90FFF */  andi  $t9, $a2, 0xfff
/* 098214 80097614 0041C025 */  or    $t8, $v0, $at
/* 098218 80097618 01A89821 */  addu  $s3, $t5, $t0
/* 09821C 8009761C 00137080 */  sll   $t6, $s3, 2
/* 098220 80097620 03203025 */  move  $a2, $t9
/* 098224 80097624 31D30FFF */  andi  $s3, $t6, 0xfff
/* 098228 80097628 03036025 */  or    $t4, $t8, $v1
/* 09822C 8009762C 3C010100 */  lui   $at, 0x100
/* 098230 80097630 0128C821 */  addu  $t9, $t1, $t0
/* 098234 80097634 00197080 */  sll   $t6, $t9, 2
/* 098238 80097638 0041C025 */  or    $t8, $v0, $at
/* 09823C 8009763C 01E03825 */  move  $a3, $t7
/* 098240 80097640 31CF0FFF */  andi  $t7, $t6, 0xfff
/* 098244 80097644 0303F825 */  or    $ra, $t8, $v1
/* 098248 80097648 AFAF004C */  sw    $t7, 0x4c($sp)
/* 09824C 8009764C 0009C080 */  sll   $t8, $t1, 2
/* 098250 80097650 33190FFF */  andi  $t9, $t8, 0xfff
/* 098254 80097654 000D7940 */  sll   $t7, $t5, 5
/* 098258 80097658 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 09825C 8009765C AFB80044 */  sw    $t8, 0x44($sp)
/* 098260 80097660 8FB8011C */  lw    $t8, 0x11c($sp)
/* 098264 80097664 8FAE0118 */  lw    $t6, 0x118($sp)
/* 098268 80097668 AFB90048 */  sw    $t9, 0x48($sp)
/* 09826C 8009766C 3319FFFF */  andi  $t9, $t8, 0xffff
/* 098270 80097670 000E7C00 */  sll   $t7, $t6, 0x10
/* 098274 80097674 01F97025 */  or    $t6, $t7, $t9
/* 098278 80097678 AFAE0040 */  sw    $t6, 0x40($sp)
/* 09827C 8009767C 10000036 */  b     .L80097758
/* 098280 80097680 00435025 */   or    $t2, $v0, $v1
.L80097684:
/* 098284 80097684 83A40117 */  lb    $a0, 0x117($sp)
/* 098288 80097688 3C01FD00 */  lui   $at, 0xfd00
/* 09828C 8009768C 8FA200EC */  lw    $v0, 0xec($sp)
/* 098290 80097690 30980007 */  andi  $t8, $a0, 7
/* 098294 80097694 00182540 */  sll   $a0, $t8, 0x15
/* 098298 80097698 8FB8013C */  lw    $t8, 0x13c($sp)
/* 09829C 8009769C 0081C825 */  or    $t9, $a0, $at
/* 0982A0 800976A0 3C010010 */  lui   $at, 0x10
/* 0982A4 800976A4 03217025 */  or    $t6, $t9, $at
/* 0982A8 800976A8 3C01F500 */  lui   $at, 0xf500
/* 0982AC 800976AC 270FFFFF */  addiu $t7, $t8, -1
/* 0982B0 800976B0 8FA300F0 */  lw    $v1, 0xf0($sp)
/* 0982B4 800976B4 31F90FFF */  andi  $t9, $t7, 0xfff
/* 0982B8 800976B8 00813825 */  or    $a3, $a0, $at
/* 0982BC 800976BC 3C010010 */  lui   $at, 0x10
/* 0982C0 800976C0 00E1C025 */  or    $t8, $a3, $at
/* 0982C4 800976C4 01D92825 */  or    $a1, $t6, $t9
/* 0982C8 800976C8 304F000F */  andi  $t7, $v0, 0xf
/* 0982CC 800976CC 8FA90134 */  lw    $t1, 0x134($sp)
/* 0982D0 800976D0 000F1380 */  sll   $v0, $t7, 0xe
/* 0982D4 800976D4 3C010700 */  lui   $at, 0x700
/* 0982D8 800976D8 000D3080 */  sll   $a2, $t5, 2
/* 0982DC 800976DC 3079000F */  andi  $t9, $v1, 0xf
/* 0982E0 800976E0 00191900 */  sll   $v1, $t9, 4
/* 0982E4 800976E4 30CE0FFF */  andi  $t6, $a2, 0xfff
/* 0982E8 800976E8 00417825 */  or    $t7, $v0, $at
/* 0982EC 800976EC 01A89821 */  addu  $s3, $t5, $t0
/* 0982F0 800976F0 0013C880 */  sll   $t9, $s3, 2
/* 0982F4 800976F4 01C03025 */  move  $a2, $t6
/* 0982F8 800976F8 33330FFF */  andi  $s3, $t9, 0xfff
/* 0982FC 800976FC 01E36025 */  or    $t4, $t7, $v1
/* 098300 80097700 3C010100 */  lui   $at, 0x100
/* 098304 80097704 01287021 */  addu  $t6, $t1, $t0
/* 098308 80097708 000EC880 */  sll   $t9, $t6, 2
/* 09830C 8009770C 00417825 */  or    $t7, $v0, $at
/* 098310 80097710 03003825 */  move  $a3, $t8
/* 098314 80097714 33380FFF */  andi  $t8, $t9, 0xfff
/* 098318 80097718 01E3F825 */  or    $ra, $t7, $v1
/* 09831C 8009771C AFB8004C */  sw    $t8, 0x4c($sp)
/* 098320 80097720 00097880 */  sll   $t7, $t1, 2
/* 098324 80097724 31EE0FFF */  andi  $t6, $t7, 0xfff
/* 098328 80097728 000DC140 */  sll   $t8, $t5, 5
/* 09832C 8009772C 330FFFFF */  andi  $t7, $t8, 0xffff
/* 098330 80097730 AFAF0044 */  sw    $t7, 0x44($sp)
/* 098334 80097734 8FAF011C */  lw    $t7, 0x11c($sp)
/* 098338 80097738 8FB90118 */  lw    $t9, 0x118($sp)
/* 09833C 8009773C AFAE0048 */  sw    $t6, 0x48($sp)
/* 098340 80097740 31EEFFFF */  andi  $t6, $t7, 0xffff
/* 098344 80097744 0019C400 */  sll   $t8, $t9, 0x10
/* 098348 80097748 030EC825 */  or    $t9, $t8, $t6
/* 09834C 8009774C AFB90040 */  sw    $t9, 0x40($sp)
/* 098350 80097750 00435025 */  or    $t2, $v0, $v1
/* 098354 80097754 8FAB00F8 */  lw    $t3, 0xf8($sp)
.L80097758:
/* 098358 80097758 02001025 */  move  $v0, $s0
/* 09835C 8009775C AC450000 */  sw    $a1, ($v0)
/* 098360 80097760 8FAF0138 */  lw    $t7, 0x138($sp)
/* 098364 80097764 028B2021 */  addu  $a0, $s4, $t3
/* 098368 80097768 0094C023 */  subu  $t8, $a0, $s4
/* 09836C 8009776C 00187040 */  sll   $t6, $t8, 1
/* 098370 80097770 25D90009 */  addiu $t9, $t6, 9
/* 098374 80097774 AC4F0004 */  sw    $t7, 4($v0)
/* 098378 80097778 001978C2 */  srl   $t7, $t9, 3
/* 09837C 8009777C 31F801FF */  andi  $t8, $t7, 0x1ff
/* 098380 80097780 26100008 */  addiu $s0, $s0, 8
/* 098384 80097784 02001825 */  move  $v1, $s0
/* 098388 80097788 00187240 */  sll   $t6, $t8, 9
/* 09838C 8009778C 00EE8825 */  or    $s1, $a3, $t6
/* 098390 80097790 00143880 */  sll   $a3, $s4, 2
/* 098394 80097794 26100008 */  addiu $s0, $s0, 8
/* 098398 80097798 02004025 */  move  $t0, $s0
/* 09839C 8009779C 30EF0FFF */  andi  $t7, $a3, 0xfff
/* 0983A0 800977A0 AC710000 */  sw    $s1, ($v1)
/* 0983A4 800977A4 AC6C0004 */  sw    $t4, 4($v1)
/* 0983A8 800977A8 3C19E600 */  lui   $t9, 0xe600
/* 0983AC 800977AC AD190000 */  sw    $t9, ($t0)
/* 0983B0 800977B0 000F3B00 */  sll   $a3, $t7, 0xc
/* 0983B4 800977B4 00049080 */  sll   $s2, $a0, 2
/* 0983B8 800977B8 3C01F400 */  lui   $at, 0xf400
/* 0983BC 800977BC 00E17025 */  or    $t6, $a3, $at
/* 0983C0 800977C0 32590FFF */  andi  $t9, $s2, 0xfff
/* 0983C4 800977C4 26100008 */  addiu $s0, $s0, 8
/* 0983C8 800977C8 02001025 */  move  $v0, $s0
/* 0983CC 800977CC 00199300 */  sll   $s2, $t9, 0xc
/* 0983D0 800977D0 3C010700 */  lui   $at, 0x700
/* 0983D4 800977D4 0241C025 */  or    $t8, $s2, $at
/* 0983D8 800977D8 AD000004 */  sw    $zero, 4($t0)
/* 0983DC 800977DC 0313B025 */  or    $s6, $t8, $s3
/* 0983E0 800977E0 26100008 */  addiu $s0, $s0, 8
/* 0983E4 800977E4 01C6A825 */  or    $s5, $t6, $a2
/* 0983E8 800977E8 AC550000 */  sw    $s5, ($v0)
/* 0983EC 800977EC 02001825 */  move  $v1, $s0
/* 0983F0 800977F0 AC560004 */  sw    $s6, 4($v0)
/* 0983F4 800977F4 26100008 */  addiu $s0, $s0, 8
/* 0983F8 800977F8 02004825 */  move  $t1, $s0
/* 0983FC 800977FC 3C0EE700 */  lui   $t6, 0xe700
/* 098400 80097800 AC6E0000 */  sw    $t6, ($v1)
/* 098404 80097804 26100008 */  addiu $s0, $s0, 8
/* 098408 80097808 AC600004 */  sw    $zero, 4($v1)
/* 09840C 8009780C 02001025 */  move  $v0, $s0
/* 098410 80097810 3C01F200 */  lui   $at, 0xf200
/* 098414 80097814 00E1C825 */  or    $t9, $a3, $at
/* 098418 80097818 AD2A0004 */  sw    $t2, 4($t1)
/* 09841C 8009781C AD310000 */  sw    $s1, ($t1)
/* 098420 80097820 0326B825 */  or    $s7, $t9, $a2
/* 098424 80097824 26100008 */  addiu $s0, $s0, 8
/* 098428 80097828 02537825 */  or    $t7, $s2, $s3
/* 09842C 8009782C AC4F0004 */  sw    $t7, 4($v0)
/* 098430 80097830 AC570000 */  sw    $s7, ($v0)
/* 098434 80097834 0200F025 */  move  $fp, $s0
/* 098438 80097838 AFC50000 */  sw    $a1, ($fp)
/* 09843C 8009783C AFBF0050 */  sw    $ra, 0x50($sp)
/* 098440 80097840 AFAD0108 */  sw    $t5, 0x108($sp)
/* 098444 80097844 AFAC0068 */  sw    $t4, 0x68($sp)
/* 098448 80097848 AFAB0100 */  sw    $t3, 0x100($sp)
/* 09844C 8009784C 26100008 */  addiu $s0, $s0, 8
/* 098450 80097850 0C0ADF8D */  jal   random_int
/* 098454 80097854 24040080 */   li    $a0, 128
/* 098458 80097858 3C0E0B00 */  lui   $t6, %hi(D_0B002A00) # $t6, 0xb00
/* 09845C 8009785C 8FAC0068 */  lw    $t4, 0x68($sp)
/* 098460 80097860 25CE2A00 */  addiu $t6, %lo(D_0B002A00) # addiu $t6, $t6, 0x2a00
/* 098464 80097864 0002C040 */  sll   $t8, $v0, 1
/* 098468 80097868 8FAB0100 */  lw    $t3, 0x100($sp)
/* 09846C 8009786C 8FBF0050 */  lw    $ra, 0x50($sp)
/* 098470 80097870 030EC821 */  addu  $t9, $t8, $t6
/* 098474 80097874 8FAD0108 */  lw    $t5, 0x108($sp)
/* 098478 80097878 02001825 */  move  $v1, $s0
/* 09847C 8009787C AFD90004 */  sw    $t9, 4($fp)
/* 098480 80097880 26100008 */  addiu $s0, $s0, 8
/* 098484 80097884 36250100 */  ori   $a1, $s1, 0x100
/* 098488 80097888 AC650000 */  sw    $a1, ($v1)
/* 09848C 8009788C 02002025 */  move  $a0, $s0
/* 098490 80097890 AC6C0004 */  sw    $t4, 4($v1)
/* 098494 80097894 26100008 */  addiu $s0, $s0, 8
/* 098498 80097898 02003025 */  move  $a2, $s0
/* 09849C 8009789C 3C0FE600 */  lui   $t7, 0xe600
/* 0984A0 800978A0 AC8F0000 */  sw    $t7, ($a0)
/* 0984A4 800978A4 26100008 */  addiu $s0, $s0, 8
/* 0984A8 800978A8 AC800004 */  sw    $zero, 4($a0)
/* 0984AC 800978AC 02001025 */  move  $v0, $s0
/* 0984B0 800978B0 ACD60004 */  sw    $s6, 4($a2)
/* 0984B4 800978B4 ACD50000 */  sw    $s5, ($a2)
/* 0984B8 800978B8 26100008 */  addiu $s0, $s0, 8
/* 0984BC 800978BC 3C18E700 */  lui   $t8, 0xe700
/* 0984C0 800978C0 AC580000 */  sw    $t8, ($v0)
/* 0984C4 800978C4 02001825 */  move  $v1, $s0
/* 0984C8 800978C8 AC400004 */  sw    $zero, 4($v0)
/* 0984CC 800978CC AC650000 */  sw    $a1, ($v1)
/* 0984D0 800978D0 AC7F0004 */  sw    $ra, 4($v1)
/* 0984D4 800978D4 8FA50130 */  lw    $a1, 0x130($sp)
/* 0984D8 800978D8 3C010100 */  lui   $at, 0x100
/* 0984DC 800978DC 02417025 */  or    $t6, $s2, $at
/* 0984E0 800978E0 26100008 */  addiu $s0, $s0, 8
/* 0984E4 800978E4 02002025 */  move  $a0, $s0
/* 0984E8 800978E8 01D3C825 */  or    $t9, $t6, $s3
/* 0984EC 800978EC 00AB7821 */  addu  $t7, $a1, $t3
/* 0984F0 800978F0 000FC080 */  sll   $t8, $t7, 2
/* 0984F4 800978F4 AC990004 */  sw    $t9, 4($a0)
/* 0984F8 800978F8 AC970000 */  sw    $s7, ($a0)
/* 0984FC 800978FC 330E0FFF */  andi  $t6, $t8, 0xfff
/* 098500 80097900 8FB8004C */  lw    $t8, 0x4c($sp)
/* 098504 80097904 000ECB00 */  sll   $t9, $t6, 0xc
/* 098508 80097908 3C01E400 */  lui   $at, 0xe400
/* 09850C 8009790C 26100008 */  addiu $s0, $s0, 8
/* 098510 80097910 03217825 */  or    $t7, $t9, $at
/* 098514 80097914 02001025 */  move  $v0, $s0
/* 098518 80097918 01F87025 */  or    $t6, $t7, $t8
/* 09851C 8009791C AC4E0000 */  sw    $t6, ($v0)
/* 098520 80097920 8FAE0048 */  lw    $t6, 0x48($sp)
/* 098524 80097924 0005C880 */  sll   $t9, $a1, 2
/* 098528 80097928 332F0FFF */  andi  $t7, $t9, 0xfff
/* 09852C 8009792C 000FC300 */  sll   $t8, $t7, 0xc
/* 098530 80097930 26100008 */  addiu $s0, $s0, 8
/* 098534 80097934 030EC825 */  or    $t9, $t8, $t6
/* 098538 80097938 AC590004 */  sw    $t9, 4($v0)
/* 09853C 8009793C 02001825 */  move  $v1, $s0
/* 098540 80097940 3C0FB300 */  lui   $t7, 0xb300
/* 098544 80097944 AC6F0000 */  sw    $t7, ($v1)
/* 098548 80097948 8FB80044 */  lw    $t8, 0x44($sp)
/* 09854C 8009794C 00147D40 */  sll   $t7, $s4, 0x15
/* 098550 80097950 26100008 */  addiu $s0, $s0, 8
/* 098554 80097954 01F87025 */  or    $t6, $t7, $t8
/* 098558 80097958 AC6E0004 */  sw    $t6, 4($v1)
/* 09855C 8009795C 02001025 */  move  $v0, $s0
/* 098560 80097960 3C19B200 */  lui   $t9, 0xb200
/* 098564 80097964 AC590000 */  sw    $t9, ($v0)
/* 098568 80097968 8FAF0040 */  lw    $t7, 0x40($sp)
/* 09856C 8009796C 26100008 */  addiu $s0, $s0, 8
/* 098570 80097970 AC4F0004 */  sw    $t7, 4($v0)
/* 098574 80097974 8FAF0128 */  lw    $t7, 0x128($sp)
/* 098578 80097978 8FB40080 */  lw    $s4, 0x80($sp)
/* 09857C 8009797C 8FB80130 */  lw    $t8, 0x130($sp)
/* 098580 80097980 8FAE00F8 */  lw    $t6, 0xf8($sp)
/* 098584 80097984 028F082B */  sltu  $at, $s4, $t7
/* 098588 80097988 030EC821 */  addu  $t9, $t8, $t6
/* 09858C 8009798C 1420FEFD */  bnez  $at, .L80097584
/* 098590 80097990 AFB90130 */   sw    $t9, 0x130($sp)
/* 098594 80097994 01E01825 */  move  $v1, $t7
.L80097998:
/* 098598 80097998 8FB80104 */  lw    $t8, 0x104($sp)
.L8009799C:
/* 09859C 8009799C 8FAD0084 */  lw    $t5, 0x84($sp)
/* 0985A0 800979A0 8FAE0134 */  lw    $t6, 0x134($sp)
/* 0985A4 800979A4 AFB80130 */  sw    $t8, 0x130($sp)
/* 0985A8 800979A8 8FB8012C */  lw    $t8, 0x12c($sp)
/* 0985AC 800979AC 8FB900F4 */  lw    $t9, 0xf4($sp)
/* 0985B0 800979B0 01B8082B */  sltu  $at, $t5, $t8
/* 0985B4 800979B4 01D97821 */  addu  $t7, $t6, $t9
/* 0985B8 800979B8 1420FEDF */  bnez  $at, .L80097538
/* 0985BC 800979BC AFAF0134 */   sw    $t7, 0x134($sp)
.L800979C0:
/* 0985C0 800979C0 26040008 */  addiu $a0, $s0, 8
.L800979C4:
/* 0985C4 800979C4 3C0EE700 */  lui   $t6, 0xe700
/* 0985C8 800979C8 AE0E0000 */  sw    $t6, ($s0)
/* 0985CC 800979CC AE000004 */  sw    $zero, 4($s0)
/* 0985D0 800979D0 3C19BA00 */  lui   $t9, (0xBA001402 >> 16) # lui $t9, 0xba00
/* 0985D4 800979D4 37391402 */  ori   $t9, (0xBA001402 & 0xFFFF) # ori $t9, $t9, 0x1402
/* 0985D8 800979D8 AC990000 */  sw    $t9, ($a0)
/* 0985DC 800979DC AC800004 */  sw    $zero, 4($a0)
/* 0985E0 800979E0 24820008 */  addiu $v0, $a0, 8
.L800979E4:
/* 0985E4 800979E4 8FBF003C */  lw    $ra, 0x3c($sp)
/* 0985E8 800979E8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0985EC 800979EC 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0985F0 800979F0 8FB20020 */  lw    $s2, 0x20($sp)
/* 0985F4 800979F4 8FB30024 */  lw    $s3, 0x24($sp)
/* 0985F8 800979F8 8FB40028 */  lw    $s4, 0x28($sp)
/* 0985FC 800979FC 8FB5002C */  lw    $s5, 0x2c($sp)
/* 098600 80097A00 8FB60030 */  lw    $s6, 0x30($sp)
/* 098604 80097A04 8FB70034 */  lw    $s7, 0x34($sp)
/* 098608 80097A08 8FBE0038 */  lw    $fp, 0x38($sp)
/* 09860C 80097A0C 03E00008 */  jr    $ra
/* 098610 80097A10 27BD0110 */   addiu $sp, $sp, 0x110