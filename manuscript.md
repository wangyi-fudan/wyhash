The Fastest Hash Function and Pseudo Random Number Generator
----
Yi Wang, ..., Diego Barrios Romero , ..., Li Jin*

Yi Wang: Ministry of Education Key Laboratory of Contemporary Anthropology, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Shanghai, China. Human Phenome Institute, Fudan University, Shanghai, China.

Diego Barrios Romero: Fraunhofer Institute for Digital Medicine MEVIS, Bremen, Germany.

Li Jin: Human Phenome Institute, Fudan University, Shanghai, China. State Key Laboratory of Genetic Engineering, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Fudan University, Shanghai, China.

----------------------------------------
**Introduction**

wyhash was born out of the desire to find a 64-bit hash function and PRNG that are solid, portable, fastest and simplest.

what is hash function and PRNG

the connection between hash and PRNG

history review

problems and challenges

----------------------------------------

**Method**

wyhash/wyrand is based on a MUM mix core with created by @vnmakarov and released on Mother's day (https://github.com/vnmakarov/mum-hash) in a [Merkle-Dåmgard construction](https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction).
```C
uint64_t MUM(uint64_t A, uint64_t B){
  __uint128_t c=(__uint128_t)A*B;
  return  (c>>64)^c;
}
```
MUM is powerful in mixing data as 64x64-bit multiplications can do the same work as 32 shifts and additions. Despite the nominal 128-bit multiplication, the actual instructions are only one `MULQ` and one `XORQ` on 64-bit machines. One of our improvements is masked-MUM: `MUM(A^P0, B^P1)`, where P0 and P1 are random prime masks containing 32 1s. The masked-MUM can randomize biased real data toward 32 1s and thus produce an avalanche effect. We observed experimentally that just two rounds of masked-MUM can pass statistical tests.

The wyhash algorithm's interface is a follows:

```C
uint64_t wyhash(const void* p, uint64_t len, uint64_t seed);
```
The algorithm works on 256-bit blocks starting from pointer `p` with the following iterations:

```C
seed = MUM(p^p0^seed, (p+8)^p1^seed) ^ MUM((p+16)^p2^seed, (p+24)^p3^seed);
```

It can be viewed as a chaotic dynamic system with 64-bit internal states.

We process the last block with proper paddings and finalize the hash with

```C
return MUM(seed, len^p4);
```

Note that the finalization MUM is critical to pass statistical tests.


The wyrand algorithm is as follows:

wyrand uses a 64-bit state which is updated by adding a polinomial `P0` on each round. This state is mixed again with polinomial `P1` on one of the inputs and fed into the MUM core.

```C
*seed += p0;
return MUM(*seed^p1, *seed);
```

The primary wyrand interface is as follows:
```C
uint64_t wyrand(uint64_t *seed);
```

Where the `seed` represents the internal state of the generator and will be updated as described above. For convenience, a second interface has been added which are a drop-in replacement for the C standard library `srand()` and `rand()` functions. In this case, the state is kept in a global variable, which can be initialized via the `wysrand()` function.

```C
void wysrand(uint64_t seed);
uint64_t wyrand(void);
```

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

wyhash is designed for speed and is not to be cryptographically secure. Analysis by @leo-yuriev highlighted that wyhash uses a so-called "narrow-pipe" [Merkle-Dåmgard construction](https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction) where manipulation of the input data can lead to entropy loss.
The probability of these cases occurring in known natural data is relatively low and thus wyhash is still useful in this context.
Some improvements which did not impact speed have been added to wyhash in version 2 to counter these effects. However, the fundamental shortcomings of the "narrow-pipe" construction still apply.

The MUM core

Other issues

----------------------------------------

**Language Bindings and Ports**

wyhash provides C functions that provide a simple interface:
```C
uint64_t wyhash(const void* key, uint64_t len, uint64_t seed);
uint64_t wyrand(uint64_t *seed);
```

This should allow wyhash to be integrated easily into any other language like Python or Java via [foreign function interface](https://en.wikipedia.org/wiki/Foreign_function_interface).

Nevertheless, ports to several languages have been made by the community. Complete implementations of the hashing algorithm and random-number generator include versions in:
- [C#](https://github.com/cocowalla/wyhash-dotnet)
- [Rust](https://github.com/eldruin/wyhash-rs)
- [Swift](https://github.com/lemire/SwiftWyhash)

TODO: Add speed comparisons between the different language ports and the C implementation?

----------------------------------------

**Discussion**

----------------------------------------

**Acknowledgment**

----------------------------------------

**References**
