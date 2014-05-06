#include <stdio.h>
#include <math.h>
#include "zmodexp.h"

zmodexp512_tmp t;

uint32 m[16] = {
  0xc03ec9cd, 0xe0954e8b, 0xe7ee5c07, 0x6957fdee,
  0x106dfabf, 0x494c1c33, 0x5ca386e1, 0x36754be7,
  0xb120b7bb, 0x4d223ee8, 0x0feb4b50, 0x4dcdb922,
  0x1cc8c907, 0x999a6e81, 0x0788d87e, 0x468dd474
};
uint32 r[16] = {
  0x12ed3a7d, 0x24554e0a, 0xbca4d309, 0x0a0d7308,
  0xea12646e, 0xeb1de6fb, 0xdffc6ca3, 0x564b03bf,
  0x022f0804, 0xa548d155, 0x243b2bc0, 0x46fb11f0,
  0xe21f9a51, 0x5a90a293, 0x81359515, 0x31701523
};
unsigned char e[400] = {
  0x80, 0x1e, 0x49, 0x20,
  0xa7, 0xad, 0x1a, 0x70,
  0x0d, 0x55, 0x78, 0xe7,
  0x3e, 0x08, 0x9c, 0x82,
  0xd0, 0xfd, 0x5b, 0x43,
  0x40, 0xb9, 0x3d, 0xea,
  0xd9, 0x83, 0xf2, 0x22,
  0x58, 0xb0, 0xfb, 0xfc,
  0xdd, 0x7a, 0x8e, 0x1e,
  0xce, 0x7b, 0xec, 0x80,
  0x09, 0x6c, 0xdb, 0x56,
  0x13, 0x3f, 0x0b, 0xa3,
  0x57, 0xc7, 0x86, 0x99,
  0x50, 0x31, 0xe2, 0xff,
  0x7a, 0x2e, 0x0b, 0x7a,
  0x69, 0xd8, 0x23, 0x40
} ;

void doit()
{
  int i;

  printf("lift(mod(0");
  for (i = 0;i < 16;++i) printf("+s^%d*%u",i,r[i]);
  printf(",");
  printf("0");
  for (i = 0;i < 16;++i) printf("+s^%d*%u",i,m[i]);
  printf(")^((0");
  for (i = 0;i < 400;++i) printf("+r^%d*%u",i,e[i]);
  printf("))-");

  zmodexp512(m,r,e,400,&t);

  printf("(0");
  for (i = 0;i < 16;++i) printf("+s^%d*%u",i,r[i]);
  printf("))\n");
  fflush(stdout);
}

uint32 foobuf[55] = { 1 };
static int foopos = 0;
static int foopos2 = 24;

int foo()
{
  if (++foopos == 55) foopos = 0;
  if (++foopos2 == 55) foopos2 = 0;
  return foobuf[foopos] += foobuf[foopos2];
}

main()
{
  int i;
  int loop;

  printf("r=2^8;s=2^32;\n");

  doit();

  for (i = 0;i < 10000;++i) foo();

  for (loop = 0;loop < 1000;++loop) {
    for (i = 0;i < 16;++i) m[i] = foo();
    m[15] |= 0x80000000;
    for (i = 0;i < 16;++i) r[i] = foo();
    for (i = 0;i < 400;i += 4) e[i] = foo();
    doit();
  }

  return 0;
}