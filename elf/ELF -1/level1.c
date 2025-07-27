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


void win() { print_flag(); } 

int main() {
    print_desc();
    printf("Find win() address!\n");
    getchar(); 
    print_exit();
    return 0;
}
