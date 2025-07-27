#include <stdio.h>
#include <string.h>
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

char secret[] = "Easy_Password123"; 

int main() {
    print_desc();
    char input[100];
    gets(input); 
    if(strcmp(input, secret) == 0) {
        print_flag();
    }
    print_exit();
    return 0;
}
