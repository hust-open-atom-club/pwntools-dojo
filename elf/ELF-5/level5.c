#include <stdio.h>
#include <stdlib.h>
#include "util.h"  
// 内置 flag 打印函数
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

int secret_code = 0; 

int main() {
    print_desc();
    char buf[100];
    printf("Change secret_code to 1337!\n");
    gets(buf); 
    if (secret_code == 1337) {
        print_flag();
    }
    print_exit();
    return 0;
}
