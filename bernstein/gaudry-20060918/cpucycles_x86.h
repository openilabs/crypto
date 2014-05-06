/*
cpucycles_x86.h version 20050201
D. J. Bernstein
Public domain.
*/

#ifndef CPUCYCLES_X86_H
#define CPUCYCLES_X86_H

extern long long cpucycles_x86(void);

#ifndef cpucycles_implementation
#define cpucycles_implementation "cpucycles_x86"
#define cpucycles cpucycles_x86
#endif

#endif
