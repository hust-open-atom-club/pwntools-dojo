#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define UTIL_MAX_LEN 0x80
#define LOG_RESET 	"\x1B[0m"
#define LOG_BOLD	"\x1B[1m"
#define LOG_RED   	"\x1B[31m"
#define LOG_BLUE   	"\x1B[34m"
#define LOG_CYAN   	"\x1B[36m"

extern void print_exit();
extern void print_desc();