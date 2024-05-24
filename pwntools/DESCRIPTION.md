Pwntools 是一个工具包（包含各种好用的小工具）与软件库，旨在尽可能简化 CTF 比赛的渗透攻击过程，同时尽可能增加攻击代码的可读性。

- send, recv
- pack, unpack
- Assembly Code
- ELF 解析 (ELF-Crackme 模块需要)
- cyclic（缓冲区溢出模块需要）
- ShellCode & ROP（ShellCode 与 ROP 模块需要）

你可以使用下述 `python` 代码来引入 pwntools 库。

```python
from pwn import *
```