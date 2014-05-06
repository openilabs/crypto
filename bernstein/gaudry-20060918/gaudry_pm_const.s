.data
.section .rodata
.p2align 5

.globl gaudry_pm_constants
.globl gaudry_pm_scale
.globl gaudry_pm_alpha26
.globl gaudry_pm_alpha51
.globl gaudry_pm_alpha77
.globl gaudry_pm_alpha102
.globl gaudry_pm_alpha127
.globl gaudry_pm_in0offset
.globl gaudry_pm_in1offset
.globl gaudry_pm_in2offset
.globl gaudry_pm_in3offset
.globl gaudry_pm_in4offset
.globl gaudry_pm_out0offset
.globl gaudry_pm_out1offset
.globl gaudry_pm_out2offset
.globl gaudry_pm_out3offset
.globl gaudry_pm_out4offset
.globl gaudry_pm_rounding

gaudry_pm_constants:
gaudry_pm_scale:
	.long 0x0,0x38000000
gaudry_pm_alpha26:
	.long 0x0,0x45880000
gaudry_pm_alpha51:
	.long 0x0,0x47180000
gaudry_pm_alpha77:
	.long 0x0,0x48b80000
gaudry_pm_alpha102:
	.long 0x0,0x4a480000
gaudry_pm_alpha127:
	.long 0x0,0x4bd80000
gaudry_pm_in0offset:
	.long 0x0,0x43300000
gaudry_pm_in1offset:
	.long 0x0,0x45300000
gaudry_pm_in2offset:
	.long 0x0,0x46b00000
gaudry_pm_in3offset:
	.long 0x0,0x48300000
gaudry_pm_in4offset:
	.long 0x0,0x49b00000
gaudry_pm_out0offset:
	.long 0x1fffffff,0x43380000
gaudry_pm_out1offset:
	.long 0xffffff8,0x44d80000
gaudry_pm_out2offset:
	.long 0x1ffffff8,0x46680000
gaudry_pm_out3offset:
	.long 0xffffff8,0x48080000
gaudry_pm_out4offset:
	.long 0x1fffff8,0x49980000
gaudry_pm_rounding:
	.byte 0x7f
	.byte 0x13
