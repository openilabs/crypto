#include "zmodexp.h"
#include "timing.h"

uint32 m32[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80000000 };
uint32 r32[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned char e[32] = {
  0x69, 0xdf, 0x4f, 0x8a,
  0xef, 0x4d, 0xf3, 0xc7,
  0x5b, 0x57, 0x63, 0x90,
  0x5d, 0x62, 0x7d, 0x56,
  0xd7, 0x3b, 0x66, 0xc5,
  0xc7, 0x25, 0x17, 0xa3,
  0xdf, 0x5d, 0x6d, 0x2d,
  0xa7, 0x74, 0x05, 0xfa
};

unsigned char bige[64] = {
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
};

timing start;
timing_basic startb;
timing finish;
timing_basic finishb;

#define TIMINGS 8
timing tnothing[2][TIMINGS];
timing tinit[2][TIMINGS];
timing tload[2][TIMINGS];
timing tstore[2][TIMINGS];
timing tmultiply[2][TIMINGS];
timing tsquare[2][TIMINGS];
timing t256[2][TIMINGS];
timing t512[2][TIMINGS];

main()
{
  zmodexp512_r *r;
  zmodexp512_m *m;
  zmodexp512_tmp *tmp;
  int i;
  int j;
  double diff;

  r = (zmodexp512_r *) malloc(sizeof(*r));
  if (!r) exit(1);
  m = (zmodexp512_m *) malloc(sizeof(*m));
  if (!m) exit(1);
  tmp = (zmodexp512_tmp *) malloc(sizeof(*tmp));
  if (!tmp) exit(1);

  timing_basic_now(&startb);
  timing_now(&start);

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tnothing[0][i]);
    timing_now(&tnothing[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tinit[0][i]);
    zmodexp512_init(m,m32);
    timing_now(&tinit[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tload[0][i]);
    zmodexp512_load(m,r,r32);
    timing_now(&tload[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tstore[0][i]);
    zmodexp512_store(m,r,r32);
    timing_now(&tstore[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tsquare[0][i]);
    zmodexp512_square(m,r);
    timing_now(&tsquare[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&tmultiply[0][i]);
    zmodexp512_multiply(m,r,r);
    timing_now(&tmultiply[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&t256[0][i]);
    zmodexp512(m32,r32,e,32,tmp);
    timing_now(&t256[1][i]);
  }

  for (i = 0;i < TIMINGS;++i) {
    timing_now(&t512[0][i]);
    zmodexp512(m32,r32,bige,64,tmp);
    timing_now(&t512[1][i]);
  }

  timing_basic_now(&finishb);
  timing_now(&finish);

  printf("Using");
#ifdef HASRDTSC
  printf(" RDTSC,");
#else
#ifdef HASGETHRTIME
  printf(" gethrtime(),");
#endif
#endif
  printf(" zmodexp/%s.c.\n",ZMODEXP_H);

  printf("nothing   ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tnothing[1][i],&tnothing[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("init      ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tinit[1][i],&tinit[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("load      ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tload[1][i],&tload[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("store     ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tstore[1][i],&tstore[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("square    ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tsquare[1][i],&tsquare[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("multiply  ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&tmultiply[1][i],&tmultiply[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("256-bit e ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&t256[1][i],&t256[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("512-bit e ");
  for (i = 0;i < TIMINGS;++i) {
    diff = timing_diff(&t512[1][i],&t512[0][i]);
    printf(" %7.0f",diff);
  }
  printf("\n");

  printf("Timings are in ticks. Nanoseconds per tick: approximately %f.\n"
    ,timing_basic_diff(&finishb,&startb) / timing_diff(&finish,&start));
  printf("Timings may be underestimates on systems without hardware tick support.\n");

  exit(0);
}
