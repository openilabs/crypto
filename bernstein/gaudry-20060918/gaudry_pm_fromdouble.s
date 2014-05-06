.text
.p2align 5
.globl _gaudry_pm_fromdouble
.globl gaudry_pm_fromdouble
_gaudry_pm_fromdouble:
gaudry_pm_fromdouble:
mov %esp,%eax
and $31,%eax
add $128,%eax
sub %eax,%esp
movl %ebp,0(%esp)
movl 8(%esp,%eax),%ecx
fldl 0(%ecx)
faddl gaudry_pm_out0offset
fstpl 64(%esp)
fldl 8(%ecx)
faddl gaudry_pm_out1offset
fstpl 72(%esp)
fldl 16(%ecx)
faddl gaudry_pm_out2offset
fstpl 80(%esp)
fldl 24(%ecx)
faddl gaudry_pm_out3offset
fstpl 88(%esp)
fldl 32(%ecx)
faddl gaudry_pm_out4offset
fstpl 96(%esp)
movl 64(%esp),%ecx
movl %ecx,4(%esp)
movl 72(%esp),%ecx
shl  $26,%ecx
movl %ecx,24(%esp)
movl 72(%esp),%ecx
shr  $6,%ecx
movl %ecx,8(%esp)
movl 80(%esp),%ecx
shl  $19,%ecx
movl %ecx,28(%esp)
movl 80(%esp),%ecx
shr  $13,%ecx
movl %ecx,12(%esp)
movl 88(%esp),%ecx
shl  $13,%ecx
movl %ecx,32(%esp)
movl 88(%esp),%ecx
shr  $19,%ecx
movl %ecx,16(%esp)
movl 96(%esp),%ecx
shl  $6,%ecx
movl %ecx,36(%esp)
movl 96(%esp),%ecx
shr  $26,%ecx
movl %ecx,20(%esp)
mov  $0,%ecx
movl %ecx,40(%esp)
movl 4(%esp),%ecx
addl 24(%esp),%ecx
movl %ecx,4(%esp)
movl 8(%esp),%ecx
adcl 28(%esp),%ecx
movl %ecx,8(%esp)
movl 12(%esp),%ecx
adcl 32(%esp),%ecx
movl %ecx,12(%esp)
movl 16(%esp),%ecx
adcl 36(%esp),%ecx
movl %ecx,16(%esp)
movl 20(%esp),%ecx
adcl 40(%esp),%ecx
movl %ecx,20(%esp)
movl 4(%esp),%ecx
adc  $0x1,%ecx
movl %ecx,24(%esp)
movl 8(%esp),%ecx
adc  $0,%ecx
movl %ecx,28(%esp)
movl 12(%esp),%ecx
adc  $0,%ecx
movl %ecx,32(%esp)
movl 16(%esp),%ecx
adc  $0x80000000,%ecx
movl %ecx,36(%esp)
movl 20(%esp),%ebp
adc  $0xffffffff,%ebp
and  $0x80000000,%ebp
sar  $31,%ebp
movl 4(%esp,%eax),%ecx
movl 4(%esp),%edx
xorl 24(%esp),%edx
and  %ebp,%edx
xorl 24(%esp),%edx
movl %edx,0(%ecx)
movl 8(%esp),%edx
xorl 28(%esp),%edx
and  %ebp,%edx
xorl 28(%esp),%edx
movl %edx,4(%ecx)
movl 12(%esp),%edx
xorl 32(%esp),%edx
and  %ebp,%edx
xorl 32(%esp),%edx
movl %edx,8(%ecx)
movl 16(%esp),%edx
xorl 36(%esp),%edx
and  %ebp,%edx
xorl 36(%esp),%edx
movl %edx,12(%ecx)
movl 0(%esp),%ebp
add %eax,%esp
ret