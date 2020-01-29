```C
uint64_t  MUM(uint64_t A,	uint64_t	B){
  __uint128_t c=(__uint128_t)A*B;
  return  (c>>64)^c;
}
```

```ASM
MUM(unsigned long, unsigned long):
mov rax, rdi
mul rsi
xor rax, rdx
ret
```
