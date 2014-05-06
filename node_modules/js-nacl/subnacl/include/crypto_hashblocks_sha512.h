#ifndef crypto_hashblocks_sha512_H
#define crypto_hashblocks_sha512_H

#define crypto_hashblocks_sha512_STATEBYTES 64
#define crypto_hashblocks_sha512_BLOCKBYTES 128
extern int crypto_hashblocks_sha512(unsigned char *,const unsigned char *,unsigned long long);
#define crypto_hashblocks_sha512_IMPLEMENTATION "crypto_hashblocks/sha512/ref"
#define crypto_hashblocks_sha512_VERSION "-"

#endif
