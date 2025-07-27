#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void print_flag()
{
	char *p;
	FILE *fp;
	char flag[100];

	fp = fopen("/flag", "r");

	if (!fp) {
		perror("[-] fopen failed");
	}

	p = fgets(flag, sizeof(flag), fp);
	if (!p) {
		perror("[-] fgets failed");
		fclose(fp);
	}
	
	printf("%s", flag);

	fclose(fp);
}

void target_function() {
    printf("Congratulations! You found the target function!\n");
    print_flag();
}

int main() {
    print_desc();
    // 获取用户输入
    unsigned long got_addr, plt_addr;
    printf("Enter the address of target_function's GOT entry (hex): ");
    scanf("%lx", &got_addr);
    printf("Enter the address of target_function's PLT entry (hex): ");
    scanf("%lx", &plt_addr);
    
    if (got_addr == (unsigned long)&target_function && 
        plt_addr == (unsigned long)target_function) {
        target_function(); 
    } else {
        printf("Try again! Wrong addresses.\n");
    }
    
    print_exit();
    return 0;
}
