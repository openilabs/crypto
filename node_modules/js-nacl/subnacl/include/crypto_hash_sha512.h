#ifndef crypto_hash_sha512_H
#define crypto_hash_sha512_H

#define crypto_hash_sha512_BYTES 64
extern int crypto_hash_sha512(unsigned char *,const unsigned char *,unsigned long long);
#define crypto_hash_sha512_IMPLEMENTATION "crypto_hash/sha512/ref"
#define crypto_hash_sha512_VERSION "-"

#endif
