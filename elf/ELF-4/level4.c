#include <stdio.h>
#include <string.h>
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

void verify_protections() {
    char answers[4][20];
    const char *correct[] = {"yes", "no", "no", "partial"}; 
    
    printf("===== Protection Check =====\n");
    printf("1. Is NX enabled? (yes/no): ");
    scanf("%19s", answers[0]);
    printf("2. Is PIE enabled? (yes/no): ");
    scanf("%19s", answers[1]);
    printf("3. Is Canary found? (yes/no): ");
    scanf("%19s", answers[2]);
    printf("4. RELRO level (none/partial/full): ");
    scanf("%19s", answers[3]);

    // 验证答案
    for (int i = 0; i < 4; i++) {
        if (strcmp(answers[i], correct[i]) != 0) {
            printf("try again!\n");
            return;
        }
    }
    print_flag(); // 全部正确才输出flag
}

int main() {
    print_desc();
    printf("Run 'checksec ./level3' and answer questions:\n");
    verify_protections();
    print_exit();
    return 0;
}
