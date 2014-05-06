#ifndef crypto_stream_salsa2012_H
#define crypto_stream_salsa2012_H

#define crypto_stream_salsa2012_KEYBYTES 32
#define crypto_stream_salsa2012_NONCEBYTES 8
extern int crypto_stream_salsa2012(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa2012_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa2012_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_salsa2012_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa2012_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
#define crypto_stream_salsa2012_IMPLEMENTATION "crypto_stream/salsa2012/ref"
#define crypto_stream_salsa2012_VERSION "-"

#endif
