#ifndef crypto_core_salsa20_H
#define crypto_core_salsa20_H

#define crypto_core_salsa20_OUTPUTBYTES 64
#define crypto_core_salsa20_INPUTBYTES 16
#define crypto_core_salsa20_KEYBYTES 32
#define crypto_core_salsa20_CONSTBYTES 16
extern int crypto_core_salsa20(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);
#define crypto_core_salsa20_IMPLEMENTATION "crypto_core/salsa20/ref"
#define crypto_core_salsa20_VERSION "-"

#endif
