TARGET = level4
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z now
INCLUDE = -I../../include ../../include/util.c

.PHONY: all clean

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

clean:
	rm -rf $(TARGET)
