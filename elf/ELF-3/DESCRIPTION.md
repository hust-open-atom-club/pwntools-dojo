在ELF二进制文件中，程序使用的字符串常量（如"/bin/sh"）通常存储在.rodata（只读数据段）中。在漏洞利用中，定位这些关键字符串的地址是构造攻击payload的重要步骤。

本关卡要求你使用pwntools的elf.search()功能，找到目标程序中硬编码的字符串"GiveMeFlag"的地址，并将该地址提交给程序，从而触发print_flag()函数获取/flag。
