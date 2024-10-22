#include "zmodexp.h"

/* XXX: using double instead of long double; won't work with spills */

static double two30 = 1073741824.0;
static double twom30 = .000000000931322574615478515625;
static double alpha0 = 13835058055282163712.0;
static double alpha30 = 14855280471424563298789490688.0;
static double beta30 = -536870911.875;
/* XXX: const here makes gcc do some silly things */

#define R r->x
#define S s->x
#define M m->x
#define Y m->y
#define INV m->inv
#define T m->t
#define Q m->q

#define V *(volatile double *)&

static void to30(register double out[18],register const uint32 in[16])
{
  register int i;
  register uint32 b;
  register uint32 c;
  register double u;
  register double z;

  u = in[0];
  z = V alpha30;
  z += u;
  b = 0;
  i = 1;
  z -= alpha30;
  u -= z;
  z *= twom30;
  out[0] = u;
  u = z;

  do {
    c = in[i];
    c <<= i + i;
    b += c;
    u += b;
    b = in[i];
    z = V alpha30;
    z += u;
    b >>= 30 - i - i;
    z -= alpha30;
    b &= ~3;
    ++i;
    u -= z;
    z *= twom30;
    out[i - 1] = u;
    u = z;
  }
  while (i < 16);

  u += b;
  z = V alpha30;
  z += u;
  z -= alpha30;
  u -= z;
  z *= twom30;

  out[16] = u;
  out[17] = z;
}

void zmodexp512_load(zmodexp512_m *m,register zmodexp512_r *r,register const uint32 r32[16])
{
  to30(R,r32);
}

void zmodexp512_store(register zmodexp512_m *m,register zmodexp512_r *r,register uint32 r32[16])
{
  register int i;
  register uint32 b;
  register uint32 c;
  register uint32 result;
  register double u;
  register double q;
  register double z;
  register double t8;

  q = R[16] * twom30;
  q += R[17];
  q *= Y;
  q += alpha0;
  q -= alpha0;

  u = 0;
  for (i = 0;i < 17;++i) {
    t8 = M[i] * q;
    u += R[i];
    u -= t8;
    z = V beta30;
    z += u;
    z += alpha30;
    z -= alpha30;
    u -= z;
    z *= twom30;
    T[i] = u;
    u = z;
  }

  t8 = M[17] * q;
  u += R[17];
  u -= t8;
  T[17] = u;

  u += beta30;
  u += alpha30;
  u -= alpha30;
  q = u * twom30; /* either 0 or -1 */

  u = 0;
  for (i = 0;i < 17;++i) {
    t8 = M[i] * q;
    u += T[i];
    u -= t8;
    z = V beta30;
    z += u;
    z += alpha30;
    z -= alpha30;
    u -= z;
    z *= twom30;
    T[i] = u;
    u = z;
  }
  t8 = M[17] * q;
  u += T[17];
  u -= t8;
  T[17] = u;

  result = (int) T[0];

  for (i = 1;i < 16;++i) {
    b = (int) T[i];
    c = b;

    b <<= 32 - i - i;
    c >>= i + i;

    result += b;
    r32[i - 1] = result;
    result = c;
  }

  b = (uint32) (T[16] + T[17] * two30);
  result += b;
  r32[15] = result;
}

void zmodexp512_init(register zmodexp512_m *m,register const uint32 m32[16])
{
  register int i;
  register int j;
  register double top;
  register double u;
  register double t;
  register double z;

  asm volatile("fldcw %0"::"m"(0x137f));
  to30(M,m32);

  top = M[16] * twom30;
  top += M[17];

  if (top < 1.0) { top = 1.0; M[17] = top; M[16] = 0; }

  Y = 1.0 / top;
  u = Y;
  u *= two30;
  u += alpha0;
  u -= alpha0;
  INV[17] = -u;

  u = two30;
  u += INV[17] * M[17];
  u *= two30;

  for (i = 16;i >= 0;--i) {
    for (j = i + 1;j <= 17;++j)
      u += INV[j] * M[i + 17 - j];

    t = u * Y;
    z = t + alpha30;
    z -= alpha30;
    u -= z * top;
    t -= z;
    z *= twom30;
    t += alpha0;
    t -= alpha0;
    u -= t * M[17];

    INV[i + 1] -= z;
    INV[i] = -t;

    u *= two30;
  }

  for (j = 0;j <= 16;++j)
    u += INV[j] * M[16 - j];
  t = u * Y;
  z = t + alpha30;
  z -= alpha30;
  z *= twom30;
  INV[0] -= z;
}

