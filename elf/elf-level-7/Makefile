# elf-level-7：crackme（学生可复制的补丁目标）+ level7（SUID 校验端）
#
# 注意：crackme.c 刻意不在本仓库——dojo 部署会把挑战目录内所有非下划线开头
# 的条目原样拷进 /challenge/，crackme 源码随包部署会破坏本关设计。源码由
# 维护者私管（默认放 ../dev-src/crackme.c），仓库只交付成品二进制。

TARGETS = crackme level7
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z execstack -Wno-implicit-function-declaration

CRACKME_SRC = ../dev-src/crackme.c

.PHONY: all clean

all: $(TARGETS)

level7: level7.c sha256.c sha256.h
	$(CC) $(CFLAGS) -o $@ level7.c sha256.c

# 重编译 crackme 后输出会变化，需重新提取并同步 level7.c 的摘要（见维护者 dev-src 工具）。
crackme:
	@if [ ! -f $(CRACKME_SRC) ]; then \
	    echo "crackme.c is maintainer-private and not shipped in this repo;" >&2; \
	    echo "use the committed binary, or place the private source at $(CRACKME_SRC) and retry." >&2; \
	    exit 1; \
	fi
	$(CC) $(CFLAGS) -static -o $@ $(CRACKME_SRC)

clean:
	rm -rf $(TARGETS)
