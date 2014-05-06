#ifndef GAUDRY_PM
#define GAUDRY_PM

extern void gaudry_pm(unsigned char *,const unsigned char *,const unsigned char *);
#ifndef gaudry
#define gaudry gaudry_pm
#endif

/* internal functions, exposed purely for testing */

extern void gaudry_pm_init(void);
#ifndef gaudry_init
#define gaudry_init gaudry_pm_init
#endif

extern void gaudry_pm_todouble(double *,const unsigned char *);
#ifndef gaudry_todouble
#define gaudry_todouble gaudry_pm_todouble
#endif

extern void gaudry_pm_hadamard(double *,const double *);
#ifndef gaudry_hadamard
#define gaudry_hadamard gaudry_pm_hadamard
#endif

extern void gaudry_pm_square(double *,const double *);
#ifndef gaudry_square
#define gaudry_square gaudry_pm_square
#endif

extern void gaudry_pm_mult(double *,const double *,const double *);
#ifndef gaudry_mult
#define gaudry_mult gaudry_pm_mult
#endif

extern void gaudry_pm_select(double *,double *,const double *,const double *,unsigned int);
#ifndef gaudry_select
#define gaudry_select gaudry_pm_select
#endif

extern void gaudry_pm_surface_specify(const unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);
#ifndef gaudry_surface_specify
#define gaudry_surface_specify gaudry_pm_surface_specify
#endif

extern void gaudry_pm_mainloop(double *,double *,const double *,const double *,const unsigned char *);
#ifndef gaudry_mainloop
#define gaudry_mainloop gaudry_pm_mainloop
#endif

extern void gaudry_pm_recip(double *,const double *);
#ifndef gaudry_recip
#define gaudry_recip gaudry_pm_recip
#endif

extern void gaudry_pm_fromdouble(unsigned char *,const double *);
#ifndef gaudry_fromdouble
#define gaudry_fromdouble gaudry_pm_fromdouble
#endif

#endif
