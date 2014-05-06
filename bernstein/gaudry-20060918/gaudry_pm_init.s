.text
.p2align 5
.globl _gaudry_pm_init
.globl gaudry_pm_init
_gaudry_pm_init:
gaudry_pm_init:
mov %esp,%eax
and $31,%eax
add $0,%eax
sub %eax,%esp
fldcw gaudry_pm_rounding
add %eax,%esp
ret
