在前几关中，你需要定位的全局变量均初始化为 0。此类变量位于 .bss 段，在 ELF 文件中没有对应的初始值字节。初始化为非零值的全局变量位于 .data 段，其初始值直接存储在文件中，修改文件中的初始值字节即可改变程序运行时的取值。

/challenge 目录为只读，修改程序需要先将 /challenge/crackme 复制到自己的用户目录。crackme 中的全局变量 gate 初始化为 1337，检测通过后程序输出一个 secret。本关卡要求你通过静态分析确定 gate 应修改为的目标值，使用 pwntools 的 elf.symbols 和 elf.write 修改副本中 gate 的初始值，运行修改后的程序取得 secret，最后将 secret 通过标准输入提交给 /challenge/level7，获得 /flag。
