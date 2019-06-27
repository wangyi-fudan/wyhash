The Fastest Short Key Hash Function and Pseudo-Random Number Generator on x86-64 Architecture
----
Yi Wang, ..., Diego Barrios Romero , Daniel Lemire, ..., Li Jin*

Yi Wang: Ministry of Education Key Laboratory of Contemporary Anthropology, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Shanghai, China. Human Phenome Institute, Fudan University, Shanghai, China.

Diego Barrios Romero: Fraunhofer Institute for Digital Medicine MEVIS, Bremen, Germany.

Daniel Lemire:  Université du Québec (TÉLUQ) Montreal, Canada

Li Jin: Human Phenome Institute, Fudan University, Shanghai, China. State Key Laboratory of Genetic Engineering, Collaborative Innovation Center for Genetics and Development, School of Life Sciences, Fudan University, Shanghai, China.

----------------------------------------
**Introduction**

A hash function is a function which is capable of mapping data of arbitrary size onto data of a fixed size ([wikipedia](https://en.wikipedia.org/wiki/Hash_function)). Hash functions are useful in a variety of applications. A notable one is hash tables. In practice, good hash functions  yield an amortized constant lookup time.  A pseudo-random number generator (PRNG) is an algorithm that is capable of generating a stream of numbers which appears random. PRNGs are only an approximation to randomness. Their values are completely determined by the original seed used for initialization.

To an outside observer, a hash function generates an apparently random output and thus it can also serve as the basis for a PRNG. If we have a good hash functions, then we can apply it to time or rounds to obtain a good PRNG. Thus we can test a hash function with statistical tests meant for random number generators such as  BigCrush or PractRand [eg. t1ha](https://github.com/rurban/smhasher/issues/54)

Numerous hash functions have been designed in the last decades. [SMHasher](https://github.com/rurban/smhasher/) is a hub to collect and evaluate more than 100 hash functions: t1ha2_atonce (known for speed), xxHash64 (known for popularity), SipHash (known for security). Also numberous PRNGs have been designed in last decades: [testingRNG](https://github.com/lemire/testingRNG) is a collection and benchmark of some modern PRNGs. We name a few excellent PRNGs: splitmix64 (popular in Java), [PCG](http://www.pcg-random.org/), [xoshiro256**](http://xoshiro.di.unimi.it/), lehmer64 (simple and fast).

Despite the rich collection of hash functions and PRNGs, there may still be faster and better alternatives for some use cases. Speed, especially for short keys, is important for a hash functions in hash table applications. Speed is also important for PRNG for applications such as simulations.  With this goal in mind, we propose a new hash function named as wyhash and a new PRNG named as wyrand. Both wyhash and wyrand are portable, fast and simple. They may be well suited for non-crypographic applications.


## (D. Lemire: Claiming that it is fastest without any qualification is not prudent. The high speed relies fundamentally on the fact that you have a fast 64-bit multiplier that can produce the full product. [On some ARM processors, it is slower than splitmix](https://lemire.me/blog/2019/03/20/arm-and-intel-have-different-performance-characteristics-a-case-study-in-random-number-generation/).) Yi Wang: I still want to claim the fastest on x86-64 architecture. And in your blog, you benchmarked the older version of wyrand which needs two MUM. I think the latest wyrand which has only one MUM will be faster. However, I don't have ARM processor to benchmark.

## (D. Lemire: You should not make any claim regarding security unless you can back it up with strong evidence. E.g., that one does not know how to invert a function is not a security feature. You have to prove that nobody else can (in some sense).) Yi Wang: Yes, we don't claim security.

----------------------------------------

**Method**

wyhash/wyrand is based on a MUM mix core created by @vnmakarov and released on Mother's day (https://github.com/vnmakarov/mum-hash) in a [Merkle-Dåmgard construction](https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction).
```C
uint64_t MUM(uint64_t A, uint64_t B){
  __uint128_t c=(__uint128_t)A*B;
  return  (c>>64)^c;
}
```
MUM is powerful in mixing data as 64x64-bit multiplications can do the same work as 32 shifts and additions. Despite the nominal 128-bit multiplication, the actual instructions are only one `MULQ` and one `XORQ` on 64-bit machines. One of our improvements is masked-MUM: `MUM(A^p0, B^p1)`, where p0 and p1 are random prime masks containing 32 1s. The masked-MUM can randomize biased real data toward 32 1s and thus produce an avalanche effect. We observed experimentally that just two rounds of masked-MUM suffice to pass statistical tests.

The wyhash algorithm's interface is as follows:

```C
uint64_t wyhash(const void* p, uint64_t len, uint64_t seed);
```
The algorithm works on 256-bit blocks starting from pointer `p` with the following iterations:

```C
seed = MUM(read64(p)^p0^seed, read64(p+8)^p1^seed) ^ MUM(read64(p+16)^p2^seed, read64(p+24)^p3^seed);
```

It can be viewed as a chaotic dynamic system with 64-bit internal states.

We process the last block with proper paddings and finalize the hash with:

```C
return MUM(seed^len, p4);
```

Note that the finalization MUM is critical to pass statistical tests.

wyhash reads the data with the `memcpy` function. This is necessary because some machine architectures do not support unaligned reads and will generate hardware exceptions. A key trick to speedup wyhash is that in the last block each 64-bit reading is implemented as two 32-bit readings: `read64(p) = (read32(p)<<32) | read32(p+4)`. This trick may be explained by the fact that memory is 4-byte aligned.

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

We evaluated wyrand with BigCrush and Practrand. wyrand passed both tests. The BigCrush results are attached as supporting information. We benchmarked wyrand, lehmer64, 3 parallel lehmer64, splitmix64, xoshiro256, pcg64 and pcg32 PRNGs using loops with 4 billion iterations.
```
g++ BenchmarkPRNG.cpp -o BenchmarkPRNG -O2 -fno-tree-vectorize -Wall
```
The result is shown in the table below:

| PRNG | ns/rand | vs wyrand |
| ---- | ---- | ---- |
| wyrand | 0.868 | 100.000% |
| lehmer64 | 1.359 | 156.538% |
| 3-lehmer64 | 0.906 | 104.412% |
| splitmix64 | 1.366 | 157.331% |
| xoshiro256 | 3.424 | 394.455% |
| pcg64 | 2.760 | 318.042% |
| pcg32 | 1.471 | 169.500% |


## (D. Lemire: If you are going to offer a hash function, and claim that it can be useful for hash tables, then you have to test it out. We know that the murmur hash function is good enough to achieve good performance with hash tables. See for example: Richter, Stefan; Alvarez, Victor; Dittrich, Jens (2015), "A seven-dimensional analysis of hashing methods and its implications on query processing" (PDF), Proceedings of the VLDB Endowment, 9 (3): 293–331.) Yi Wang: I did some experiment and show that in state-of-art hash tables (https://github.com/skarupke/flat_hash_map) with short string key, hash function is not a bottleneck. Replacing default hash function with wyhash yields ~1% speedup.

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
- [Go](https://github.com/dgryski/go-wyhash)
- [Rust](https://github.com/eldruin/wyhash-rs)
- [Swift](https://github.com/lemire/SwiftWyhash)

TODO: Add speed comparisons between the different language ports and the C implementation?

----------------------------------------

**Discussion**

----------------------------------------

**Acknowledgment**

We appreciate these people/users for contributing code and/or comments in the development of wyhash/wyrand.

Reini Urban, Dietrich Epp, Joshua Haberman, Tommy Ettinger, Daniel Lemire, Otmar Ertl, cocowalla, leo-yuriev

**TODO** you are welcome to the author area by joining the paper writing process.

----------------------------------------

**References**
