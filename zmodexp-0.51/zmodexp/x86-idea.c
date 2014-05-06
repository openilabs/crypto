#include "zmodexp.h"

static const double two30 = 1073741824.0;
static const double twom30 = .000000000931322574615478515625;
static const double alpha0 = 13835058055282163712.0;
static const double alpha30 = 14855280471424563298789490688.0;
static const double beta30 = -536870911.875;

#define R r->x
#define S s->x
#define M m->x
#define Y m->y
#define INV m->inv
#define T m->t
#define Q m->q

static inline long double round0(register long double u)
{
  u += alpha0;
  u -= alpha0;
  return u;
}

static inline long double round30(register long double u)
{
  u += alpha30;
  u -= alpha30;
  return u;
}

static inline long double floor30(register long double u)
{
  u += beta30;
  return round30(u);
}

static void to30(register double out[18],register const uint32 in[16])
{
  register int i;
  register uint32 b;
  register uint32 c;
  register long double u;
  register long double z;

  u = 0;
  b = 0;
  for (i = 0;i < 16;++i) {
    c = in[i];
    c <<= i + i;
    b += c;
    u += b;
    z = round30(u); u -= z; z *= twom30;
    out[i] = u;
    b = in[i];
    b >>= 30 - i - i;
    b &= ~3;
    u = z;
  }

  u += b;
  z = round30(u); u -= z; z *= twom30;

  out[16] = u;
  out[17] = z;
}

void zmodexp512_load(zmodexp512_m *m,register zmodexp512_r *r,register const uint32 r32[16])
{
  to30(R,r32);
}

void zmodexp512_init(register zmodexp512_m *m,register const uint32 m32[16])
{
  int loop;
  int i;
  int j;
  register long double top;
  register long double u;
  register long double t;
  register long double z;

  asm volatile("fldcw %0"::"m"(0x137f));

  to30(M,m32);

  top = M[16] * twom30;
  top += M[17];

  if (top < 1.0) { top = 1.0; M[17] = top; M[16] = 0; }

  Y = 1.0 / top;
  INV[17] = -round0(two30 * Y);

  u = two30;
  u += INV[17] * (long double) M[17];
  u *= two30;

  for (i = 16;i >= 0;--i) {
    for (j = i + 1;j <= 17;++j)
      u += INV[j] * (long double) M[i + 17 - j];

    t = u * Y;
    z = round30(t);
    u -= z * top;
    t -= z;
    z *= twom30;
    t = round0(t);
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

void zmodexp512_store(register zmodexp512_m *m,register zmodexp512_r *r,register uint32 r32[16])
{
  register int i;
  register uint32 b;
  register uint32 c;
  register uint32 result;
  register long double u;
  register long double q;
  register long double z;

  q = R[16] * twom30;
  q += R[17];
  q = round0(q * Y);

  u = 0;
  for (i = 0;i < 17;++i) {
    u += R[i];
    u -= q * M[i];
    z = floor30(u); u -= z; z *= twom30;
    T[i] = u;
    u = z;
  }

  u += R[17];
  u -= q * M[17];
  T[17] = u;

  q = floor30(u) * twom30; /* either 0 or -1 */

  u = 0;
  for (i = 0;i < 17;++i) {
    u += T[i];
    u -= q * M[i];
    z = floor30(u); u -= z; z *= twom30;
    T[i] = u;
    u = z;
  }
  u += T[17];
  u -= q * M[17];
  T[17] = u;

  /* now 0 <= T < n */

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

static double addlow(register double out[18],register const double x[18],register const double y[18])
{
  register long double u;
  register long double z;
  register int i;
  register int j;

  u = 0;
  for (i = 0;i < 18;++i) {
    u += out[i];
    for (j = 0;j <= i;++j)
      u += x[j] * (long double) y[i - j];
    
    z = round30(u); u -= z; z *= twom30;
    out[i] = u;
    u = z;
  }
  return u;
}

static double mid(register const double x[18],register const double y[18])
{
  register int i;
  register long double u;

  u = 0;
  for (i = 0;i < 18;++i)
    u += x[i] * (long double) y[17 - i];
  return round30(u) * twom30;
}

static double sethigh(register double out[17],register const double x[18],register const double y[18],double carry)
{
  register long double u;
  register long double z;
  register int i;
  register int j;

  u = carry;
  for (i = 18;i < 35;++i) {
    for (j = i - 17;j < 18;++j)
      u += x[j] * (long double) y[i - j];

    z = round30(u); u -= z; z *= twom30;
    out[i - 18] = u;
    u = z;
  }
  return u;
}

void zmodexp512_multiply(register zmodexp512_m *m,register zmodexp512_r *r,register const zmodexp512_r *s)
{
  register int i;
  register double u;

  for (i = 0;i < 18;++i)
    T[i] = 0;

  u = addlow(T,R,S);
  sethigh(T + 18,R,S,u);

  /* R and S are so small that sethigh() returns 0; no need for T[35] */

  u = mid(T + 17,INV);
  Q[17] = sethigh(Q,T + 17,INV,u);

  addlow(T,Q,M);

  for (i = 0;i < 18;++i)
    R[i] = T[i];
}

static double addlowsquare(register double out[18],register const double x[18])
{
  register long double u;
  register long double z;
  register long double t8;
  register int i;
  register int j;

  u = 0;
  i = 0;
  while (i < 18) {
    u += out[i];
    t8 = 0;
    for (j = 0;j + j < i;++j)
      t8 += x[j] * (long double) x[i - j];
    t8 += t8;
    t8 += x[j] * (long double) x[i - j];
    u += t8;
    
    z = round30(u); u -= z; z *= twom30;
    out[i] = u;
    u = z;
    ++i;

    u += out[i];
    t8 = 0;
    for (j = 0;j + j < i;++j)
      t8 += x[j] * (long double) x[i - j];
    t8 += t8;
    u += t8;
    
    z = round30(u); u -= z; z *= twom30;
    out[i] = u;
    u = z;
    ++i;
  }
  return u;
}

static double sethighsquare(register double out[17],register const double x[18],double carry)
{
  register long double u;
  register long double z;
  register long double t8;
  register int i;
  register int j;

  u = carry;
  i = 18;
  for (;;) {
    t8 = 0;
    for (j = i - 17;j + j < i;++j)
      t8 += x[j] * (long double) x[i - j];
    t8 += t8;
    t8 += x[j] * (long double) x[i - j];
    u += t8;

    z = round30(u); u -= z; z *= twom30;
    out[i - 18] = u;
    u = z;
    ++i;
    if (i >= 35) break;

    t8 = 0;
    for (j = i - 17;j + j < i;++j)
      t8 += x[j] * (long double) x[i - j];
    t8 += t8;
    u += t8;

    z = round30(u); u -= z; z *= twom30;
    out[i - 18] = u;
    u = z;
    ++i;
  }
  return u;
}

void zmodexp512_square(zmodexp512_m *m,zmodexp512_r *r)
{
  register int i;
  register double u;

  for (i = 0;i < 18;++i)
    T[i] = 0;

  u = addlowsquare(T,R);
  sethighsquare(T + 18,R,u);

  u = mid(T + 17,INV);
  Q[17] = sethigh(Q,T + 17,INV,u);

  addlow(T,Q,M);

  for (i = 0;i < 18;++i)
    R[i] = T[i];
}
