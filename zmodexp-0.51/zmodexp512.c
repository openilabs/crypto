#include "zmodexp.h"

static const uint32 one[16] =
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#define M (t->m)
#define X (t->x)
#define R (t->r)

void zmodexp512(const uint32 m32[16],uint32 r32[16],unsigned char *e,unsigned int elen,zmodexp512_tmp *t)
{
  int i;

  zmodexp512_init(&M,m32);
  zmodexp512_load(&M,&R[0],one);
  zmodexp512_load(&M,&R[1],r32);
  R[2] = R[1]; zmodexp512_square(&M,&R[2]);
  for (i = 3;i <= 15;i += 2) {
    R[i] = R[i - 2];
    zmodexp512_multiply(&M,&R[i],&R[2]);
  }
  for (i = 4;i <= 14;i += 2) {
    R[i] = R[i / 2];
    zmodexp512_square(&M,&R[i]);
  }

  X = R[0];
  while (elen > 0) {
    --elen;

    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_multiply(&M,&X,&R[e[elen] >> 4]);
    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_square(&M,&X);
    zmodexp512_multiply(&M,&X,&R[e[elen] & 15]);
  }

  zmodexp512_store(&M,&X,r32);
}
