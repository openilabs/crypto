CC=gcc -O3 -g -malign-double -march=pentiumpro -fomit-frame-pointer

current: \
gaudrytest \
gaudryspeed

gaudrytest: gaudrytest.c \
gaudry_pm_const.s \
gaudry_pm_init.s \
gaudry_pm_todouble.s \
gaudry_pm_hadamard.s \
gaudry_pm_square.s \
gaudry_pm_mult.s \
gaudry_pm_select.s \
gaudry_pm_mainloop.s \
gaudry_pm_fromdouble.s \
gaudry_pm.c
	$(CC) -o gaudrytest gaudrytest.c \
	gaudry_pm_const.s \
	gaudry_pm_init.s \
	gaudry_pm_todouble.s \
	gaudry_pm_hadamard.s \
	gaudry_pm_square.s \
	gaudry_pm_mult.s \
	gaudry_pm_select.s \
	gaudry_pm_mainloop.s \
	gaudry_pm_fromdouble.s \
	gaudry_pm.c \
	-lm

gaudryspeed: gaudryspeed.c \
gaudry_pm_const.s \
gaudry_pm_init.s \
gaudry_pm_todouble.s \
gaudry_pm_hadamard.s \
gaudry_pm_square.s \
gaudry_pm_mult.s \
gaudry_pm_select.s \
gaudry_pm_mainloop.s \
gaudry_pm_fromdouble.s \
gaudry_pm.c \
cpucycles_x86.s
	$(CC) -o gaudryspeed gaudryspeed.c \
	gaudry_pm_const.s \
	gaudry_pm_init.s \
	gaudry_pm_todouble.s \
	gaudry_pm_hadamard.s \
	gaudry_pm_square.s \
	gaudry_pm_mult.s \
	gaudry_pm_select.s \
	gaudry_pm_mainloop.s \
	gaudry_pm_fromdouble.s \
	gaudry_pm.c \
	cpucycles_x86.s \
	-lm