static void addlow(register double out[18],register const double x[18],register const double y[18],register double *carry)
{
register double z;
register double u;
register double t5;
register double t6;
register double t7;
register double t8;

u = V out[0];
t8 = V x[0];
t8 *= y[0];
t7 = V x[0];
t7 *= y[1];
u += t8;
t6 = V x[1];
z = V alpha30;
z += u;
t6 *= y[0];
t7 += out[1];
z -= alpha30;
t5 = V x[0];
t5 *= y[2];
u -= z;
z *= twom30;
t8 = V x[1];
t7 += t6;
out[0] = u;
z += t7;
t8 *= y[1];
u = V alpha30;
u += z;
t7 = V x[2];
t7 *= y[0];
u -= alpha30;
t5 += t8;
t7 += out[2];
z -= u;
u *= twom30;
t5 += t7;
t6 = V x[0];
out[1] = z;
t7 = V x[3];
u += t5;
t6 *= y[3];
z = V alpha30;
z += u;
t5 = V x[1];
t5 *= y[2];
z -= alpha30;
t8 = V x[2];
t8 *= y[1];
u -= z;
z *= twom30;
t6 += t5;
t7 *= y[0];
t6 += t8;
out[2] = u;
z += out[3];
t7 += t6;
t6 = V x[0];
t6 *= y[4];
z += t7;
t5 = V x[1];
t5 *= y[3];
u = V alpha30;
u += z;
t8 = V x[2];
t8 *= y[2];
u -= alpha30;
t6 += t5;
t7 = V x[3];
t7 *= y[1];
z -= u;
u *= twom30;
t6 += t8;
t5 = V x[4];
t5 *= y[0];
t6 += t7;
out[3] = z;
u += out[4];
t6 += t5;
t8 = V x[0];
t8 *= y[5];
u += t6;
t7 = V x[1];
t7 *= y[4];
z = V alpha30;
z += u;
t6 = V x[2];
t6 *= y[3];
t8 += t7;
z -= alpha30;
t5 = V x[3];
t5 *= y[2];
t8 += t6;
u -= z;
z *= twom30;
t7 = V x[4];
t7 *= y[1];
t8 += t5;
out[4] = u;
t6 = V x[5];
t6 *= y[0];
z += out[5];
t8 += t7;
t5 = V x[0];
t5 *= y[6];
t8 += t6;
t7 = V x[2];
t7 *= y[4];
z += t8;
t8 = V x[1];
t8 *= y[5];
t5 += t7;
u = V alpha30;
u += z;
t6 = V x[3];
t6 *= y[3];
t5 += t8;
u -= alpha30;
t8 = V x[4];
t8 *= y[2];
t5 += t6;
z -= u;
u *= twom30;
t7 = V x[5];
t7 *= y[1];
t5 += t8;
out[5] = z;
t6 = V x[6];
t6 *= y[0];
u += out[6];
t5 += t7;
t8 = V x[1];
t8 *= y[6];
t5 += t6;
t7 = V x[2];
t7 *= y[5];
u += t5;
t5 = V x[0];
t5 *= y[7];
z = V alpha30;
z += u;
t6 = V x[3];
t6 *= y[4];
t5 += t8;
z -= alpha30;
t8 = V x[4];
t8 *= y[3];
t5 += t7;
u -= z;
z *= twom30;
t5 += t6;
t7 = V x[5];
t7 *= y[2];
t5 += t8;
out[6] = u;
t6 = V x[6];
t6 *= y[1];
z += out[7];
t5 += t7;
t8 = V x[7];
t8 *= y[0];
t5 += t6;
t7 = V x[0];
t7 *= y[8];
t5 += t8;
t6 = V x[1];
t6 *= y[7];
z += t5;
t5 = V x[2];
t5 *= y[6];
u = V alpha30;
u += z;
t7 += t6;
t8 = V x[3];
t8 *= y[5];
u -= alpha30;
t7 += t5;
t6 = V x[4];
t6 *= y[4];
z -= u;
u *= twom30;
t7 += t8;
t5 = V x[5];
t5 *= y[3];
out[7] = z;
t8 = V x[6];
t7 += t6;
t8 *= y[2];
u += out[8];
t7 += t5;
t6 = V x[7];
t6 *= y[1];
t7 += t8;
t5 = V x[8];
t5 *= y[0];
t7 += t6;
t8 = V x[0];
t8 *= y[9];
t7 += t5;
t6 = V x[2];
t6 *= y[7];
u += t7;
t7 = V x[1];
t7 *= y[8];
z = V alpha30;
z += u;
t8 += t7;
t5 = V x[3];
t5 *= y[6];
t8 += t6;
z -= alpha30;
t7 = V x[4];
t7 *= y[5];
t8 += t5;
u -= z;
z *= twom30;
t6 = V x[5];
t6 *= y[4];
t8 += t7;
out[8] = u;
t5 = V x[6];
z += out[9];
t5 *= y[3];
t8 += t6;
t7 = V x[7];
t7 *= y[2];
t8 += t5;
t6 = V x[8];
t6 *= y[1];
t8 += t7;
t5 = V x[9];
t5 *= y[0];
t8 += t6;
t7 = V x[1];
t7 *= y[9];
t8 += t5;
t6 = V x[2];
t6 *= y[8];
z += t8;
t8 = V x[0];
t8 *= y[10];
u = V alpha30;
u += z;
t8 += t7;
t5 = V x[3];
t5 *= y[7];
t8 += t6;
u -= alpha30;
t7 = V x[4];
t7 *= y[6];
t8 += t5;
z -= u;
u *= twom30;
t6 = V x[5];
t6 *= y[5];
t8 += t7;
out[9] = z;
t5 = V x[6];
t5 *= y[4];
t8 += t6;
u += out[10];
t7 = V x[7];
t7 *= y[3];
t8 += t5;
t6 = V x[8];
t6 *= y[2];
t8 += t7;
t5 = V x[9];
t5 *= y[1];
t8 += t6;
t7 = V x[10];
t7 *= y[0];
t8 += t5;
t6 = V x[0];
t6 *= y[11];
t8 += t7;
t5 = V x[1];
t5 *= y[10];
u += t8;
t8 = V x[2];
t8 *= y[9];
z = V alpha30;
z += u;
t6 += t5;
t7 = V x[3];
t7 *= y[8];
z -= alpha30;
t6 += t8;
t5 = V x[4];
t5 *= y[7];
u -= z;
t6 += t7;
z *= twom30;
t8 = V x[5];
t8 *= y[6];
t6 += t5;
out[10] = u;
t7 = V x[6];
t7 *= y[5];
z += out[11];
t6 += t8;
t5 = V x[7];
t5 *= y[4];
t6 += t7;
t8 = V x[8];
t8 *= y[3];
t6 += t5;
t7 = V x[9];
t7 *= y[2];
t6 += t8;
t5 = V x[10];
t5 *= y[1];
t6 += t7;
t8 = V x[11];
t8 *= y[0];
t6 += t5;
t7 = V x[0];
t7 *= y[12];
t6 += t8;
t5 = V x[2];
t5 *= y[10];
z += t6;
t6 = V x[1];
t6 *= y[11];
u = V alpha30;
u += z;
t7 += t6;
t8 = V x[3];
t8 *= y[9];
t7 += t5;
u -= alpha30;
t6 = V x[4];
t6 *= y[8];
t7 += t8;
z -= u;
u *= twom30;
t5 = V x[5];
t5 *= y[7];
t7 += t6;
out[11] = z;
t8 = V x[6];
t8 *= y[6];
u += out[12];
t7 += t5;
t6 = V x[7];
t6 *= y[5];
t7 += t8;
t5 = V x[8];
t5 *= y[4];
t7 += t6;
t8 = V x[9];
t8 *= y[3];
t7 += t5;
t6 = V x[10];
t6 *= y[2];
t7 += t8;
t5 = V x[11];
t5 *= y[1];
t7 += t6;
t8 = V x[12];
t8 *= y[0];
t7 += t5;
t6 = V x[1];
t6 *= y[12];
t7 += t8;
t5 = V x[2];
t5 *= y[11];
u += t7;
t7 = V x[0];
t7 *= y[13];
z = V alpha30;
z += u;
t7 += t6;
t8 = V x[3];
t8 *= y[10];
t7 += t5;
z -= alpha30;
t6 = V x[4];
t6 *= y[9];
t7 += t8;
u -= z;
z *= twom30;
t5 = V x[5];
t5 *= y[8];
t7 += t6;
out[12] = u;
t8 = V x[6];
t8 *= y[7];
z += out[13];
t7 += t5;
t6 = V x[7];
t6 *= y[6];
t7 += t8;
t5 = V x[8];
t5 *= y[5];
t7 += t6;
t8 = V x[9];
t8 *= y[4];
t7 += t5;
t6 = V x[10];
t6 *= y[3];
t7 += t8;
t5 = V x[11];
t5 *= y[2];
t7 += t6;
t8 = V x[12];
t8 *= y[1];
t7 += t5;
t6 = V x[13];
t6 *= y[0];
t7 += t8;
t5 = V x[0];
t5 *= y[14];
t7 += t6;
t8 = V x[1];
t8 *= y[13];
z += t7;
t7 = V x[2];
t7 *= y[12];
t5 += t8;
u = V alpha30;
u += z;
t6 = V x[3];
t6 *= y[11];
t5 += t7;
u -= alpha30;
t8 = V x[4];
t8 *= y[10];
t5 += t6;
z -= u;
u *= twom30;
t7 = V x[5];
t7 *= y[9];
t5 += t8;
out[13] = z;
t6 = V x[6];
t6 *= y[8];
u += out[14];
t5 += t7;
t8 = V x[7];
t8 *= y[7];
t5 += t6;
t7 = V x[8];
t7 *= y[6];
t5 += t8;
t6 = V x[9];
t6 *= y[5];
t5 += t7;
t8 = V x[10];
t8 *= y[4];
t5 += t6;
t7 = V x[11];
t7 *= y[3];
t5 += t8;
t6 = V x[12];
t6 *= y[2];
t5 += t7;
t8 = V x[13];
t8 *= y[1];
t5 += t6;
t7 = V x[14];
t7 *= y[0];
t5 += t8;
t6 = V x[0];
t6 *= y[15];
t5 += t7;
t8 = V x[2];
t8 *= y[13];
u += t5;
t5 = V x[1];
t5 *= y[14];
z = V alpha30;
z += u;
t6 += t5;
t7 = V x[3];
t7 *= y[12];
t6 += t8;
z -= alpha30;
t5 = V x[4];
t5 *= y[11];
t6 += t7;
u -= z;
z *= twom30;
t8 = V x[5];
t8 *= y[10];
t6 += t5;
out[14] = u;
t7 = V x[6];
t7 *= y[9];
z += out[15];
t6 += t8;
t5 = V x[7];
t5 *= y[8];
t6 += t7;
t8 = V x[8];
t8 *= y[7];
t6 += t5;
t7 = V x[9];
t7 *= y[6];
t6 += t8;
t5 = V x[10];
t5 *= y[5];
t6 += t7;
t8 = V x[11];
t8 *= y[4];
t6 += t5;
t7 = V x[12];
t7 *= y[3];
t6 += t8;
t5 = V x[13];
t5 *= y[2];
t6 += t7;
t8 = V x[14];
t8 *= y[1];
t6 += t5;
t7 = V x[15];
t7 *= y[0];
t6 += t8;
t5 = V x[1];
t5 *= y[15];
t6 += t7;
t8 = V x[2];
t8 *= y[14];
z += t6;
t6 = V x[0];
t6 *= y[16];
u = V alpha30;
u += z;
t6 += t5;
t7 = V x[3];
t7 *= y[13];
t6 += t8;
u -= alpha30;
t5 = V x[4];
t5 *= y[12];
t6 += t7;
z -= u;
u *= twom30;
t8 = V x[5];
t8 *= y[11];
t6 += t5;
out[15] = z;
t7 = V x[6];
t7 *= y[10];
u += out[16];
t6 += t8;
t5 = V x[7];
t5 *= y[9];
t6 += t7;
t8 = V x[8];
t8 *= y[8];
t6 += t5;
t7 = V x[9];
t7 *= y[7];
t6 += t8;
t5 = V x[10];
t5 *= y[6];
t6 += t7;
t8 = V x[11];
t8 *= y[5];
t6 += t5;
t7 = V x[12];
t7 *= y[4];
t6 += t8;
t5 = V x[13];
t5 *= y[3];
t6 += t7;
t8 = V x[14];
t8 *= y[2];
t6 += t5;
t7 = V x[15];
t7 *= y[1];
t6 += t8;
t5 = V x[16];
t5 *= y[0];
t6 += t7;
t8 = V x[0];
t8 *= y[17];
t6 += t5;
t7 = V x[1];
t7 *= y[16];
u += t6;
t6 = V x[2];
t6 *= y[15];
t8 += t7;
z = V alpha30;
z += u;
t5 = V x[3];
t5 *= y[14];
t8 += t6;
z -= alpha30;
t7 = V x[4];
t7 *= y[13];
t8 += t5;
u -= z;
z *= twom30;
t6 = V x[5];
t6 *= y[12];
t8 += t7;
out[16] = u;
t5 = V x[6];
t5 *= y[11];
z += out[17];
t8 += t6;
t7 = V x[7];
t7 *= y[10];
t8 += t5;
t6 = V x[8];
t6 *= y[9];
t8 += t7;
t5 = V x[9];
t5 *= y[8];
t8 += t6;
t7 = V x[10];
t7 *= y[7];
t8 += t5;
t6 = V x[11];
t6 *= y[6];
t8 += t7;
t5 = V x[12];
t5 *= y[5];
t8 += t6;
t7 = V x[13];
t7 *= y[4];
t8 += t5;
t6 = V x[14];
t6 *= y[3];
t8 += t7;
t5 = V x[15];
t5 *= y[2];
t8 += t6;
t7 = V x[16];
t7 *= y[1];
t8 += t5;
t6 = V x[17];
t6 *= y[0];
z += t7;

t8 += t6;

z += t8;
u = V alpha30;

u += z;

u -= alpha30;

z -= u;
u *= twom30;

out[17] = z;
*carry = u;
}

