#ifndef crypto_core_hsalsa20_H
#define crypto_core_hsalsa20_H

#define crypto_core_hsalsa20_OUTPUTBYTES 32
#define crypto_core_hsalsa20_INPUTBYTES 16
#define crypto_core_hsalsa20_KEYBYTES 32
#define crypto_core_hsalsa20_CONSTBYTES 16
extern int crypto_core_hsalsa20(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);
#define crypto_core_hsalsa20_IMPLEMENTATION "crypto_core/hsalsa20/ref"
#define crypto_core_hsalsa20_VERSION "-"

#endif
