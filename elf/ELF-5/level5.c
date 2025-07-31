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

int target_value = 0x1234; 

int main() {
    printf("Find target_value address: ");
    unsigned long addr;
    scanf("%lx", &addr);
    if(addr == (unsigned long)&target_value) {
        print_flag();
    }
    return 0;
}
