#include <stdio.h>
#include "cpucycles.h"
#include "gaudry.h"

#define TIMINGS 21
long long t[TIMINGS + 1];

void printcycles(const char *s)
{
  int i;
  int j;
  int belowj;
  int abovej;
  printf("%s",s);
  for (i = 0;i < TIMINGS;++i) t[i] = t[i + 1] - t[i];
  for (j = 0;j < TIMINGS;++j) {
    belowj = 0; for (i = 0;i < TIMINGS;++i) if (t[i] < t[j]) ++belowj;
    abovej = 0; for (i = 0;i < TIMINGS;++i) if (t[i] > t[j]) ++abovej;
    if (belowj <= TIMINGS / 2 && abovej <= TIMINGS / 2) break;
  }
  printf(" %6lld",t[j]);
  for (i = 0;i < TIMINGS;++i) printf(" %6lld",t[i]);
  printf("\n");
  fflush(stdout);
  for (i = 0;i <= TIMINGS;++i) t[i] = cpucycles();
}

double e[20];
double f[20];
double g[20];
double h[20];
unsigned char u[32];
unsigned char v[48];
unsigned char k[48] = {
  0xAA, 0xE3, 0xFF, 0xE5, 0xE2, 0x57, 0xF6, 0x1D, 0x50, 0xFF, 0xEA, 0x1A, 0xC4, 0xA7, 0xA6, 0x0A,
  0xAF, 0x8B, 0xC4, 0xF2, 0xA5, 0xFA, 0x5F, 0xEF, 0xF5, 0x0F, 0x78, 0x58, 0xCA, 0xC3, 0x2B, 0x4D,
  0xE7, 0xF3, 0xE0, 0x46, 0xD0, 0x2C, 0x3F, 0x75, 0x9C, 0x45, 0xD8, 0x40, 0xE5, 0x81, 0xFA, 0x35,
};

main()
{
  int i;

  for (i = 0;i < 32;++i) u[i] = random();

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
  }
  printcycles("nothing       ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry_hadamard(e,f);
  }
  printcycles("hadamard      ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry_square(h,f);
  }
  printcycles("square        ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry_mult(h,f,g);
  }
  printcycles("mult          ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry_select(e,f,g,h,1);
  }
  printcycles("select        ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry_recip(h,f);
  }
  printcycles("recip         ");

  for (i = 0;i <= TIMINGS;++i) { t[i] = cpucycles();
    gaudry(v,u,k);
  }
  printcycles("gaudry        ");

  return 0;
}
