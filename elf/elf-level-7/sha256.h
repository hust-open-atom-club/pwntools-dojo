/*********************************************************************
 * Minimal SHA-256, in the style of Brad Conte's public-domain
 * crypto-algorithms repository:
 *   https://github.com/B-Con/crypto-algorithms  (sha256.c / sha256.h)
 * Original author: Brad Conte (brad@bradconte.com), who released the
 * implementation into the public domain. Re-typed here with the same
 * API so the challenge builds with zero external dependencies.
 *********************************************************************/
#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t  BYTE;             /* 8-bit byte */
typedef uint32_t WORD;             /* 32-bit word, change to unsigned
                                      long on 32-bit machines */

typedef struct {
    BYTE data[64];
    WORD datalen;
    unsigned long long bitlen;
    WORD state[8];
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx);
void sha256_transform(SHA256_CTX *ctx, const BYTE data[]);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);

#endif /* SHA256_H */
