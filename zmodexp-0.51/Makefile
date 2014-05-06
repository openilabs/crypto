# Don't edit Makefile! Use conf-* for configuration.

SHELL=/bin/sh

default: it

accuracy: \
load accuracy.o zmodexp.a math.lib
	./load accuracy zmodexp.a  `cat math.lib`

accuracy.o: \
compile accuracy.c zmodexp.h uint32.h
	./compile accuracy.c

compile: \
warn-auto.sh conf-cc
	( cat warn-auto.sh; \
	echo exec "`head -1 conf-cc`" '-c $${1+"$$@"}' \
	) > compile
	chmod 755 compile

hasgethr.h: \
trygethr.c compile load
	( ( ./compile trygethr.c && ./load trygethr ) >/dev/null \
	2>&1 \
	&& echo \#define HASGETHRTIME 1 || exit 0 ) > hasgethr.h
	rm -f trygethr.o

hasrdtsc.h: \
tryrdtsc.c compile load
	( ( ./compile tryrdtsc.c && ./load tryrdtsc && ./tryrdtsc \
	) >/dev/null 2>&1 \
	&& echo \#define HASRDTSC 1 || exit 0 ) > hasrdtsc.h
	rm -f tryrdtsc.o tryrdtsc

it: \
prog

load: \
warn-auto.sh conf-ld
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo exec "`head -1 conf-ld`" \
	'-o "$$main" "$$main".o $${1+"$$@"}' \
	) > load
	chmod 755 load

makelib: \
warn-auto.sh systype
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo 'rm -f "$$main"'; \
	echo 'ar cr "$$main" $${1+"$$@"}'; \
	case "`cat systype`" in \
	sunos-5.*) ;; \
	unix_sv*) ;; \
	irix64-*) ;; \
	irix-*) ;; \
	dgux-*) ;; \
	hp-ux-*) ;; \
	sco*) ;; \
	*) echo 'ranlib "$$main"' ;; \
	esac \
	) > makelib
	chmod 755 makelib

prog: \
accuracy speed

speed: \
load speed.o zmodexp.a
	./load speed zmodexp.a 

speed.o: \
compile speed.c zmodexp.h uint32.h timing.h hasrdtsc.h hasgethr.h
	./compile speed.c

systype: \
find-systype.sh conf-cc conf-ld trycpp.c
	( cat warn-auto.sh; \
	echo CC=\'`head -1 conf-cc`\'; \
	echo LD=\'`head -1 conf-ld`\'; \
	cat find-systype.sh; \
	) | sh > systype

uint32.h: \
tryulong32.c compile load uint32.h1 uint32.h2
	( ( ./compile tryulong32.c && ./load tryulong32 && \
	./tryulong32 ) >/dev/null 2>&1 \
	&& cat uint32.h2 || cat uint32.h1 ) > uint32.h
	rm -f tryulong32.o tryulong32

zmodexp.a: \
makelib zmodexp.o zmodexp512.o
	./makelib zmodexp.a zmodexp.o zmodexp512.o

zmodexp.c: \
systype conf-opt print-opt.sh zmodexp/x86-idea.c zmodexp/x86-sched.c
	sh print-opt.sh zmodexp c > zmodexp.c

zmodexp.h: \
systype conf-opt print-opt.sh zmodexp/x86-idea.h zmodexp/x86-sched.h
	sh print-opt.sh zmodexp h > zmodexp.h

zmodexp.o: \
compile zmodexp.c zmodexp.h uint32.h
	./compile zmodexp.c

zmodexp512.o: \
compile zmodexp512.c zmodexp.h uint32.h
	./compile zmodexp512.c
