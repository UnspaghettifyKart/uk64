glabel func_8000B140
/* 00BD40 8000B140 000478C0 */  sll   $t7, $a0, 3
/* 00BD44 8000B144 01E47823 */  subu  $t7, $t7, $a0
/* 00BD48 8000B148 000F7900 */  sll   $t7, $t7, 4
/* 00BD4C 8000B14C 01E47823 */  subu  $t7, $t7, $a0
/* 00BD50 8000B150 000F7880 */  sll   $t7, $t7, 2
/* 00BD54 8000B154 01E47823 */  subu  $t7, $t7, $a0
/* 00BD58 8000B158 3C18800F */  lui   $t8, %hi(gPlayers) # $t8, 0x800f
/* 00BD5C 8000B15C 27186990 */  addiu $t8, %lo(gPlayers) # addiu $t8, $t8, 0x6990
/* 00BD60 8000B160 000F78C0 */  sll   $t7, $t7, 3
/* 00BD64 8000B164 27BDFF00 */  addiu $sp, $sp, -0x100
/* 00BD68 8000B168 01F81821 */  addu  $v1, $t7, $t8
/* 00BD6C 8000B16C 8C6500BC */  lw    $a1, 0xbc($v1)
/* 00BD70 8000B170 AFBF003C */  sw    $ra, 0x3c($sp)
/* 00BD74 8000B174 F7BA0030 */  sdc1  $f26, 0x30($sp)
/* 00BD78 8000B178 30B90010 */  andi  $t9, $a1, 0x10
/* 00BD7C 8000B17C F7B80028 */  sdc1  $f24, 0x28($sp)
/* 00BD80 8000B180 F7B60020 */  sdc1  $f22, 0x20($sp)
/* 00BD84 8000B184 F7B40018 */  sdc1  $f20, 0x18($sp)
/* 00BD88 8000B188 1720018F */  bnez  $t9, .L8000B7C8
/* 00BD8C 8000B18C AFA40100 */   sw    $a0, 0x100($sp)
/* 00BD90 8000B190 00046840 */  sll   $t5, $a0, 1
/* 00BD94 8000B194 3C028016 */  lui   $v0, %hi(D_801630E8) # 0x8016
/* 00BD98 8000B198 004D1021 */  addu  $v0, $v0, $t5
/* 00BD9C 8000B19C 844230E8 */  lh    $v0, %lo(D_801630E8)($v0) # 0x30e8($v0)
/* 00BDA0 8000B1A0 24010001 */  li    $at, 1
/* 00BDA4 8000B1A4 AFAD005C */  sw    $t5, 0x5c($sp)
/* 00BDA8 8000B1A8 10410187 */  beq   $v0, $at, .L8000B7C8
/* 00BDAC 8000B1AC 2406FFFF */   li    $a2, -1
/* 00BDB0 8000B1B0 10C20185 */  beq   $a2, $v0, .L8000B7C8
/* 00BDB4 8000B1B4 3C0B8016 */   lui   $t3, %hi(D_80163068) # $t3, 0x8016
/* 00BDB8 8000B1B8 256B3068 */  addiu $t3, %lo(D_80163068) # addiu $t3, $t3, 0x3068
/* 00BDBC 8000B1BC 00047880 */  sll   $t7, $a0, 2
/* 00BDC0 8000B1C0 016FC021 */  addu  $t8, $t3, $t7
/* 00BDC4 8000B1C4 3C01BF80 */  li    $at, 0xBF800000 # -1.000000
/* 00BDC8 8000B1C8 AFB80054 */  sw    $t8, 0x54($sp)
/* 00BDCC 8000B1CC AFAF0058 */  sw    $t7, 0x58($sp)
/* 00BDD0 8000B1D0 4481D000 */  mtc1  $at, $f26
/* 00BDD4 8000B1D4 C7000000 */  lwc1  $f0, ($t8)
/* 00BDD8 8000B1D8 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 00BDDC 8000B1DC 461A003C */  c.lt.s $f0, $f26
/* 00BDE0 8000B1E0 00000000 */  nop   
/* 00BDE4 8000B1E4 45030179 */  bc1tl .L8000B7CC
/* 00BDE8 8000B1E8 8FBF003C */   lw    $ra, 0x3c($sp)
/* 00BDEC 8000B1EC 4481C000 */  mtc1  $at, $f24
/* 00BDF0 8000B1F0 00000000 */  nop   
/* 00BDF4 8000B1F4 4600C03C */  c.lt.s $f24, $f0
/* 00BDF8 8000B1F8 00000000 */  nop   
/* 00BDFC 8000B1FC 45030173 */  bc1tl .L8000B7CC
/* 00BE00 8000B200 8FBF003C */   lw    $ra, 0x3c($sp)
/* 00BE04 8000B204 94620254 */  lhu   $v0, 0x254($v1)
/* 00BE08 8000B208 24010005 */  li    $at, 5
/* 00BE0C 8000B20C 1041016E */  beq   $v0, $at, .L8000B7C8
/* 00BE10 8000B210 24010007 */   li    $at, 7
/* 00BE14 8000B214 1041016C */  beq   $v0, $at, .L8000B7C8
/* 00BE18 8000B218 24010004 */   li    $at, 4
/* 00BE1C 8000B21C 1041016A */  beq   $v0, $at, .L8000B7C8
/* 00BE20 8000B220 30AC0200 */   andi  $t4, $a1, 0x200
/* 00BE24 8000B224 15800168 */  bnez  $t4, .L8000B7C8
/* 00BE28 8000B228 3C014190 */   li    $at, 0x41900000 # 18.000000
/* 00BE2C 8000B22C C4640094 */  lwc1  $f4, 0x94($v1)
/* 00BE30 8000B230 44813000 */  mtc1  $at, $f6
/* 00BE34 8000B234 3C014358 */  li    $at, 0x43580000 # 216.000000
/* 00BE38 8000B238 44815000 */  mtc1  $at, $f10
/* 00BE3C 8000B23C 46062203 */  div.s $f8, $f4, $f6
/* 00BE40 8000B240 3C098016 */  lui   $t1, %hi(D_80164438) # 0x8016
/* 00BE44 8000B244 012D4821 */  addu  $t1, $t1, $t5
/* 00BE48 8000B248 85294438 */  lh    $t1, %lo(D_80164438)($t1) # 0x4438($t1)
/* 00BE4C 8000B24C 240303E8 */  li    $v1, 1000
/* 00BE50 8000B250 27A5009C */  addiu $a1, $sp, 0x9c
/* 00BE54 8000B254 27A200B0 */  addiu $v0, $sp, 0xb0
/* 00BE58 8000B258 27A400C0 */  addiu $a0, $sp, 0xc0
/* 00BE5C 8000B25C 00005025 */  move  $t2, $zero
/* 00BE60 8000B260 460A4582 */  mul.s $f22, $f8, $f10
/* 00BE64 8000B264 00000000 */  nop   
.L8000B268:
/* 00BE68 8000B268 24420002 */  addiu $v0, $v0, 2
/* 00BE6C 8000B26C 0044082B */  sltu  $at, $v0, $a0
/* 00BE70 8000B270 24A50002 */  addiu $a1, $a1, 2
/* 00BE74 8000B274 A4A6FFFE */  sh    $a2, -2($a1)
/* 00BE78 8000B278 1420FFFB */  bnez  $at, .L8000B268
/* 00BE7C 8000B27C A443FFFE */   sh    $v1, -2($v0)
/* 00BE80 8000B280 8FAE005C */  lw    $t6, 0x5c($sp)
/* 00BE84 8000B284 3C0F8016 */  lui   $t7, %hi(D_80163010) # $t7, 0x8016
/* 00BE88 8000B288 25EF3010 */  addiu $t7, %lo(D_80163010) # addiu $t7, $t7, 0x3010
/* 00BE8C 8000B28C 01CFC021 */  addu  $t8, $t6, $t7
/* 00BE90 8000B290 AFB8004C */  sw    $t8, 0x4c($sp)
/* 00BE94 8000B294 87020000 */  lh    $v0, ($t8)
/* 00BE98 8000B298 18400006 */  blez  $v0, .L8000B2B4
/* 00BE9C 8000B29C 2459FFFF */   addiu $t9, $v0, -1
/* 00BEA0 8000B2A0 1F200004 */  bgtz  $t9, .L8000B2B4
/* 00BEA4 8000B2A4 A7190000 */   sh    $t9, ($t8)
/* 00BEA8 8000B2A8 3C018016 */  lui   $at, %hi(D_80162FF8) # 0x8016
/* 00BEAC 8000B2AC 002E0821 */  addu  $at, $at, $t6
/* 00BEB0 8000B2B0 A4202FF8 */  sh    $zero, %lo(D_80162FF8)($at) # 0x2ff8($at)
.L8000B2B4:
/* 00BEB4 8000B2B4 3C0140A0 */  li    $at, 0x40A00000 # 5.000000
/* 00BEB8 8000B2B8 4481A000 */  mtc1  $at, $f20
/* 00BEBC 8000B2BC 00004025 */  move  $t0, $zero
/* 00BEC0 8000B2C0 8FAC0100 */  lw    $t4, 0x100($sp)
.L8000B2C4:
/* 00BEC4 8000B2C4 000868C0 */  sll   $t5, $t0, 3
/* 00BEC8 8000B2C8 01A86823 */  subu  $t5, $t5, $t0
/* 00BECC 8000B2CC 110C0047 */  beq   $t0, $t4, .L8000B3EC
/* 00BED0 8000B2D0 000D6900 */   sll   $t5, $t5, 4
/* 00BED4 8000B2D4 01A86823 */  subu  $t5, $t5, $t0
/* 00BED8 8000B2D8 000D6880 */  sll   $t5, $t5, 2
/* 00BEDC 8000B2DC 01A86823 */  subu  $t5, $t5, $t0
/* 00BEE0 8000B2E0 3C0F800F */  lui   $t7, %hi(gPlayers) # $t7, 0x800f
/* 00BEE4 8000B2E4 25EF6990 */  addiu $t7, %lo(gPlayers) # addiu $t7, $t7, 0x6990
/* 00BEE8 8000B2E8 000D68C0 */  sll   $t5, $t5, 3
/* 00BEEC 8000B2EC 01AF1021 */  addu  $v0, $t5, $t7
/* 00BEF0 8000B2F0 94580000 */  lhu   $t8, ($v0)
/* 00BEF4 8000B2F4 3C014190 */  li    $at, 0x41900000 # 18.000000
/* 00BEF8 8000B2F8 33198000 */  andi  $t9, $t8, 0x8000
/* 00BEFC 8000B2FC 5320003C */  beql  $t9, $zero, .L8000B3F0
/* 00BF00 8000B300 29410002 */   slti  $at, $t2, 2
/* 00BF04 8000B304 C4440094 */  lwc1  $f4, 0x94($v0)
/* 00BF08 8000B308 44813000 */  mtc1  $at, $f6
/* 00BF0C 8000B30C 3C014358 */  li    $at, 0x43580000 # 216.000000
/* 00BF10 8000B310 44815000 */  mtc1  $at, $f10
/* 00BF14 8000B314 46062203 */  div.s $f8, $f4, $f6
/* 00BF18 8000B318 00087040 */  sll   $t6, $t0, 1
/* 00BF1C 8000B31C 3C038016 */  lui   $v1, %hi(D_80164438) # 0x8016
/* 00BF20 8000B320 006E1821 */  addu  $v1, $v1, $t6
/* 00BF24 8000B324 4614B081 */  sub.s $f2, $f22, $f20
/* 00BF28 8000B328 84634438 */  lh    $v1, %lo(D_80164438)($v1) # 0x4438($v1)
/* 00BF2C 8000B32C 3125FFFF */  andi  $a1, $t1, 0xffff
/* 00BF30 8000B330 00003025 */  move  $a2, $zero
/* 00BF34 8000B334 24070014 */  li    $a3, 20
/* 00BF38 8000B338 3C0C8016 */  lui   $t4, %hi(D_80164430) # $t4, 0x8016
/* 00BF3C 8000B33C 3064FFFF */  andi  $a0, $v1, 0xffff
/* 00BF40 8000B340 460A4002 */  mul.s $f0, $f8, $f10
/* 00BF44 8000B344 4602003C */  c.lt.s $f0, $f2
/* 00BF48 8000B348 00000000 */  nop   
/* 00BF4C 8000B34C 45020028 */  bc1fl .L8000B3F0
/* 00BF50 8000B350 29410002 */   slti  $at, $t2, 2
/* 00BF54 8000B354 958C4430 */  lhu   $t4, %lo(D_80164430)($t4)
/* 00BF58 8000B358 A7A300E4 */  sh    $v1, 0xe4($sp)
/* 00BF5C 8000B35C AFA800FC */  sw    $t0, 0xfc($sp)
/* 00BF60 8000B360 A7A900E6 */  sh    $t1, 0xe6($sp)
/* 00BF64 8000B364 AFAA00F0 */  sw    $t2, 0xf0($sp)
/* 00BF68 8000B368 E7A000DC */  swc1  $f0, 0xdc($sp)
/* 00BF6C 8000B36C E7A20060 */  swc1  $f2, 0x60($sp)
/* 00BF70 8000B370 0C001EFE */  jal   func_80007BF8
/* 00BF74 8000B374 AFAC0010 */   sw    $t4, 0x10($sp)
/* 00BF78 8000B378 3C0B8016 */  lui   $t3, %hi(D_80163068) # $t3, 0x8016
/* 00BF7C 8000B37C 256B3068 */  addiu $t3, %lo(D_80163068) # addiu $t3, $t3, 0x3068
/* 00BF80 8000B380 87A300E4 */  lh    $v1, 0xe4($sp)
/* 00BF84 8000B384 8FA800FC */  lw    $t0, 0xfc($sp)
/* 00BF88 8000B388 87A900E6 */  lh    $t1, 0xe6($sp)
/* 00BF8C 8000B38C 8FAA00F0 */  lw    $t2, 0xf0($sp)
/* 00BF90 8000B390 C7A000DC */  lwc1  $f0, 0xdc($sp)
/* 00BF94 8000B394 18400015 */  blez  $v0, .L8000B3EC
/* 00BF98 8000B398 C7A20060 */   lwc1  $f2, 0x60($sp)
/* 00BF9C 8000B39C 000A1040 */  sll   $v0, $t2, 1
/* 00BFA0 8000B3A0 03A26821 */  addu  $t5, $sp, $v0
/* 00BFA4 8000B3A4 00692823 */  subu  $a1, $v1, $t1
/* 00BFA8 8000B3A8 27AF00B0 */  addiu $t7, $sp, 0xb0
/* 00BFAC 8000B3AC 000AC080 */  sll   $t8, $t2, 2
/* 00BFB0 8000B3B0 27B90074 */  addiu $t9, $sp, 0x74
/* 00BFB4 8000B3B4 A5A8009C */  sh    $t0, 0x9c($t5)
/* 00BFB8 8000B3B8 03192021 */  addu  $a0, $t8, $t9
/* 00BFBC 8000B3BC 18A00003 */  blez  $a1, .L8000B3CC
/* 00BFC0 8000B3C0 004F3021 */   addu  $a2, $v0, $t7
/* 00BFC4 8000B3C4 10000006 */  b     .L8000B3E0
/* 00BFC8 8000B3C8 A4C50000 */   sh    $a1, ($a2)
.L8000B3CC:
/* 00BFCC 8000B3CC 3C0E8016 */  lui   $t6, %hi(D_80164430) # $t6, 0x8016
/* 00BFD0 8000B3D0 95CE4430 */  lhu   $t6, %lo(D_80164430)($t6)
/* 00BFD4 8000B3D4 006E6021 */  addu  $t4, $v1, $t6
/* 00BFD8 8000B3D8 01896823 */  subu  $t5, $t4, $t1
/* 00BFDC 8000B3DC A4CD0000 */  sh    $t5, ($a2)
.L8000B3E0:
/* 00BFE0 8000B3E0 46001101 */  sub.s $f4, $f2, $f0
/* 00BFE4 8000B3E4 254A0001 */  addiu $t2, $t2, 1
/* 00BFE8 8000B3E8 E4840000 */  swc1  $f4, ($a0)
.L8000B3EC:
/* 00BFEC 8000B3EC 29410002 */  slti  $at, $t2, 2
.L8000B3F0:
/* 00BFF0 8000B3F0 10200004 */  beqz  $at, .L8000B404
/* 00BFF4 8000B3F4 25080001 */   addiu $t0, $t0, 1
/* 00BFF8 8000B3F8 29010008 */  slti  $at, $t0, 8
/* 00BFFC 8000B3FC 5420FFB1 */  bnel  $at, $zero, .L8000B2C4
/* 00C000 8000B400 8FAC0100 */   lw    $t4, 0x100($sp)
.L8000B404:
/* 00C004 8000B404 114000F0 */  beqz  $t2, .L8000B7C8
/* 00C008 8000B408 00004025 */   move  $t0, $zero
/* 00C00C 8000B40C 4600C486 */  mov.s $f18, $f24
/* 00C010 8000B410 194000BD */  blez  $t2, .L8000B708
/* 00C014 8000B414 4600D506 */   mov.s $f20, $f26
/* 00C018 8000B418 31420001 */  andi  $v0, $t2, 1
/* 00C01C 8000B41C 1040003B */  beqz  $v0, .L8000B50C
/* 00C020 8000B420 87A3009C */   lh    $v1, 0x9c($sp)
/* 00C024 8000B424 00037880 */  sll   $t7, $v1, 2
/* 00C028 8000B428 016FC021 */  addu  $t8, $t3, $t7
/* 00C02C 8000B42C C7020000 */  lwc1  $f2, ($t8)
/* 00C030 8000B430 24080001 */  li    $t0, 1
/* 00C034 8000B434 4602D03C */  c.lt.s $f26, $f2
/* 00C038 8000B438 00000000 */  nop   
/* 00C03C 8000B43C 45000032 */  bc1f  .L8000B508
/* 00C040 8000B440 00000000 */   nop   
/* 00C044 8000B444 4618103C */  c.lt.s $f2, $f24
/* 00C048 8000B448 87A200B0 */  lh    $v0, 0xb0($sp)
/* 00C04C 8000B44C 4500002E */  bc1f  .L8000B508
/* 00C050 8000B450 00000000 */   nop   
/* 00C054 8000B454 44824000 */  mtc1  $v0, $f8
/* 00C058 8000B458 3C0141A0 */  li    $at, 0x41A00000 # 20.000000
/* 00C05C 8000B45C 4481B000 */  mtc1  $at, $f22
/* 00C060 8000B460 468042A0 */  cvt.s.w $f10, $f8
/* 00C064 8000B464 3C01800F */  lui   $at, %hi(D_800ECFCC) # $at, 0x800f
/* 00C068 8000B468 C426CFCC */  lwc1  $f6, %lo(D_800ECFCC)($at)
/* 00C06C 8000B46C 3C014120 */  li    $at, 0x41200000 # 10.000000
/* 00C070 8000B470 C7A00074 */  lwc1  $f0, 0x74($sp)
/* 00C074 8000B474 4618C032 */  c.eq.s $f24, $f24
/* 00C078 8000B478 46165100 */  add.s $f4, $f10, $f22
/* 00C07C 8000B47C 4604B203 */  div.s $f8, $f22, $f4
/* 00C080 8000B480 44812000 */  mtc1  $at, $f4
/* 00C084 8000B484 46083282 */  mul.s $f10, $f6, $f8
/* 00C088 8000B488 46040180 */  add.s $f6, $f0, $f4
/* 00C08C 8000B48C 460A3202 */  mul.s $f8, $f6, $f10
/* 00C090 8000B490 45000008 */  bc1f  .L8000B4B4
/* 00C094 8000B494 46164303 */   div.s $f12, $f8, $f22
/* 00C098 8000B498 461AD032 */  c.eq.s $f26, $f26
/* 00C09C 8000B49C 00000000 */  nop   
/* 00C0A0 8000B4A0 45020005 */  bc1fl .L8000B4B8
/* 00C0A4 8000B4A4 460C1381 */   sub.s $f14, $f2, $f12
/* 00C0A8 8000B4A8 460C1481 */  sub.s $f18, $f2, $f12
/* 00C0AC 8000B4AC 10000016 */  b     .L8000B508
/* 00C0B0 8000B4B0 460C1500 */   add.s $f20, $f2, $f12
.L8000B4B4:
/* 00C0B4 8000B4B4 460C1381 */  sub.s $f14, $f2, $f12
.L8000B4B8:
/* 00C0B8 8000B4B8 460C1400 */  add.s $f16, $f2, $f12
/* 00C0BC 8000B4BC 4618703C */  c.lt.s $f14, $f24
/* 00C0C0 8000B4C0 00000000 */  nop   
/* 00C0C4 8000B4C4 45020008 */  bc1fl .L8000B4E8
/* 00C0C8 8000B4C8 4610D03C */   c.lt.s $f26, $f16
/* 00C0CC 8000B4CC 460C1100 */  add.s $f4, $f2, $f12
/* 00C0D0 8000B4D0 4604C03C */  c.lt.s $f24, $f4
/* 00C0D4 8000B4D4 00000000 */  nop   
/* 00C0D8 8000B4D8 45020003 */  bc1fl .L8000B4E8
/* 00C0DC 8000B4DC 4610D03C */   c.lt.s $f26, $f16
/* 00C0E0 8000B4E0 46007486 */  mov.s $f18, $f14
/* 00C0E4 8000B4E4 4610D03C */  c.lt.s $f26, $f16
.L8000B4E8:
/* 00C0E8 8000B4E8 00000000 */  nop   
/* 00C0EC 8000B4EC 45000006 */  bc1f  .L8000B508
/* 00C0F0 8000B4F0 00000000 */   nop   
/* 00C0F4 8000B4F4 461A703C */  c.lt.s $f14, $f26
/* 00C0F8 8000B4F8 00000000 */  nop   
/* 00C0FC 8000B4FC 45000002 */  bc1f  .L8000B508
/* 00C100 8000B500 00000000 */   nop   
/* 00C104 8000B504 46008506 */  mov.s $f20, $f16
.L8000B508:
/* 00C108 8000B508 110A007F */  beq   $t0, $t2, .L8000B708
.L8000B50C:
/* 00C10C 8000B50C 3C0141A0 */   li    $at, 0x41A00000 # 20.000000
/* 00C110 8000B510 00081040 */  sll   $v0, $t0, 1
/* 00C114 8000B514 27B9009C */  addiu $t9, $sp, 0x9c
/* 00C118 8000B518 4481B000 */  mtc1  $at, $f22
/* 00C11C 8000B51C 00592821 */  addu  $a1, $v0, $t9
/* 00C120 8000B520 27A400B0 */  addiu $a0, $sp, 0xb0
/* 00C124 8000B524 27A30074 */  addiu $v1, $sp, 0x74
.L8000B528:
/* 00C128 8000B528 84AE0000 */  lh    $t6, ($a1)
/* 00C12C 8000B52C 000E6080 */  sll   $t4, $t6, 2
/* 00C130 8000B530 016C6821 */  addu  $t5, $t3, $t4
/* 00C134 8000B534 C5A20000 */  lwc1  $f2, ($t5)
/* 00C138 8000B538 4602D03C */  c.lt.s $f26, $f2
/* 00C13C 8000B53C 00000000 */  nop   
/* 00C140 8000B540 45020034 */  bc1fl .L8000B614
/* 00C144 8000B544 84AC0002 */   lh    $t4, 2($a1)
/* 00C148 8000B548 4618103C */  c.lt.s $f2, $f24
/* 00C14C 8000B54C 00087880 */  sll   $t7, $t0, 2
/* 00C150 8000B550 006FC021 */  addu  $t8, $v1, $t7
/* 00C154 8000B554 3C014120 */  li    $at, 0x41200000 # 10.000000
/* 00C158 8000B558 4500002D */  bc1f  .L8000B610
/* 00C15C 8000B55C 0082C821 */   addu  $t9, $a0, $v0
/* 00C160 8000B560 C7060000 */  lwc1  $f6, ($t8)
/* 00C164 8000B564 44815000 */  mtc1  $at, $f10
/* 00C168 8000B568 872E0000 */  lh    $t6, ($t9)
/* 00C16C 8000B56C 3C01800F */  lui   $at, %hi(D_800ECFD0) # $at, 0x800f
/* 00C170 8000B570 460A3200 */  add.s $f8, $f6, $f10
/* 00C174 8000B574 448E3000 */  mtc1  $t6, $f6
/* 00C178 8000B578 C424CFD0 */  lwc1  $f4, %lo(D_800ECFD0)($at)
/* 00C17C 8000B57C 46189032 */  c.eq.s $f18, $f24
/* 00C180 8000B580 468032A0 */  cvt.s.w $f10, $f6
/* 00C184 8000B584 46165180 */  add.s $f6, $f10, $f22
/* 00C188 8000B588 4606B283 */  div.s $f10, $f22, $f6
/* 00C18C 8000B58C 460A2182 */  mul.s $f6, $f4, $f10
/* 00C190 8000B590 00000000 */  nop   
/* 00C194 8000B594 46064102 */  mul.s $f4, $f8, $f6
/* 00C198 8000B598 45000008 */  bc1f  .L8000B5BC
/* 00C19C 8000B59C 46162003 */   div.s $f0, $f4, $f22
/* 00C1A0 8000B5A0 461AA032 */  c.eq.s $f20, $f26
/* 00C1A4 8000B5A4 00000000 */  nop   
/* 00C1A8 8000B5A8 45020005 */  bc1fl .L8000B5C0
/* 00C1AC 8000B5AC 46001301 */   sub.s $f12, $f2, $f0
/* 00C1B0 8000B5B0 46001481 */  sub.s $f18, $f2, $f0
/* 00C1B4 8000B5B4 10000016 */  b     .L8000B610
/* 00C1B8 8000B5B8 46001500 */   add.s $f20, $f2, $f0
.L8000B5BC:
/* 00C1BC 8000B5BC 46001301 */  sub.s $f12, $f2, $f0
.L8000B5C0:
/* 00C1C0 8000B5C0 46001380 */  add.s $f14, $f2, $f0
/* 00C1C4 8000B5C4 4612603C */  c.lt.s $f12, $f18
/* 00C1C8 8000B5C8 00000000 */  nop   
/* 00C1CC 8000B5CC 45020008 */  bc1fl .L8000B5F0
/* 00C1D0 8000B5D0 460EA03C */   c.lt.s $f20, $f14
/* 00C1D4 8000B5D4 46001280 */  add.s $f10, $f2, $f0
/* 00C1D8 8000B5D8 460A903C */  c.lt.s $f18, $f10
/* 00C1DC 8000B5DC 00000000 */  nop   
/* 00C1E0 8000B5E0 45020003 */  bc1fl .L8000B5F0
/* 00C1E4 8000B5E4 460EA03C */   c.lt.s $f20, $f14
/* 00C1E8 8000B5E8 46006486 */  mov.s $f18, $f12
/* 00C1EC 8000B5EC 460EA03C */  c.lt.s $f20, $f14
.L8000B5F0:
/* 00C1F0 8000B5F0 00000000 */  nop   
/* 00C1F4 8000B5F4 45020007 */  bc1fl .L8000B614
/* 00C1F8 8000B5F8 84AC0002 */   lh    $t4, 2($a1)
/* 00C1FC 8000B5FC 4614603C */  c.lt.s $f12, $f20
/* 00C200 8000B600 00000000 */  nop   
/* 00C204 8000B604 45020003 */  bc1fl .L8000B614
/* 00C208 8000B608 84AC0002 */   lh    $t4, 2($a1)
/* 00C20C 8000B60C 46007506 */  mov.s $f20, $f14
.L8000B610:
/* 00C210 8000B610 84AC0002 */  lh    $t4, 2($a1)
.L8000B614:
/* 00C214 8000B614 24A50004 */  addiu $a1, $a1, 4
/* 00C218 8000B618 000C6880 */  sll   $t5, $t4, 2
/* 00C21C 8000B61C 016D7821 */  addu  $t7, $t3, $t5
/* 00C220 8000B620 C5E00000 */  lwc1  $f0, ($t7)
/* 00C224 8000B624 4600D03C */  c.lt.s $f26, $f0
/* 00C228 8000B628 00000000 */  nop   
/* 00C22C 8000B62C 45020034 */  bc1fl .L8000B700
/* 00C230 8000B630 25080002 */   addiu $t0, $t0, 2
/* 00C234 8000B634 4618003C */  c.lt.s $f0, $f24
/* 00C238 8000B638 0008C080 */  sll   $t8, $t0, 2
/* 00C23C 8000B63C 0078C821 */  addu  $t9, $v1, $t8
/* 00C240 8000B640 3C014120 */  li    $at, 0x41200000 # 10.000000
/* 00C244 8000B644 4500002D */  bc1f  .L8000B6FC
/* 00C248 8000B648 00827021 */   addu  $t6, $a0, $v0
/* 00C24C 8000B64C C7280004 */  lwc1  $f8, 4($t9)
/* 00C250 8000B650 44813000 */  mtc1  $at, $f6
/* 00C254 8000B654 85CC0002 */  lh    $t4, 2($t6)
/* 00C258 8000B658 3C01800F */  lui   $at, %hi(D_800ECFD4) # $at, 0x800f
/* 00C25C 8000B65C 46064100 */  add.s $f4, $f8, $f6
/* 00C260 8000B660 448C4000 */  mtc1  $t4, $f8
/* 00C264 8000B664 C42ACFD4 */  lwc1  $f10, %lo(D_800ECFD4)($at)
/* 00C268 8000B668 46189032 */  c.eq.s $f18, $f24
/* 00C26C 8000B66C 468041A0 */  cvt.s.w $f6, $f8
/* 00C270 8000B670 46163200 */  add.s $f8, $f6, $f22
/* 00C274 8000B674 4608B183 */  div.s $f6, $f22, $f8
/* 00C278 8000B678 46065202 */  mul.s $f8, $f10, $f6
/* 00C27C 8000B67C 00000000 */  nop   
/* 00C280 8000B680 46082282 */  mul.s $f10, $f4, $f8
/* 00C284 8000B684 45000008 */  bc1f  .L8000B6A8
/* 00C288 8000B688 46165083 */   div.s $f2, $f10, $f22
/* 00C28C 8000B68C 461AA032 */  c.eq.s $f20, $f26
/* 00C290 8000B690 00000000 */  nop   
/* 00C294 8000B694 45020005 */  bc1fl .L8000B6AC
/* 00C298 8000B698 46020301 */   sub.s $f12, $f0, $f2
/* 00C29C 8000B69C 46020481 */  sub.s $f18, $f0, $f2
/* 00C2A0 8000B6A0 10000016 */  b     .L8000B6FC
/* 00C2A4 8000B6A4 46020500 */   add.s $f20, $f0, $f2
.L8000B6A8:
/* 00C2A8 8000B6A8 46020301 */  sub.s $f12, $f0, $f2
.L8000B6AC:
/* 00C2AC 8000B6AC 46020380 */  add.s $f14, $f0, $f2
/* 00C2B0 8000B6B0 4612603C */  c.lt.s $f12, $f18
/* 00C2B4 8000B6B4 00000000 */  nop   
/* 00C2B8 8000B6B8 45020008 */  bc1fl .L8000B6DC
/* 00C2BC 8000B6BC 460EA03C */   c.lt.s $f20, $f14
/* 00C2C0 8000B6C0 46020180 */  add.s $f6, $f0, $f2
/* 00C2C4 8000B6C4 4606903C */  c.lt.s $f18, $f6
/* 00C2C8 8000B6C8 00000000 */  nop   
/* 00C2CC 8000B6CC 45020003 */  bc1fl .L8000B6DC
/* 00C2D0 8000B6D0 460EA03C */   c.lt.s $f20, $f14
/* 00C2D4 8000B6D4 46006486 */  mov.s $f18, $f12
/* 00C2D8 8000B6D8 460EA03C */  c.lt.s $f20, $f14
.L8000B6DC:
/* 00C2DC 8000B6DC 00000000 */  nop   
/* 00C2E0 8000B6E0 45020007 */  bc1fl .L8000B700
/* 00C2E4 8000B6E4 25080002 */   addiu $t0, $t0, 2
/* 00C2E8 8000B6E8 4614603C */  c.lt.s $f12, $f20
/* 00C2EC 8000B6EC 00000000 */  nop   
/* 00C2F0 8000B6F0 45020003 */  bc1fl .L8000B700
/* 00C2F4 8000B6F4 25080002 */   addiu $t0, $t0, 2
/* 00C2F8 8000B6F8 46007506 */  mov.s $f20, $f14
.L8000B6FC:
/* 00C2FC 8000B6FC 25080002 */  addiu $t0, $t0, 2
.L8000B700:
/* 00C300 8000B700 150AFF89 */  bne   $t0, $t2, .L8000B528
/* 00C304 8000B704 24420004 */   addiu $v0, $v0, 4
.L8000B708:
/* 00C308 8000B708 4612A03C */  c.lt.s $f20, $f18
/* 00C30C 8000B70C 8FAD0054 */  lw    $t5, 0x54($sp)
/* 00C310 8000B710 4503002E */  bc1tl .L8000B7CC
/* 00C314 8000B714 8FBF003C */   lw    $ra, 0x3c($sp)
/* 00C318 8000B718 C5A00000 */  lwc1  $f0, ($t5)
/* 00C31C 8000B71C 4612003C */  c.lt.s $f0, $f18
/* 00C320 8000B720 00000000 */  nop   
/* 00C324 8000B724 45030029 */  bc1tl .L8000B7CC
/* 00C328 8000B728 8FBF003C */   lw    $ra, 0x3c($sp)
/* 00C32C 8000B72C 4600A03C */  c.lt.s $f20, $f0
/* 00C330 8000B730 00000000 */  nop   
/* 00C334 8000B734 45030025 */  bc1tl .L8000B7CC
/* 00C338 8000B738 8FBF003C */   lw    $ra, 0x3c($sp)
/* 00C33C 8000B73C 4614C03C */  c.lt.s $f24, $f20
/* 00C340 8000B740 8FAF005C */  lw    $t7, 0x5c($sp)
/* 00C344 8000B744 3C188016 */  lui   $t8, %hi(D_80162FF8) # $t8, 0x8016
/* 00C348 8000B748 27182FF8 */  addiu $t8, %lo(D_80162FF8) # addiu $t8, $t8, 0x2ff8
/* 00C34C 8000B74C 45000002 */  bc1f  .L8000B758
/* 00C350 8000B750 01F81021 */   addu  $v0, $t7, $t8
/* 00C354 8000B754 4600C506 */  mov.s $f20, $f24
.L8000B758:
/* 00C358 8000B758 461A903C */  c.lt.s $f18, $f26
/* 00C35C 8000B75C 8FAE004C */  lw    $t6, 0x4c($sp)
/* 00C360 8000B760 4614C201 */  sub.s $f8, $f24, $f20
/* 00C364 8000B764 8FB8004C */  lw    $t8, 0x4c($sp)
/* 00C368 8000B768 45000002 */  bc1f  .L8000B774
/* 00C36C 8000B76C 24190002 */   li    $t9, 2
/* 00C370 8000B770 4600D486 */  mov.s $f18, $f26
.L8000B774:
/* 00C374 8000B774 46189100 */  add.s $f4, $f18, $f24
/* 00C378 8000B778 240C0001 */  li    $t4, 1
/* 00C37C 8000B77C 240F003C */  li    $t7, 60
/* 00C380 8000B780 4608203C */  c.lt.s $f4, $f8
/* 00C384 8000B784 00000000 */  nop   
/* 00C388 8000B788 4502000A */  bc1fl .L8000B7B4
/* 00C38C 8000B78C A70F0000 */   sh    $t7, ($t8)
/* 00C390 8000B790 2419003C */  li    $t9, 60
/* 00C394 8000B794 A5D90000 */  sh    $t9, ($t6)
/* 00C398 8000B798 8FAD0058 */  lw    $t5, 0x58($sp)
/* 00C39C 8000B79C 3C018016 */  lui   $at, %hi(D_80163090)
/* 00C3A0 8000B7A0 A44C0000 */  sh    $t4, ($v0)
/* 00C3A4 8000B7A4 002D0821 */  addu  $at, $at, $t5
/* 00C3A8 8000B7A8 10000007 */  b     .L8000B7C8
/* 00C3AC 8000B7AC E4343090 */   swc1  $f20, %lo(D_80163090)($at)
/* 00C3B0 8000B7B0 A70F0000 */  sh    $t7, ($t8)
.L8000B7B4:
/* 00C3B4 8000B7B4 8FAE0058 */  lw    $t6, 0x58($sp)
/* 00C3B8 8000B7B8 3C018016 */  lui   $at, %hi(D_80163090)
/* 00C3BC 8000B7BC A4590000 */  sh    $t9, ($v0)
/* 00C3C0 8000B7C0 002E0821 */  addu  $at, $at, $t6
/* 00C3C4 8000B7C4 E4323090 */  swc1  $f18, %lo(D_80163090)($at)
.L8000B7C8:
/* 00C3C8 8000B7C8 8FBF003C */  lw    $ra, 0x3c($sp)
.L8000B7CC:
/* 00C3CC 8000B7CC D7B40018 */  ldc1  $f20, 0x18($sp)
/* 00C3D0 8000B7D0 D7B60020 */  ldc1  $f22, 0x20($sp)
/* 00C3D4 8000B7D4 D7B80028 */  ldc1  $f24, 0x28($sp)
/* 00C3D8 8000B7D8 D7BA0030 */  ldc1  $f26, 0x30($sp)
/* 00C3DC 8000B7DC 03E00008 */  jr    $ra
/* 00C3E0 8000B7E0 27BD0100 */   addiu $sp, $sp, 0x100