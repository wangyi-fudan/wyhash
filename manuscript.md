The Fastest Hash Function and Pseudo Random Number Generator
----
Yi Wang, ..., ... , ..., Li Jin*

Yi Wang: Ministry of Education Key Laboratory of Contemporary Anthropology, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Shanghai, China. Human Phenome Institute, Fudan University, Shanghai, China.

Li Jin: Human Phenome Institute, Fudan University, Shanghai, China. State Key Laboratory of Genetic Engineering, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Fudan University, Shanghai, China.

----------------------------------------
**Introduction**

what is hash function and PRNG

the connection between hash and PRNG

history review

problems and challenges

----------------------------------------

**Method**

wyhash/wyrand is based on a MUM mix core with known credit from @vnmakarov (https://github.com/vnmakarov/mum-hash). 
```
uint64_t MUM(uint64_t A, uint64_t B){
  __uint128_t c=(__uint128_t)A*B;
  return  (c>>64)^c;  
}
```
MUM is powerful in mixing data as 64x64-bit multiplication can do the same work as 32 shifts and additions. Despite the nominal 128-bit mulplication, the actual instructions are only one MULQ and one XORQ on 64-bit machines. One of our improvement is masked-MUM=MUM(A^P0,B^P1), where P0 and P1 are random prime mask with 32 1s and 32 0s. The masked-MUM can randomize real biased data and thus produce well mixed (avalanche) result. We observed from experiment that just two rounds of masked-MUM can pass statistical tests.

wyhash design

wyrand design

----------------------------------------

**Statistical Test**

SMHasher

BigCrush

PractRand

----------------------------------------

**Speed Benchmark**

Benchmark of Hash functions 

Benchmark of PRNG

----------------------------------------

**Security Analysis**

The MUM core

Other issues

----------------------------------------

**Languages Bindings**

----------------------------------------

**Discussion**

----------------------------------------

**Acknowledgment**

----------------------------------------

**References**