static inline void mid(register const double x[18],register const double y[18],register double *carry)
{
  register double u;
  register double t6, t7;

  u = x[0] * y[17];
  t7 = x[1] * y[16];
  t6 = x[2] * y[15];
  u += t7;
  t7 = x[3] * y[14];
  u += t6;
  t6 = x[4] * y[13];
  u += t7;
  t7 = x[5] * y[12];
  u += t6;
  t6 = x[6] * y[11];
  u += t7;
  t7 = x[7] * y[10];
  u += t6;
  t6 = x[8] * y[9];
  u += t7;
  t7 = x[9] * y[8];
  u += t6;
  t6 = x[10] * y[7];
  u += t7;
  t7 = x[11] * y[6];
  u += t6;
  t6 = x[12] * y[5];
  u += t7;
  t7 = x[13] * y[4];
  u += t6;
  t6 = x[14] * y[3];
  u += t7;
  t7 = x[15] * y[2];
  u += t6;
  t6 = x[16] * y[1];
  u += t7;
  t7 = x[17] * y[0];
  u += t6;

  u += t7;
  u += alpha30;
  u -= alpha30;
  u *= twom30;
  *carry = u;
}

static void sethigh(register double out[17],register const double x[18],register const double y[18],double *carry)
{
register double z;
register double u;
register double t5;
register double t6;
register double t7;
register double t8;

u = *carry;
t8 = V x[1];
t8 *= y[17];
t6 = V x[2];
t6 *= y[16];
t5 = V x[3];
t5 *= y[15];
t8 += t6;
t7 = V x[4];
t7 *= y[14];
t8 += t5;
t6 = V x[5];
t6 *= y[13];
t8 += t7;
t5 = V x[6];
t5 *= y[12];
t8 += t6;
t7 = V x[7];
t7 *= y[11];
t8 += t5;
t6 = V x[8];
t6 *= y[10];
t8 += t7;
t5 = V x[9];
t5 *= y[9];
t8 += t6;
t7 = V x[10];
t7 *= y[8];
t8 += t5;
t6 = V x[11];
t6 *= y[7];
t8 += t7;
t5 = V x[12];
t5 *= y[6];
t8 += t6;
t7 = V x[13];
t7 *= y[5];
t8 += t5;
t6 = V x[14];
t6 *= y[4];
t8 += t7;
t5 = V x[15];
t5 *= y[3];
t8 += t6;
t7 = V x[16];
t7 *= y[2];
t8 += t5;
t6 = V x[17];
t6 *= y[1];
u += t7;
t5 = V x[2];
t5 *= y[17];
t8 += t6;
t7 = V x[3];
t7 *= y[16];
u += t8;
t6 = V x[4];
z = V alpha30;
z += u;
t6 *= y[15];
t5 += t7;
z -= alpha30;
t8 = V x[5];
t8 *= y[14];
t5 += t6;
u -= z;
z *= twom30;
t7 = V x[6];
t7 *= y[13];
t5 += t8;
out[0] = u;
t6 = V x[7];
t6 *= y[12];
t5 += t7;
t8 = V x[8];
t8 *= y[11];
t5 += t6;
t7 = V x[9];
t7 *= y[10];
t5 += t8;
t6 = V x[10];
t6 *= y[9];
t5 += t7;
t8 = V x[11];
t8 *= y[8];
t5 += t6;
t7 = V x[12];
t7 *= y[7];
t5 += t8;
t6 = V x[13];
t6 *= y[6];
t5 += t7;
t8 = V x[14];
t8 *= y[5];
t5 += t6;
t7 = V x[15];
t7 *= y[4];
t5 += t8;
t6 = V x[16];
t6 *= y[3];
t5 += t7;
t8 = V x[17];
t8 *= y[2];
z += t6;
t7 = V x[3];
t5 += t8;
t7 *= y[17];
t8 = V x[5];
z += t5;
t5 = V x[4];
t5 *= y[16];
u = V alpha30;
u += z;
t8 *= y[15];
t7 += t5;
u -= alpha30;
t6 = V x[6];
t6 *= y[14];
t7 += t8;
z -= u;
u *= twom30;
t5 = V x[7];
t5 *= y[13];
t7 += t6;
out[1] = z;
t8 = V x[8];
t8 *= y[12];
t7 += t5;
t6 = V x[9];
t6 *= y[11];
t7 += t8;
t5 = V x[10];
t5 *= y[10];
t7 += t6;
t8 = V x[11];
t8 *= y[9];
t7 += t5;
t6 = V x[12];
t6 *= y[8];
t7 += t8;
t5 = V x[13];
t5 *= y[7];
t7 += t6;
t8 = V x[14];
t8 *= y[6];
t7 += t5;
t6 = V x[15];
t6 *= y[5];
t7 += t8;
t5 = V x[16];
t5 *= y[4];
t7 += t6;
t8 = V x[17];
t8 *= y[3];
u += t5;
t5 = V x[5];
t7 += t8;
t5 *= y[16];
t8 = V x[6];
u += t7;
t7 = V x[4];
t7 *= y[17];
z = V alpha30;
z += u;
t8 *= y[15];
t7 += t5;
z -= alpha30;
t6 = V x[7];
t6 *= y[14];
t7 += t8;
u -= z;
z *= twom30;
t5 = V x[8];
t5 *= y[13];
t7 += t6;
out[2] = u;
t8 = V x[9];
t8 *= y[12];
t7 += t5;
t6 = V x[10];
t6 *= y[11];
t7 += t8;
t5 = V x[11];
t5 *= y[10];
t7 += t6;
t8 = V x[12];
t8 *= y[9];
t7 += t5;
t6 = V x[13];
t6 *= y[8];
t7 += t8;
t5 = V x[14];
t5 *= y[7];
t7 += t6;
t8 = V x[15];
t8 *= y[6];
t7 += t5;
t6 = V x[16];
t6 *= y[5];
t7 += t8;
t5 = V x[17];
t5 *= y[4];
z += t6;
t8 = V x[5];
t7 += t5;
t8 *= y[17];
t6 = V x[6];
z += t7;
t6 *= y[16];
u = V alpha30;
u += z;
t5 = V x[7];
t5 *= y[15];
t8 += t6;
u -= alpha30;
t7 = V x[8];
t7 *= y[14];
t8 += t5;
z -= u;
u *= twom30;
t6 = V x[9];
t6 *= y[13];
t8 += t7;
out[3] = z;
t5 = V x[10];
t5 *= y[12];
t8 += t6;
t7 = V x[11];
t7 *= y[11];
t8 += t5;
t6 = V x[12];
t6 *= y[10];
t8 += t7;
t5 = V x[13];
t5 *= y[9];
t8 += t6;
t7 = V x[14];
t7 *= y[8];
t8 += t5;
t6 = V x[15];
t6 *= y[7];
t8 += t7;
t5 = V x[16];
t5 *= y[6];
t8 += t6;
t7 = V x[17];
t7 *= y[5];
u += t5;
t6 = V x[6];
t8 += t7;
t6 *= y[17];
t7 = V x[8];
u += t8;
t8 = V x[7];
t8 *= y[16];
z = V alpha30;
z += u;
t7 *= y[15];
t6 += t8;
z -= alpha30;
t5 = V x[9];
t5 *= y[14];
t6 += t7;
u -= z;
z *= twom30;
t8 = V x[10];
t8 *= y[13];
t6 += t5;
out[4] = u;
t7 = V x[11];
t7 *= y[12];
t6 += t8;
t5 = V x[12];
t5 *= y[11];
t6 += t7;
t8 = V x[13];
t8 *= y[10];
t6 += t5;
t7 = V x[14];
t7 *= y[9];
t6 += t8;
t5 = V x[15];
t5 *= y[8];
t6 += t7;
t8 = V x[16];
t8 *= y[7];
t6 += t5;
t7 = V x[17];
t7 *= y[6];
z += t8;
t8 = V x[8];
t6 += t7;
t8 *= y[16];
t7 = V x[9];
z += t6;
t6 = V x[7];
t6 *= y[17];
u = V alpha30;
u += z;
t7 *= y[15];
t6 += t8;
u -= alpha30;
t5 = V x[10];
t5 *= y[14];
t6 += t7;
z -= u;
u *= twom30;
t8 = V x[11];
t8 *= y[13];
t6 += t5;
out[5] = z;
t7 = V x[12];
t7 *= y[12];
t6 += t8;
t5 = V x[13];
t5 *= y[11];
t6 += t7;
t8 = V x[14];
t8 *= y[10];
t6 += t5;
t7 = V x[15];
t7 *= y[9];
t6 += t8;
t5 = V x[16];
t5 *= y[8];
t6 += t7;
t8 = V x[17];
t8 *= y[7];
u += t5;
t7 = V x[8];
t6 += t8;
t7 *= y[17];
t5 = V x[9];
u += t6;
t5 *= y[16];
z = V alpha30;
z += u;
t8 = V x[10];
t8 *= y[15];
t7 += t5;
z -= alpha30;
t6 = V x[11];
t6 *= y[14];
u -= z;
z *= twom30;
t7 += t8;
t5 = V x[12];
t5 *= y[13];
out[6] = u;
t8 = V x[13];
t7 += t6;
t8 *= y[12];
t6 = V x[14];
t7 += t5;
t6 *= y[11];
t5 = V x[15];
t7 += t8;
t5 *= y[10];
t8 = V x[16];
t7 += t6;
t8 *= y[9];
t6 = V x[17];
t7 += t5;
t6 *= y[8];
z += t8;
t5 = V x[9];
t7 += t6;
t5 *= y[17];
t6 = V x[11];
z += t7;
t7 = V x[10];
t7 *= y[16];
u = V alpha30;
u += z;
t6 *= y[15];
t5 += t7;
u -= alpha30;
t8 = V x[12];
t8 *= y[14];
t5 += t6;
z -= u;
u *= twom30;
t7 = V x[13];
t7 *= y[13];
t5 += t8;
out[7] = z;
t6 = V x[14];
t6 *= y[12];
t5 += t7;
t8 = V x[15];
t8 *= y[11];
t5 += t6;
t7 = V x[16];
t7 *= y[10];
t5 += t8;
t6 = V x[17];
t6 *= y[9];
u += t7;
t7 = V x[11];
t5 += t6;
t7 *= y[16];
t6 = V x[12];
u += t5;
t5 = V x[10];
t5 *= y[17];
z = V alpha30;
z += u;
t6 *= y[15];
t5 += t7;
z -= alpha30;
t8 = V x[13];
t8 *= y[14];
t5 += t6;
u -= z;
z *= twom30;
t7 = V x[14];
t7 *= y[13];
t5 += t8;
out[8] = u;
t6 = V x[15];
t6 *= y[12];
t5 += t7;
t8 = V x[16];
t8 *= y[11];
t5 += t6;
t7 = V x[17];
t7 *= y[10];
z += t8;
t8 = V x[12];
t8 *= y[16];
t5 += t7;
t6 = V x[11];
t6 *= y[17];
z += t5;
t7 = V x[13];
t7 *= y[15];
t6 += t8;
u = V alpha30;
u += z;
t5 = V x[14];
t5 *= y[14];
t6 += t7;
u -= alpha30;
t8 = V x[15];
t8 *= y[13];
t6 += t5;
z -= u;
u *= twom30;
t7 = V x[16];
t7 *= y[12];
t6 += t8;
out[9] = z;
t5 = V x[17];
t5 *= y[11];
u += t7;
t8 = V x[12];
t6 += t5;
t8 *= y[17];
t5 = V x[14];
u += t6;
t5 *= y[15];
z = V alpha30;
z += u;
t6 = V x[13];
t6 *= y[16];
z -= alpha30;
t8 += t6;
t7 = V x[15];
t7 *= y[14];
u -= z;
z *= twom30;
t8 += t5;
t6 = V x[16];
t6 *= y[13];
t8 += t7;
out[10] = u;
t5 = V x[17];
t5 *= y[12];
z += t6;
t6 = V x[14];
t8 += t5;
t6 *= y[16];
t5 = V x[15];
z += t8;
t5 *= y[15];
u = V alpha30;
u += z;
t8 = V x[13];
t8 *= y[17];
u -= alpha30;
t7 = V x[16];
t7 *= y[14];
z -= u;
t8 += t6;
t6 = V x[17];
t6 *= y[13];
out[11] = z;
u *= twom30;
t8 += t6;
u += t7;
t6 = V x[16];
t8 += t5;
u += t8;
t6 *= y[15];
z = V alpha30;
z += u;
t5 = V x[14];
t5 *= y[17];
z -= alpha30;
t7 = V x[15];
t7 *= y[16];
u -= z;
z *= twom30;
t5 += t7;
t8 = V x[17];
t8 *= y[14];
out[12] = u;
t5 += t8;
z += t6;
t7 = V x[15];
t7 *= y[17];
z += t5;
t5 = V x[16];
u = V alpha30;
u += z;
t5 *= y[16];
t8 = V x[17];
u -= alpha30;
t7 += t5;
t8 *= y[15];
z -= u;
u *= twom30;
t7 += t8;
t5 = V x[17];
out[13] = z;
u += t7;
t5 *= y[16];
z = V alpha30;
z += u;
t7 = V x[16];
t7 *= y[17];
z -= alpha30;
t8 = V x[17];
t5 += t7;
u -= z;
z *= twom30;
t8 *= y[17];

z += t5;
out[14] = u;
u = V alpha30;
u += z;

u -= alpha30;

z -= u;
u *= twom30;

out[15] = z;
u += t8;
z = V alpha30;

z += u;

z -= alpha30;

u -= z;
z *= twom30;

out[16] = u;
*carry = z;
}

