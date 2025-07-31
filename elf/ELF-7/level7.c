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

int check = 0; 

int main() {
    if(check == 1) {
        print_flag();
    } else {
        printf("Try to change check to 1!\n");
    }
    return 0;
}
