#ifndef crypto_secretbox_xsalsa20poly1305_H
#define crypto_secretbox_xsalsa20poly1305_H

#define crypto_secretbox_xsalsa20poly1305_KEYBYTES 32
#define crypto_secretbox_xsalsa20poly1305_NONCEBYTES 24
#define crypto_secretbox_xsalsa20poly1305_ZEROBYTES 32
#define crypto_secretbox_xsalsa20poly1305_BOXZEROBYTES 16
extern int crypto_secretbox_xsalsa20poly1305(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_secretbox_xsalsa20poly1305_open(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
#define crypto_secretbox_xsalsa20poly1305_IMPLEMENTATION "crypto_secretbox/xsalsa20poly1305/ref"
#define crypto_secretbox_xsalsa20poly1305_VERSION "-"

#endif
