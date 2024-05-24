当前关卡将指导你需要你阅读并理解本挑战题目的逻辑。接下来，你需要使用 pwntools 中的 `process`、`send`、`recv` 等 API 编写利用脚本，发送特定输入绕过检查，并读取 `/flag`。

```
from pwn import *

# Set architecture, os and log level
context(arch="amd64", os="linux", log_level='debug')
# Load the ELF file and execute it as a new process.
challenge_path = "/challenge/pwntools-tutorials-level0.0"
elf = ELF(challenge_path)
p = process(elf.path)
# Generate a payload to bypass the check.
payload = 'pokemon'
# Send the payload after the string "Enter your input> \n" is found.
p.sendafter("Enter your input>", payload)
# Receive flag from the process
flag = p.recvline()
print(f"flag is: {flag}")
```