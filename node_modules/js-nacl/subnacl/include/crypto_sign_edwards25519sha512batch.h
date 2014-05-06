#ifndef crypto_sign_edwards25519sha512batch_H
#define crypto_sign_edwards25519sha512batch_H

#define crypto_sign_edwards25519sha512batch_SECRETKEYBYTES 64
#define crypto_sign_edwards25519sha512batch_PUBLICKEYBYTES 32
#define crypto_sign_edwards25519sha512batch_BYTES 64
extern int crypto_sign_edwards25519sha512batch(unsigned char *,unsigned long long *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_sign_edwards25519sha512batch_open(unsigned char *,unsigned long long *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_sign_edwards25519sha512batch_keypair(unsigned char *,unsigned char *);
#define crypto_sign_edwards25519sha512batch_IMPLEMENTATION "crypto_sign/edwards25519sha512batch/ref"
#define crypto_sign_edwards25519sha512batch_VERSION "-"

#endif
