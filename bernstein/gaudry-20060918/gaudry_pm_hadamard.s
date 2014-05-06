.text
.p2align 5
.globl _gaudry_pm_hadamard
.globl gaudry_pm_hadamard
_gaudry_pm_hadamard:
gaudry_pm_hadamard:
mov %esp,%eax
and $31,%eax
add $0,%eax
sub %eax,%esp
movl 8(%esp,%eax),%edx
movl 4(%esp,%eax),%ecx
fldl 0(%edx)
fldl 40(%edx)
fldl 80(%edx)
fldl 120(%edx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 40(%edx)
fxch %st(1)
fsubl 120(%edx)
fldl 8(%edx)
fldl 48(%edx)
fldl 88(%edx)
fldl 128(%edx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 48(%edx)
fxch %st(1)
fsubl 128(%edx)
fxch %st(6)
fstpl 0(%ecx)
fxch %st(6)
fstpl 40(%ecx)
fxch %st(3)
fstpl 80(%ecx)
fxch %st(1)
fstpl 120(%ecx)
fxch %st(1)
fstpl 8(%ecx)
fstpl 48(%ecx)
fxch %st(1)
fstpl 88(%ecx)
fstpl 128(%ecx)
fldl 16(%edx)
fldl 56(%edx)
fldl 96(%edx)
fldl 136(%edx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 56(%edx)
fxch %st(1)
fsubl 136(%edx)
fldl 24(%edx)
fldl 64(%edx)
fldl 104(%edx)
fldl 144(%edx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 64(%edx)
fxch %st(1)
fsubl 144(%edx)
fxch %st(6)
fstpl 16(%ecx)
fxch %st(6)
fstpl 56(%ecx)
fxch %st(3)
fstpl 96(%ecx)
fxch %st(1)
fstpl 136(%ecx)
fxch %st(1)
fstpl 24(%ecx)
fstpl 64(%ecx)
fxch %st(1)
fstpl 104(%ecx)
fstpl 144(%ecx)
fldl 32(%edx)
fldl 72(%edx)
fldl 112(%edx)
fldl 152(%edx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 72(%edx)
fxch %st(1)
fsubl 152(%edx)
fldl 0(%ecx)
fldl 40(%ecx)
fldl 80(%ecx)
fldl 120(%ecx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 40(%ecx)
fxch %st(1)
fsubl 120(%ecx)
fxch %st(6)
fstpl 32(%ecx)
fxch %st(6)
fstpl 72(%ecx)
fxch %st(3)
fstpl 112(%ecx)
fxch %st(1)
fstpl 152(%ecx)
fxch %st(1)
fstpl 0(%ecx)
fxch %st(2)
fstpl 40(%ecx)
fxch %st(1)
fstpl 80(%ecx)
fstpl 120(%ecx)
fldl 8(%ecx)
fldl 48(%ecx)
fldl 88(%ecx)
fldl 128(%ecx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 48(%ecx)
fxch %st(1)
fsubl 128(%ecx)
fldl 16(%ecx)
fldl 56(%ecx)
fldl 96(%ecx)
fldl 136(%ecx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 56(%ecx)
fxch %st(1)
fsubl 136(%ecx)
fxch %st(6)
fstpl 8(%ecx)
fxch %st(4)
fstpl 48(%ecx)
fxch %st(5)
fstpl 88(%ecx)
fxch %st(1)
fstpl 128(%ecx)
fxch %st(3)
fstpl 16(%ecx)
fstpl 56(%ecx)
fxch %st(1)
fstpl 96(%ecx)
fstpl 136(%ecx)
fldl 24(%ecx)
fldl 64(%ecx)
fldl 104(%ecx)
fldl 144(%ecx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 64(%ecx)
fxch %st(1)
fsubl 144(%ecx)
fldl 32(%ecx)
fldl 72(%ecx)
fldl 112(%ecx)
fldl 152(%ecx)
fxch %st(3)
fadd %st(0),%st(2)
fxch %st(1)
fadd %st(0),%st(3)
fxch %st(1)
fsubl 72(%ecx)
fxch %st(1)
fsubl 152(%ecx)
fxch %st(6)
fstpl 24(%ecx)
fxch %st(4)
fstpl 64(%ecx)
fxch %st(5)
fstpl 104(%ecx)
fxch %st(1)
fstpl 144(%ecx)
fxch %st(3)
fstpl 32(%ecx)
fstpl 72(%ecx)
fxch %st(1)
fstpl 112(%ecx)
fstpl 152(%ecx)
add %eax,%esp
ret