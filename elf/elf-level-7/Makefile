# elf-level-7：crackme（学生可复制的补丁目标）+ level7（SUID 校验端）
#
# 注意：crackme.c 刻意不在本目录。dojo 部署时会把挑战目录内所有非下划线
# 开头的条目原样拷进 /challenge/，而 crackme 的源码一旦被学生看到，防
# 逆向设计即失效。维护者源码在 ../dev-src/crackme.c，此处只放成品二进制。

TARGETS = crackme level7
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z execstack -Wno-implicit-function-declaration

CRACKME_SRC = ../dev-src/crackme.c

.PHONY: all clean

all: $(TARGETS)

level7: level7.c sha256.c sha256.h
	$(CC) $(CFLAGS) -o $@ level7.c sha256.c

# v2：静态链接把派生代码埋进 ~1.6MB 的 libc 代码海。不 strip——IDA 阅读
# 是教学体验的一部分，符号全保留；派生函数用中性名 f1..f9、表用 T1..T3，
# 不泄露算法结构；gate/main 保持原名供学生定位。
# 注意：秘密依赖最终 .text 字节，重编译后必须重提取秘密并同步 level7.c。
crackme: $(CRACKME_SRC)
	$(CC) $(CFLAGS) -static -o $@ $(CRACKME_SRC)

clean:
	rm -rf $(TARGETS)
