#include <stdio.h>
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
    unsigned long entry;
    printf("Enter the entry point address (hex): ");
    scanf("%lx", &entry);
    if (entry == (unsigned long)&main) {  
        print_flag();
    }
    return 0;
}
