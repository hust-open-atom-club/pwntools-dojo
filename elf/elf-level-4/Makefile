TARGET = level4
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z now

.PHONY: all clean

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	rm -rf $(TARGET)
