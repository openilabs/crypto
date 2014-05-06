#include "gaudry.h"

#define init gaudry_init
#define hadamard gaudry_hadamard
#define mult gaudry_mult
#define square gaudry_square
#define recip gaudry_recip
#define select gaudry_select
#define todouble gaudry_todouble
#define fromdouble gaudry_fromdouble
#define surface_specify gaudry_surface_specify
#define mainloop gaudry_mainloop

void recip(double out[5],const double z[5])
{
  int i;
  double t7[5];
  double t8[5];
  double z2_5_0[5];
  double z2_10_0[5];
  double z2_25_0[5];
  double z2_50_0[5];

  /* 126 squares, 11 mults */
  /* haven't checked whether this chain is optimal */
  /* 2            */ square(t7,z);
  /* 30           */ for (i = 0;i < 3;++i) { mult(t8,t7,z); square(t7,t8); }
  /* 2^5 - 2^0    */ mult(z2_5_0,t7,z);
  /* 2^6 - 2^1    */ square(t8,z2_5_0);
  /* 2^7 - 2^2    */ square(t7,t8);
  /* 2^8 - 2^3    */ square(t8,t7);
  /* 2^9 - 2^4    */ square(t7,t8);
  /* 2^10 - 2^5   */ square(t8,t7);
  /* 2^10 - 2^0   */ mult(z2_10_0,t8,z2_5_0);
  /* 2^11 - 2^1   */ square(t8,z2_10_0);
  /* 2^19 - 2^9   */ for (i = 0;i < 4;++i) { square(t7,t8); square(t8,t7); }
  /* 2^20 - 2^10  */ square(t7,t8);
  /* 2^20 - 2^0   */ mult(t8,t7,z2_10_0);
  /* 2^21 - 2^1   */ square(t7,t8);
  /* 2^22 - 2^2   */ square(t8,t7);
  /* 2^23 - 2^3   */ square(t7,t8);
  /* 2^24 - 2^4   */ square(t8,t7);
  /* 2^25 - 2^5   */ square(t7,t8);
  /* 2^25 - 2^0   */ mult(z2_25_0,t7,z2_5_0);
  /* 2^26 - 2^1   */ square(t8,z2_25_0);
  /* 2^50 - 2^25  */ for (i = 0;i < 12;++i) { square(t7,t8); square(t8,t7); }
  /* 2^50 - 2^0   */ mult(z2_50_0,t8,z2_25_0);
  /* 2^51 - 2^1   */ square(t8,z2_50_0);
  /* 2^99 - 2^49  */ for (i = 0;i < 24;++i) { square(t7,t8); square(t8,t7); }
  /* 2^100 - 2^50 */ square(t7,t8);
  /* 2^100 - 2^0  */ mult(t8,t7,z2_50_0);
  /* 2^124 - 2^24 */ for (i = 0;i < 12;++i) { square(t7,t8); square(t8,t7); }
  /* 2^125 - 2^25 */ square(t7,t8);
  /* 2^125 - 1    */ mult(t8,t7,z2_25_0);
  /* 2^126 - 2    */ square(t7,t8);
  /* 2^127 - 4    */ square(t8,t7);
  /* 2^127 - 3    */ mult(out,t8,z);
}

static double gaudry_pm_surface_params[30];
#define AAoverBB (gaudry_pm_surface_params + 0)
#define AAoverCC (gaudry_pm_surface_params + 5)
#define AAoverDD (gaudry_pm_surface_params + 10)
#define aoverb (gaudry_pm_surface_params + 15)
#define aoverc (gaudry_pm_surface_params + 20)
#define aoverd (gaudry_pm_surface_params + 25)
static double zero[20];

void surface_specify(
  const unsigned char astr[16],
  const unsigned char bstr[16],
  const unsigned char cstr[16],
  const unsigned char dstr[16])
{
  double t[5];
  double aabbccdd[20];
  double AABBCCDDscaled[20];

  todouble(zero + 0,astr);
  todouble(zero + 5,bstr);
  todouble(zero + 10,cstr);
  todouble(zero + 15,dstr);
  recip(t,zero + 5); mult(aoverb,zero + 0,t);
  recip(t,zero + 10); mult(aoverc,zero + 0,t);
  recip(t,zero + 15); mult(aoverd,zero + 0,t);
  square(aabbccdd + 0,zero + 0);
  square(aabbccdd + 5,zero + 5);
  square(aabbccdd + 10,zero + 10);
  square(aabbccdd + 15,zero + 15);
  hadamard(AABBCCDDscaled,aabbccdd);
  recip(t,AABBCCDDscaled + 5); mult(AAoverBB,t,AABBCCDDscaled);
  recip(t,AABBCCDDscaled + 10); mult(AAoverCC,t,AABBCCDDscaled);
  recip(t,AABBCCDDscaled + 15); mult(AAoverDD,t,AABBCCDDscaled);
}

void gaudry_pm(unsigned char ek[48],
  const unsigned char e[32],
  const unsigned char k[48])
{
  static double x1overy1z1t1[15];
  static double km[20];
  static double kmplus1[20];
  static double kn[20];
  static double kn1[20];
  double yz[5];
  double yzt[5];
  double yztrecip[5];
  double xoveryzt[5];
  double xoveryz[5];
  double xovery[5];
  double xoverz[5];
  double xovert[5];
  int i;
  int j;
  unsigned int ebit;
  unsigned int lastebit;

  init();
  todouble(x1overy1z1t1 + 0,k + 0);
  todouble(x1overy1z1t1 + 5,k + 16);
  todouble(x1overy1z1t1 + 10,k + 32);
  for (i = 0;i < 20;++i) km[i] = zero[i];
  mult(kmplus1 + 15,x1overy1z1t1 + 0,x1overy1z1t1 + 5);
  mult(kmplus1 + 10,x1overy1z1t1 + 0,x1overy1z1t1 + 10);
  mult(kmplus1 + 5,x1overy1z1t1 + 5,x1overy1z1t1 + 10);
  mult(kmplus1 + 0,kmplus1 + 15,x1overy1z1t1 + 10);
  mainloop(km,kmplus1,x1overy1z1t1,gaudry_pm_surface_params,e);
  select(kn,kn1,km,kmplus1,1 & e[0]);
  mult(yz,kn + 5,kn + 10);
  mult(yzt,yz,kn + 15);
  recip(yztrecip,yzt);
  mult(xoveryzt,kn + 0,yztrecip);
  mult(xoveryz,xoveryzt,kn + 15);
  mult(xoverz,xoveryz,kn + 5);
  mult(xovery,xoveryz,kn + 10);
  mult(xovert,xoveryzt,yz);
  fromdouble(ek + 0,xovery);
  fromdouble(ek + 16,xoverz);
  fromdouble(ek + 32,xovert);
}
