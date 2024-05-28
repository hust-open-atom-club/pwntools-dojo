当前关卡属于教学关卡，相对简单。你可以直接在终端中运行 `/challenge/pwntools-tutorials-level0.0`，然后输入特定字符串（此处需要阅读 `bypass_me` 函数），但这不是当前关卡的目的。

当前关卡将指导你如何使用 `pwntools` 完成本关卡挑战。接下来，你需要使用 pwntools 中的 `process`、`send`、`recv` 等 API 编写利用脚本，发送特定输入绕过检查，并读取 `/flag`。请参加如下 pwntools 示例代码（**提示：请注意修改 FIXME 为上述特定字符串**）：

```
from pwn import *

# Set architecture, os and log level
context(arch="amd64", os="linux", log_level="info")

# Load the ELF file and execute it as a new process.
challenge_path = "/challenge/pwntools-tutorials-level0.0"
p = process(challenge_path)

payload = b'FIXME'
# Send the payload after the string ":)\n###\n" is found.
p.sendafter(":)\n###\n", payload)

# Receive flag from the process
flag = p.recvline()
print(f"flag is: {flag}")
```