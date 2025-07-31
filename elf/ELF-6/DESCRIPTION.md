在二进制安全分析中，理解ELF文件的节区（Section）布局至关重要。.text段存储着程序的可执行代码，定位该段的基地址是许多漏洞利用的前提条件。

本关卡要求你使用pwntools的节区分析功能，通过elf.get_section_by_name()找到目标程序中.text段的起始地址，并将该地址提交给程序来触发print_flag()。
