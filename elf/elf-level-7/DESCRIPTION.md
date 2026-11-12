前几关里你要找的全局变量初始值都是 `0`——它们住在 .bss 段，文件里根本没有对应的字节。这一关不一样：`/challenge/crackme` 的全局变量 `gate` 初始化为 `1337`，非零初值让它住进了 .data 段，文件里实打实躺着 4 个字节，这正是 `elf.write` 的用武之地。

不过 `/challenge` 是只读的，而且你也不该修改大家共用的原件——好在 `crackme` 没有 SUID，随便复制一份就行：

```
cp /challenge/crackme ~/crackme
```

要把它改成什么？本题直接告诉你：改成 `2026`（好心省掉你逆向比较指令的功夫）。用 pwntools 打开副本：`elf.symbols['gate']` 拿到 `gate` 的虚拟地址，`elf.write` 收的就是虚拟地址（它会在内部换算成文件偏移再写回），最后 `elf.save()` 保存：

```python
from pwn import *
elf = ELF('/home/hacker/crackme')
elf.write(elf.symbols['gate'], p32(2026))
elf.save('/home/hacker/crackme')
```

运行打过补丁的 `~/crackme`，它会打印一个 `secret`。这个秘密是程序运行时一层层算出来的，静态逆向它比打补丁费劲得多——别跟它较劲。

最后一步：把 secret 通过标准输入交给 `/challenge/level7`（例如 `echo <secret> | /challenge/level7`），就能拿到 `/flag`。注意必须是 `/challenge` 里那个 `level7`——复制出来的 `level7` 会丢掉 SUID，读不了 `/flag`。
