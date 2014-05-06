#ifndef crypto_auth_hmacsha512256_H
#define crypto_auth_hmacsha512256_H

#define crypto_auth_hmacsha512256_BYTES 32
#define crypto_auth_hmacsha512256_KEYBYTES 32
extern int crypto_auth_hmacsha512256(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_auth_hmacsha512256_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
#define crypto_auth_hmacsha512256_IMPLEMENTATION "crypto_auth/hmacsha512256/ref"
#define crypto_auth_hmacsha512256_VERSION "-"

#endif
