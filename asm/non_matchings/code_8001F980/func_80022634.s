glabel func_80022634
/* 023234 80022634 AFA50004 */  sw    $a1, 4($sp)
/* 023238 80022638 84820000 */  lh    $v0, ($a0)
/* 02323C 8002263C 00057400 */  sll   $t6, $a1, 0x10
/* 023240 80022640 000E7C03 */  sra   $t7, $t6, 0x10
/* 023244 80022644 004FC023 */  subu  $t8, $v0, $t7
/* 023248 80022648 44984000 */  mtc1  $t8, $f8
/* 02324C 8002264C 44866000 */  mtc1  $a2, $f12
/* 023250 80022650 44822000 */  mtc1  $v0, $f4
/* 023254 80022654 468042A0 */  cvt.s.w $f10, $f8
/* 023258 80022658 468021A0 */  cvt.s.w $f6, $f4
/* 02325C 8002265C 460C5402 */  mul.s $f16, $f10, $f12
/* 023260 80022660 46103481 */  sub.s $f18, $f6, $f16
/* 023264 80022664 4600910D */  trunc.w.s $f4, $f18
/* 023268 80022668 44082000 */  mfc1  $t0, $f4
/* 02326C 8002266C 03E00008 */  jr    $ra
/* 023270 80022670 A4880000 */   sh    $t0, ($a0)