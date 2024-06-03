当前关卡需要你编写一段汇编代码来满足如下条件绕过检查，并使用 `pwntools` 的 `asm` API 编写汇编语句完成本关卡挑战。本挑战关卡的条件是：

```
rax = 0x12345678
```

请参考如下 `pwntools` 示例代码完成代码编写(**提示：请注意修改 NOP 指令为特定功能的汇编指令**)：
```
from pwn import *

def print_lines(io):
    info("Printing io received lines")
    while True:
        try:
            line = io.recvline()
            success(line.decode())
        except EOFError:
            break

# Set architecture, os and log level
context(arch="amd64", os="linux", log_level="info")

# Load the ELF file and execute it as a new process.
challenge_path = "/challenge/pwntools-tutorials-level2.0"

p = process(challenge_path)

# Send the payload after the string "(up to 0x1000 bytes): \n" is found.
p.sendafter("Please give me your assembly in bytes", asm("NOP"))

print_lines(p)
```