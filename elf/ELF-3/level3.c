#include <stdio.h>
#include <string.h>  
#include <stdlib.h>
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

int main() {
    char* key_str = "GiveMeFlag";  
    printf("Find address of 'GiveMeFlag': ");
    
    unsigned long addr;
    scanf("%lx", &addr);
    if(addr == (unsigned long)key_str) {
        print_flag();
    }
    return 0;
}
