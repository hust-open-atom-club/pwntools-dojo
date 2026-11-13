/*
 * elf-level-7 :: level7
 *
 * SUID root。从标准输入读取 16 位十六进制 secret，对输入字符串做
 * SHA-256 并与内嵌摘要比对，匹配则打印 /flag。
 *
 * 文件内嵌 SHA-256 实现：Brad Conte 的公有领域实现（重录入，API 相同），
 * 出处：https://github.com/B-Con/crypto-algorithms
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

/*
 * SHA-256（公有领域，Brad Conte）
 */
typedef uint8_t  BYTE;             /* 8-bit byte */
typedef uint32_t WORD;             /* 32-bit word */

typedef struct {
    BYTE data[64];
    WORD datalen;
    unsigned long long bitlen;
    WORD state[8];
} SHA256_CTX;

#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define CH(x, y, z)    (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z)   (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)         (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x)         (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x)        (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x)        (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

static const WORD k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void sha256_transform(SHA256_CTX *ctx, const BYTE data[])
{
    WORD a, b, c, d, e, f, g, h, t1, t2, m[64];
    WORD i, j;

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = ((WORD)data[j] << 24) | ((WORD)data[j + 1] << 16) |
               ((WORD)data[j + 2] << 8) | (WORD)data[j + 3];
    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

static void sha256_init(SHA256_CTX *ctx)
{
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

static void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{
    WORD i;

    for (i = 0; i < (WORD)len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha256_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

static void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
    WORD i;

    i = ctx->datalen;

    /* Pad whatever data is left in the buffer. */
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56)
            ctx->data[i++] = 0x00;
    } else {
        ctx->data[i++] = 0x80;
        while (i < 64)
            ctx->data[i++] = 0x00;
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56);
    }

    /* Append to the padding the total message's length in bits. */
    ctx->bitlen += ctx->datalen * 8;
    ctx->data[63] = (BYTE)(ctx->bitlen);
    ctx->data[62] = (BYTE)(ctx->bitlen >> 8);
    ctx->data[61] = (BYTE)(ctx->bitlen >> 16);
    ctx->data[60] = (BYTE)(ctx->bitlen >> 24);
    ctx->data[59] = (BYTE)(ctx->bitlen >> 32);
    ctx->data[58] = (BYTE)(ctx->bitlen >> 40);
    ctx->data[57] = (BYTE)(ctx->bitlen >> 48);
    ctx->data[56] = (BYTE)(ctx->bitlen >> 56);
    sha256_transform(ctx, ctx->data);

    /* Output hash. */
    for (i = 0; i < 4; ++i) {
        hash[i]      = (BYTE)((ctx->state[0] >> (24 - i * 8)) & 0xff);
        hash[i + 4]  = (BYTE)((ctx->state[1] >> (24 - i * 8)) & 0xff);
        hash[i + 8]  = (BYTE)((ctx->state[2] >> (24 - i * 8)) & 0xff);
        hash[i + 12] = (BYTE)((ctx->state[3] >> (24 - i * 8)) & 0xff);
        hash[i + 16] = (BYTE)((ctx->state[4] >> (24 - i * 8)) & 0xff);
        hash[i + 20] = (BYTE)((ctx->state[5] >> (24 - i * 8)) & 0xff);
        hash[i + 24] = (BYTE)((ctx->state[6] >> (24 - i * 8)) & 0xff);
        hash[i + 28] = (BYTE)((ctx->state[7] >> (24 - i * 8)) & 0xff);
    }
}

/* SHA-256（预期的 secret，16 字符小写十六进制 ASCII 字符串） */
static const BYTE EXPECTED_DIGEST[32] = {
    0x30, 0xCB, 0x3D, 0x1D, 0xCE, 0x9E, 0xFB, 0xEF,
    0x9C, 0x01, 0xB6, 0x61, 0x55, 0x4B, 0x2C, 0xBE,
    0xE6, 0xB8, 0xBB, 0x22, 0xAF, 0xD9, 0x0F, 0x29,
    0xD7, 0xA9, 0x1A, 0x1D, 0x61, 0x77, 0x71, 0x77
};

void print_flag()
{
	char *p;
	FILE *fp;
	char flag[100];

	fp = fopen("/flag", "r");

	if (!fp) {
		perror("[-] fopen failed");
		exit(1);
	}

	p = fgets(flag, sizeof(flag), fp);
	if (!p) {
		perror("[-] fgets failed");
		fclose(fp);
		exit(1);
	}

	printf("%s", flag);

	fclose(fp);
}

static void hash_input16(const char *s, BYTE out[32])
{
	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, (const BYTE *)s, 16);
	sha256_final(&ctx, out);
}

int main()
{
	char in[64];
	BYTE digest[32];
	size_t i;
	int ok = 1;

	printf("Enter the secret (16 hex chars): ");
	if (scanf("%63s", in) != 1) {
		puts("[-] read failed");
		return 1;
	}

	if (strlen(in) != 16) {
		puts("[-] wrong secret");
		return 1;
	}

	/* 只接受十六进制字符，统一转为小写后计算摘要 */
	for (i = 0; i < 16; i++) {
		if (!isxdigit((unsigned char)in[i]))
			ok = 0;
		in[i] = (char)tolower((unsigned char)in[i]);
	}
	if (!ok) {
		puts("[-] wrong secret");
		return 1;
	}

	hash_input16(in, digest);

	if (memcmp(digest, EXPECTED_DIGEST, 32) == 0) {
		print_flag();
	} else {
		puts("[-] wrong secret");
	}

	return 0;
}
