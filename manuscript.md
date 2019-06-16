The Fastest Short Key Hash Function and Pseudo Random Number Generator
----
Yi Wang, ..., Diego Barrios Romero , ..., Li Jin*

Yi Wang: Ministry of Education Key Laboratory of Contemporary Anthropology, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Shanghai, China. Human Phenome Institute, Fudan University, Shanghai, China.

Diego Barrios Romero: Fraunhofer Institute for Digital Medicine MEVIS, Bremen, Germany.

Li Jin: Human Phenome Institute, Fudan University, Shanghai, China. State Key Laboratory of Genetic Engineering, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Fudan University, Shanghai, China.

----------------------------------------
**Introduction**

A hash function is a function which is capable of mapping data of arbitrary size onto data of a fixed size (see [here](https://en.wikipedia.org/wiki/Hash_function)). Hash functions are useful in a variety of applications. A notable one is hash tables. Hash tables use a hash function to accelerate the lookup of data in a table as it is faster to compute the hash of the key once and use that as an index. This yields an amortized constant average operation cost. Desirable properties of a hash function include determinism, speed, being non-invertible, and generating an avalanche-effect.

On the other hand, a pseudo-random number generator (PRNG) is an algorithm that is capable of generating a stream of numbers which appear to be randomly chosen. PRNGs are only an approximation, though. Its values are completely determined by the original seed used for initialization.

To an outside observer, a hash function generates an apparently random output and thus it can also serve as the basis for a PRNG. If we have a good hash functions, then we can apply it to time or rounds to obtain a good PRNG. This idea means that we can test a hash function with BigCrush (conventionally for PRNG) by applying it on rounds. We did crushed some hash functions in this way. [eg. t1ha](https://github.com/rurban/smhasher/issues/54)

Numberous hash functions have been designed in last decades. [SMHasher](https://github.com/rurban/smhasher/) is a hub to collect and evaluate more than 100 hash functions. We name a few excellent hash function: t1ha2_atonce (known for speed), xxHash64 (known for popularity), SipHash (known for security). Also numberous PRNGs have been designed in last decades. [testingRNG](https://github.com/lemire/testingRNG) is a collection and benchmark of some modern PRNGs. We name a few excellent PRNGs: splitmix64 ( popular in Java), [PCG](http://www.pcg-random.org/), [xoshiro256**](http://xoshiro.di.unimi.it/), lehmer64 (simple and fast). 

Despite the richness of hash function and PRNGs, we are still on the way to our ultimate aesthetic goals: fastest and simplest under the premise of soildity and portability. Security is a secondary goal as 64-bit hash function and PRNGs are fundamentally weak against brute force attacks. 

With the above goals in mind and heart, we feel lucky to discover/invent a new hash function named as wyhash and a new PRNG named as wyrand. wyhash and wyrand are solid, portable, fastest and simplest. They are not designed to be cryptographically secure but still have a little security considerations without sacrifying speeed and simplisity. 

----------------------------------------

**Method**

wyhash/wyrand is based on a MUM mix core created by @vnmakarov and released on Mother's day (https://github.com/vnmakarov/mum-hash) in a [Merkle-Dåmgard construction](https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction).
```C
uint64_t MUM(uint64_t A, uint64_t B){
  __uint128_t c=(__uint128_t)A*B;
  return  (c>>64)^c;
}
```
MUM is powerful in mixing data as 64x64-bit multiplications can do the same work as 32 shifts and additions. Despite the nominal 128-bit multiplication, the actual instructions are only one `MULQ` and one `XORQ` on 64-bit machines. One of our improvements is masked-MUM: `MUM(A^p0, B^p1)`, where p0 and p1 are random prime masks containing 32 1s. The masked-MUM can randomize biased real data toward 32 1s and thus produce an avalanche effect. We observed experimentally that just two rounds of masked-MUM can pass statistical tests.

The wyhash algorithm's interface is as follows:

```C
uint64_t wyhash(const void* p, uint64_t len, uint64_t seed);
```
The algorithm works on 256-bit blocks starting from pointer `p` with the following iterations:

```C
seed = MUM(read64(p)^p0^seed, read64(p+8)^p1^seed) ^ MUM(read64(p+16)^p2^seed, read64(p+24)^p3^seed);
```

It can be viewed as a chaotic dynamic system with 64-bit internal states.

We process the last block with proper paddings and finalize the hash with

```C
return MUM(seed^len, p4);
```

Note that the finalization MUM is critical to pass statistical tests.

wyhash reads the data with the memcpy function. This is necessary because some machine architectures do not support unaligned reads and will generate hardware exceptions. A key trick to speedup wyhash is that in the last block each 64-bit reading is implemented as two 32-bit readings: `read64(p) = (read32(p)<<32) | read32(p+4)`. This trick may be explained by the fact that memory is 4-byte aligned.

The primary wyrand interface is as follows:
```C
uint64_t wyrand(uint64_t *seed);
```

Where the `seed` represents the internal state of the generator and will be updated. For convenience, a second interface has been added which is a drop-in replacement for the C standard library `srand()` and `rand()` functions. In this case, the state is kept in a global variable, which can be initialized via the `wysrand()` function.

```C
void wysrand(uint64_t seed);
uint64_t wyrand(void);
```

wyrand updates its 64-bit state by simply adding a prime `p0` on each round. The state is then hashed to produce an output using the MUM core.

```C
*seed += p0;
return MUM(*seed^p1, *seed);
```


----------------------------------------

**Statistical Tests and Speed Benchmarks**

wyhash and wyrand are tested and benchmarked on a dual-Xeon E5 2683-v3 server with 4 X 16 DDR3 @ 2133 MHz memory.

The SMHasher test results are reported in SMHasher.wyhash, SMHasher.t1ha2_atonce, SMHasher.xxHash64, SMHasher.SipHash respectively. All benchmarked algorithms passed all tests.

Large key speed (Bytes/Cycle)

| key size	| wyhash	| t1ha2_atonce	| xxHash64	| SipHash |
| ----| ----| ----| ----| ---- |
| 256kb	| 4.249	| 6.224	| 5.627	| 0.477 |

Short key time cost (Cycle/Hash)

| key size	| wyhash	| t1ha2_atonce	| xxHash64	| SipHash |
| ----| ----| ----| ----| ---- |
| 1	| 16	| 41	| 21	| 75 |
| 2	| 16	| 33.49	| 24	| 75 |
| 3	| 17	| 27	| 28	| 75 |
| 4	| 16	| 27	| 22	| 75 |
| 5	| 17	| 27	| 25	| 75 |
| 6	| 17	| 27	| 28	| 75 |
| 7	| 18	| 27.86	| 32	| 75 |
| 8	| 17	| 27	| 31	| 92 |
| 9	| 17	| 30	| 34	| 92 |
| 10	| 17	| 30	| 38	| 92 |
| 11	| 17	| 30	| 41	| 92 |
| 12	| 17	| 29.97	| 35	| 91 |
| 13	| 17	| 29.89	| 38	| 92 |
| 14	| 17	| 29.9	| 42	| 92 |
| 15	| 17	| 29.93	| 45	| 92 |
| 16	| 17	| 29.97	| 35	| 108 |
| 17	| 18	| 33.32	| 38	| 109 |
| 18	| 18	| 33.24	| 42	| 108 |
| 19	| 18	| 33.12	| 45	| 109 |
| 20	| 18	| 33.12	| 39	| 108 |
| 21	| 18	| 33	| 42	| 109 |
| 22	| 18	| 33.48	| 46	| 109 |
| 23	| 18	| 33.17	| 49	| 110 |
| 24	| 18	| 33	| 39	| 125 |
| 25	| 18	| 37	| 42	| 125.27 |
| 26	| 18	| 37	| 46	| 125 |
| 27	| 18	| 37	| 49	| 125.61 |
| 28	| 18	| 37	| 43	| 125 |
| 29	| 18	| 37	| 46	| 126 |
| 30	| 18	| 37	| 50	| 125 |
| 31	| 18.26	| 37	| 53	| 130.5 |
| average	| 17.428	| 32.305	| 38.323	| 101.206 |

We benchmark wyrand, lehmer64, 3 parallel lehmer64, splitmix64, xoshiro256, pcg64, pcg32 PRNGs using a loop of 4 billion.
```
g++ BenchmarkPRNG.cpp -o BenchmarkPRNG -O2 -fno-tree-vectorize -Wall
```
The result is shown in the below table:

| PRNG | ns/rand | vs wyrand |
| ---- | ---- | ---- |
| wyrand | 0.868 | 100.000% |
| lehmer64 | 1.359 | 156.538% |
| 3-lehmer64 | 0.906 | 104.412% |
| splitmix64 | 1.366 | 157.331% |
| xoshiro256 | 3.424 | 394.455% |
| pcg64 | 2.760 | 318.042% |
| pcg32 | 1.471 | 169.500% |


----------------------------------------

**Security Analysis**

wyhash is designed for speed - not to be cryptographically secure. Analysis by @leo-yuriev highlighted that wyhash uses a so-called "narrow-pipe" [Merkle-Dåmgard construction](https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction) where manipulation of the input data can lead to entropy loss.
The probability of these cases occurring in known natural data is relatively low and thus wyhash is still useful in this context. Some improvements which did not impact speed have been added to wyhash in version 2 to counter these effects. However, the fundamental shortcomings of the "narrow-pipe" construction still apply. The detailed discussion is as follow:

The MUM core is not secure. If A=0 or B=0 then MUM(A,B)=0 no matter the other part. Attackers or commom input data can trig this security problem.

The masked-MUM is almost safe with normal data but is not secure for intended attack. If A=p0 or B=p1 then MUM(A^p0,B^p1)=0. Normal data has a rare probabily to match the prime mask (prob=2^-64). But attackers can hide any B content by providing A=p0.

The seed-masked-MUM is almost safe for both normal data and intended attack when seed is kept privatedly by the hasher. Only when A=seed^p0 or B=seed^p1, MUM(A^seed^p0, B^seed^p1)=0. This can occur at low probability (2^-64) both for natural data and intended attacks.

The iterative security is also discussed. Simple MUM has a problem when seed is zeroed before reaching the end. We want the seed to be regenarated toward 32 1s in any case. The seed-masked-MUM enables this ability: the next block will almost produce another seed value no matter the current seed value.

The iterative dynamic is also attractive in the sense of security. Some other hash functions uses accmulators as internal states. We consider iterative dynamic system is more hard to be analysed than accumulators and is more sensitive to initial values and has better avalanche effect (chaos).

**TODO** can somebody prove the MUM is reversible or not? it seems that one can solve a new type of equation for x:

MUM(x,p)=q     x=?    @lemire


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

We appreciate these people/user for contributing codes and/or comments in the development of wyhash/wyrand.

Reini Urban, Dietrich Epp, Joshua Haberman, Tommy Ettinger, Daniel Lemire, Otmar Ertl, cocowalla, leo-yuriev

**TODO** you can be moved to author area by joining the paper writing process.

----------------------------------------

**References**