void zmodexp512_multiply(register zmodexp512_m *m,register zmodexp512_r *r,register const zmodexp512_r *s)
{
  T[0] = 0;
  T[1] = 0;
  T[2] = 0;
  T[3] = 0;
  T[4] = 0;
  T[5] = 0;
  T[6] = 0;
  T[7] = 0;
  T[8] = 0;
  T[9] = 0;
  T[10] = 0;
  T[11] = 0;
  T[12] = 0;
  T[13] = 0;
  T[14] = 0;
  T[15] = 0;
  T[16] = 0;
  T[17] = 0;

  addlow(T,R,S,&m->carry);
  sethigh(T + 18,R,S,&m->carry);
  mid(T + 17,INV,&Q[17]);
  sethigh(Q,T + 17,INV,&Q[17]);
  addlow(T,Q,M,&m->carry);

  R[0] = T[0];
  R[1] = T[1];
  R[2] = T[2];
  R[3] = T[3];
  R[4] = T[4];
  R[5] = T[5];
  R[6] = T[6];
  R[7] = T[7];
  R[8] = T[8];
  R[9] = T[9];
  R[10] = T[10];
  R[11] = T[11];
  R[12] = T[12];
  R[13] = T[13];
  R[14] = T[14];
  R[15] = T[15];
  R[16] = T[16];
  R[17] = T[17];
}

void zmodexp512_square(register zmodexp512_m *m,register zmodexp512_r *r)
{
  zmodexp512_multiply(m,r,r);
}
/* on original Pentium and Pentium Pro, no room left in code cache */
