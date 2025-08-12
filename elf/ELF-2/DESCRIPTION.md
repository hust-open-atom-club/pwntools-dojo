在程序的动态链接过程中，GOT 表（Global Offset Table）和 PLT 表（Procedure Linkage Table）起着至关重要的作用。它们主要用于解决外部函数的调用问题，提高程序的空间效率和运行效率。

当前关卡需要你阅读挑战关卡的源代码，使用 `pwntools` 完成本关卡挑战。你需要使用 `pwntools` 工具库中的 `elf.got[]` 和 `elf.plt[]` 指令读取指定函数 `target_function` 的 GOT 表和 PLT 表地址，按照题目要求将其正确输入即可读取 `/flag`。
