#ifndef crypto_onetimeauth_poly1305_H
#define crypto_onetimeauth_poly1305_H

#define crypto_onetimeauth_poly1305_BYTES 16
#define crypto_onetimeauth_poly1305_KEYBYTES 32
extern int crypto_onetimeauth_poly1305(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_onetimeauth_poly1305_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
#define crypto_onetimeauth_poly1305_IMPLEMENTATION "crypto_onetimeauth/poly1305/ref"
#define crypto_onetimeauth_poly1305_VERSION "-"

#endif
