.text
.p2align 5
.globl _gaudry_pm_todouble
.globl gaudry_pm_todouble
_gaudry_pm_todouble:
gaudry_pm_todouble:
mov %esp,%eax
and $31,%eax
add $64,%eax
sub %eax,%esp
movl 8(%esp,%eax),%ecx
movl 0(%ecx),%edx
movl  $0x43300000,4(%esp)
movl %edx,0(%esp)
movl 4(%ecx),%edx
and  $0xffffff,%edx
movl  $0x45300000,12(%esp)
movl %edx,8(%esp)
movl 7(%ecx),%edx
and  $0xffffff,%edx
movl  $0x46b00000,20(%esp)
movl %edx,16(%esp)
movl 10(%ecx),%edx
and  $0xffffff,%edx
movl  $0x48300000,28(%esp)
movl %edx,24(%esp)
movl 12(%ecx),%ecx
shr  $8,%ecx
movl  $0x49b00000,36(%esp)
movl %ecx,32(%esp)
movl 4(%esp,%eax),%ecx
fldl 32(%esp)
fsubl gaudry_pm_in4offset
fldl gaudry_pm_alpha127
fadd %st(1),%st(0)
fsubl gaudry_pm_alpha127
fsubr %st(0),%st(1)
fldl 0(%esp)
fsubl gaudry_pm_in0offset
fxch %st(1)
fmull gaudry_pm_scale
faddp %st(0),%st(1)
fldl gaudry_pm_alpha26
fadd %st(1),%st(0)
fsubl gaudry_pm_alpha26
fsubr %st(0),%st(1)
fxch %st(1)
fstpl 0(%ecx)
fldl 8(%esp)
fsubl gaudry_pm_in1offset
faddp %st(0),%st(1)
fldl gaudry_pm_alpha51
fadd %st(1),%st(0)
fsubl gaudry_pm_alpha51
fsubr %st(0),%st(1)
fxch %st(1)
fstpl 8(%ecx)
fldl 16(%esp)
fsubl gaudry_pm_in2offset
faddp %st(0),%st(1)
fldl gaudry_pm_alpha77
fadd %st(1),%st(0)
fsubl gaudry_pm_alpha77
fsubr %st(0),%st(1)
fxch %st(1)
fstpl 16(%ecx)
fldl 24(%esp)
fsubl gaudry_pm_in3offset
faddp %st(0),%st(1)
fldl gaudry_pm_alpha102
fadd %st(1),%st(0)
fsubl gaudry_pm_alpha102
fsubr %st(0),%st(1)
fxch %st(1)
fstpl 24(%ecx)
faddp %st(0),%st(1)
fstpl 32(%ecx)
add %eax,%esp
ret
