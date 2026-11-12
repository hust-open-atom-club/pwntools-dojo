/*
 * elf-level-7 :: level7
 *
 * SUID root。收学生输入的 16 位十六进制 secret（crackme 补丁后打印的
 * 那个），对输入的 16 字符 ASCII 串做 SHA-256，与内嵌摘要比对；匹配则
 * 打印 /flag。本文件可以放进挑战目录（部署后学生可读）：里面只有摘要，
 * 没有秘密，也没有秘密的派生逻辑。
 *
 * SHA-256 实现见同目录 sha256.c/sha256.h（公有领域，Brad Conte 风格）。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "sha256.h"

/*
 * SHA256(<secret 的 16 字符小写 hex ASCII 串>)。
 * 摘要在开发期由 dev-src/extract_secret.sh 提取秘密后计算填入。
 */
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

	/* 只收十六进制字符；顺手统一成小写再哈希 */
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
