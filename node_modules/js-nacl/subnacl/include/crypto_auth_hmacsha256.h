#ifndef crypto_auth_hmacsha256_H
#define crypto_auth_hmacsha256_H

#define crypto_auth_hmacsha256_BYTES 32
#define crypto_auth_hmacsha256_KEYBYTES 32
extern int crypto_auth_hmacsha256(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_auth_hmacsha256_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
#define crypto_auth_hmacsha256_IMPLEMENTATION "crypto_auth/hmacsha256/ref"
#define crypto_auth_hmacsha256_VERSION "-"

#endif
