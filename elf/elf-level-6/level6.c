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
    printf("Find .text section address: ");
    unsigned long addr;
    scanf("%lx", &addr);

	// linux下通过/proc/self/exe获取当前进程的ELF文件
    unsigned long text_addr = 0;
    int fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) return 0;

    unsigned char e_ident[EI_NIDENT];
    if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT ||
        e_ident[EI_MAG0] != ELFMAG0 ||
        e_ident[EI_MAG1] != ELFMAG1 ||
        e_ident[EI_MAG2] != ELFMAG2 ||
        e_ident[EI_MAG3] != ELFMAG3) {
        close(fd);
        return 0;
    }

	// 根据ELF文件头中的EI_CLASS字段判断ELF文件是64位还是32位

    if (e_ident[EI_CLASS] == ELFCLASS64) {
        Elf64_Ehdr eh;
        lseek(fd, 0, SEEK_SET);
        if (read(fd, &eh, sizeof(eh)) != sizeof(eh)) { close(fd); return 0; }

		// 根据ELF文件头中的e_shoff和e_shentsize字段，获取节区表的偏移和节区表项的大小
        Elf64_Shdr *shdrs = malloc(eh.e_shentsize * eh.e_shnum);
        if (!shdrs) { close(fd); return 0; }
        lseek(fd, eh.e_shoff, SEEK_SET);
        if (read(fd, shdrs, eh.e_shentsize * eh.e_shnum) != (ssize_t)(eh.e_shentsize * eh.e_shnum)) { free(shdrs); close(fd); return 0; }

		// 根据ELF文件头中的e_shstrndx字段，获取节区表中节区字符串表的索引
        Elf64_Shdr shstr = shdrs[eh.e_shstrndx];
        char *shnames = malloc(shstr.sh_size);
        if (!shnames) { free(shdrs); close(fd); return 0; }
        lseek(fd, shstr.sh_offset, SEEK_SET);
        if (read(fd, shnames, shstr.sh_size) != (ssize_t)shstr.sh_size) { free(shnames); free(shdrs); close(fd); return 0; }

		// 遍历节区表，找到.text节区
        for (int i = 0; i < eh.e_shnum; i++) {
            const char *name = shnames + shdrs[i].sh_name;
            if (strcmp(name, ".text") == 0) { text_addr = (unsigned long)shdrs[i].sh_addr; break; }
        }
        free(shnames);
        free(shdrs);
    } else if (e_ident[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr eh;
        lseek(fd, 0, SEEK_SET);
        if (read(fd, &eh, sizeof(eh)) != sizeof(eh)) { close(fd); return 0; }

        Elf32_Shdr *shdrs = malloc(eh.e_shentsize * eh.e_shnum);
        if (!shdrs) { close(fd); return 0; }
        lseek(fd, eh.e_shoff, SEEK_SET);
        if (read(fd, shdrs, eh.e_shentsize * eh.e_shnum) != (ssize_t)(eh.e_shentsize * eh.e_shnum)) { free(shdrs); close(fd); return 0; }

        Elf32_Shdr shstr = shdrs[eh.e_shstrndx];
        char *shnames = malloc(shstr.sh_size);
        if (!shnames) { free(shdrs); close(fd); return 0; }
        lseek(fd, shstr.sh_offset, SEEK_SET);
        if (read(fd, shnames, shstr.sh_size) != (ssize_t)shstr.sh_size) { free(shnames); free(shdrs); close(fd); return 0; }

        for (int i = 0; i < eh.e_shnum; i++) {
            const char *name = shnames + shdrs[i].sh_name;
            if (strcmp(name, ".text") == 0) { text_addr = (unsigned long)shdrs[i].sh_addr; break; }
        }
        free(shnames);
        free(shdrs);
    }

    close(fd);

    if (addr == text_addr && text_addr != 0) print_flag();
}
