#include <stdio.h>
#include <stdlib.h>  
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>

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

int main() {
    unsigned long entry;
    unsigned long elf_entry = 0;
    int fd;

    printf("Enter the entry point address (hex): ");
    scanf("%lx", &entry);

	// linux下通过/proc/self/exe获取当前进程的ELF文件
    fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) {
        perror("[-] open /proc/self/exe failed");
        return 1;
    }

	// 读取并解析ELF文件头

    unsigned char e_ident[EI_NIDENT];
    if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT ||
        e_ident[EI_MAG0] != ELFMAG0 ||
        e_ident[EI_MAG1] != ELFMAG1 ||
        e_ident[EI_MAG2] != ELFMAG2 ||
        e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "[-] Not an ELF file\n");
        close(fd);
        return 1;
    }

    // 利用结构体对ELF文件头进行解析，获取入口地址
	// 根据ELF文件头中的EI_CLASS字段判断ELF文件是64位还是32位

    if (e_ident[EI_CLASS] == ELFCLASS64) {
        Elf64_Ehdr hdr;
        lseek(fd, 0, SEEK_SET);
        if (read(fd, &hdr, sizeof(hdr)) != sizeof(hdr)) {
            perror("[-] read ELF64_Ehdr failed");
            close(fd);
            return 1;
        }
        elf_entry = (unsigned long)hdr.e_entry;
    } else if (e_ident[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr hdr;
        lseek(fd, 0, SEEK_SET);
        if (read(fd, &hdr, sizeof(hdr)) != sizeof(hdr)) {
            perror("[-] read ELF32_Ehdr failed");
            close(fd);
            return 1;
        }
        elf_entry = (unsigned long)hdr.e_entry;
    } else {
        fprintf(stderr, "[-] Unsupported ELF class\n");
        close(fd);
        return 1;
    }

    close(fd);

    if (entry == elf_entry) {  
        print_flag();
    }
    return 0;
}
