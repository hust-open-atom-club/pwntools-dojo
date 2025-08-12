TARGET = level6
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -no-pie -z execstack 

.PHONY: all clean

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	rm -rf $(TARGET)
