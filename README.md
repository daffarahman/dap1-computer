# dap1-computer
My simple virtual computer inspired by [Tom Scott's video](https://www.youtube.com/watch?v=Z5JC9Ve1sfI)

## Instructions
Here are some instructions that you can use
| Instruction | Opcode | Parameter |
|-------------|--------|-----------|
| LOAD        | 0x1    | Address   |
| ADD         | 0xB    | Address   |
| STORE       | 0x4    | Address   |
| JUMP        | 0xD    | Address   |

### Code Example
Here's a sample code that adds two numbers from address 0x8 (0x2) and address 0x9 (0x5), then store it into address 0xC
```
1 8
b 9
4 a
0 0
2 5
0 0
```
Save it as `test.dap1` and run `.\dap1.exe test.dap1`  
Press `enter` to step every instructions until the accumulator (a) becomes 7  
And that's basically how you do it
