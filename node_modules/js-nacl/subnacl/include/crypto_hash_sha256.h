#ifndef crypto_hash_sha256_H
#define crypto_hash_sha256_H

#define crypto_hash_sha256_BYTES 32
extern int crypto_hash_sha256(unsigned char *,const unsigned char *,unsigned long long);
#define crypto_hash_sha256_IMPLEMENTATION "crypto_hash/sha256/ref"
#define crypto_hash_sha256_VERSION "-"

#endif
