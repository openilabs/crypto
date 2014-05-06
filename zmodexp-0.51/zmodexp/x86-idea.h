#ifndef ZMODEXP_H
#define ZMODEXP_H "x86-idea"

#include "uint32.h"

typedef struct {
  double x[18];
  double inv[18];
  double t[35];
  double y;
  double q[18];
} zmodexp512_m;

typedef struct {
  double x[18];
} zmodexp512_r;

extern void zmodexp512_init(zmodexp512_m *,const uint32 [16]);
extern void zmodexp512_load(zmodexp512_m *,zmodexp512_r *,const uint32 [16]);
extern void zmodexp512_store(zmodexp512_m *,zmodexp512_r *,uint32 [16]);
extern void zmodexp512_square(zmodexp512_m *,zmodexp512_r *);
extern void zmodexp512_multiply(zmodexp512_m *,zmodexp512_r *,const zmodexp512_r *);

typedef struct {
  zmodexp512_m m;
  zmodexp512_r x;
  zmodexp512_r r[16];
} zmodexp512_tmp;

extern void zmodexp512(const uint32 [16],uint32 [16],unsigned char *,unsigned int,zmodexp512_tmp *);

#endif
