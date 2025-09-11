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
		return;
	}

	p = fgets(flag, sizeof(flag), fp);
	if (!p) {
		if (ferror(fp)) {
			perror("[-] fgets failed");
		}
		fclose(fp);
		return;
	}
	
	printf("%s", flag);

	fclose(fp);
}

int check = 1; 

int main() {
    if(check == 0) {
        print_flag();
    } else {
        printf("Try to change check to 0!\n");
    }
    return 0;
}
