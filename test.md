```C
uint64_t  mum(uint64_t A, uint64_t B){
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

```C
uint64_t wyrand(uint64_t *seed) { 
  *seed+=p0; 
  return mum(*seed^p1,*seed); 
}
```
```C
uint64_t rotr(uint64_t v, unsigned k) { return (v>>k)|(v<<(64-k)); }
uint64_t mum32(uint64_t A, uint64_t B) {
 uint64_t hh=(A>>32)*(B>>32), hl=(A>>32)*(unsigned)B；
 uint64_t lh=(unsigned)A*(B>>32), ll=(uint64_t)(unsigned)A*(unsigned)B;
 return  rotr(hl,32)^rotr(lh,32)^hh^ll;
}
```
