# crackme 的源码不在本仓库，仓库只交付成品二进制。
# 维护者源码默认位于 ../dev-src/crackme.c。

TARGETS = crackme level7
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z execstack -Wno-implicit-function-declaration

CRACKME_SRC = ../dev-src/crackme.c

.PHONY: all clean

all: $(TARGETS)

level7: level7.c
	$(CC) $(CFLAGS) -o $@ level7.c

# 重编译 crackme 后其输出会变化，需要重新提取并同步 level7.c 中的摘要。
crackme:
	@if [ ! -f $(CRACKME_SRC) ]; then \
	    echo "crackme.c is maintainer-private and not shipped in this repo;" >&2; \
	    echo "use the committed binary, or place the private source at $(CRACKME_SRC) and retry." >&2; \
	    exit 1; \
	fi
	$(CC) $(CFLAGS) -static -o $@ $(CRACKME_SRC)

clean:
	rm -rf $(TARGETS)
