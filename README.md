Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: solid, portable, fastest, simplest. wyhash passed SMHasher, wyrand passed BigCrush, practrand and designed to drop-in replace C rand(). See our [manuscript](manuscript.md). Currently wyhash is a hasher by default in a hash table in the great Zig language.

wyhash vs XXH3
====
Initially, we found wyhash is fastest for short keys based on SMHasher. However, things becomes complex later. I will discuss as follow:

Safety and Portability:
----
0: wyhash passes all SMHasher tests, while XXH3 fails on recent moment chi2 test created by me (without intention).

1: wyhash obeys all safty rules. It uses memcpy to access memory, while XXH3 do unaligned memory access.

2: wyhash is about 62 bit strength against hash collision, not perfect but not bad. XXH3 is of 64 bit strength.

3: the amazing bulk speed of XXH is based on AVX2 instruction, while wyhash uses no "magic" instructions.

4: the wyhash_v3 have a macro WYHASH_EVIL_FAST which is unsafe but fast, I leave the choice for users.

5: wyhash paid attentions on adverarial attacks, though I can't prove wyhash is secure due my poor math.

Speed:
----
0: XXH3 is faster on bulk hash with AVX2 instruction. With SSE instruction, XXH3 and wyhash are of similar speed. And without any vector instructions, wyhash is faster.

1: for fixed length short keys, wyhash is the faster due to inlining.

2: for dynamic length short keys, XXH3 is faster. 

3: If you turn on WYHASH_EVIL_FAST, wyhash is faster on dynamic length short keys.

----------------------------------------

wyrand code:
```C
inline	uint64_t	wyrand(uint64_t	*seed){    
	*seed+=0xa0761d6478bd642full;    
	__uint128_t	t=(__uint128_t)(*seed^0xe7037ed1a0b428dbull)*(*seed);    
	return	(t>>64)^t;    
}
```

The speed benchmarks are as follow:

https://github.com/rurban/smhasher


|key size | wyhash | XXH_SCALAR|XXH_SSE2|XXH3_AVX2 | t1ha2_atonce |
| ---- | ---- | ---- | ---- | ---- | ---- |
|bulk:bytes/cycle|9.888 | 3.173| 9.931|15.500|7.872|
|small:cycles/hash|13.070 |18.293 |18.304|18.242|25.830|

----------------------------------------

https://github.com/lemire/testingRNG

| PRNG |  cycles per byte |
| ---- | ---- |
| xorshift_k4 | 1.60 |
| xorshift_k5 | 1.77 |
| mersennetwister | 2.41 |
| mitchellmoore | 3.12 |
| widynski | 1.88 |
| xorshift32 | 2.07 |
| pcg32 | 1.72 |
| rand | 5.04 |
| aesdragontamer | 0.71 |
| aesctr | 0.83 |
| lehmer64 | 0.86 |
| xorshift128plus | 0.85 |
| xoroshiro128plus | 0.96 |
| splitmix64 | 0.85 |
| pcg64 | 1.16 |
| xorshift1024star | 1.28 |
| xorshift1024plus | 0.91 |
| wyrand | 0.67 |

----------------------------------------

Lemire:[The fastest conventional random number generator that can pass Big Crush?](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/)


| PRNG | ns/rand | vs wyrand |
| ---- | ---- | ---- |
| wyrand | 0.792 | 100.000% |
| lehmer64 | 1.219 | 153.858% |
| 3-lehmer64 | 0.816 | 103.010% |
| splitmix64 | 1.220 | 154.059% |
| 3-splitmix64 | 1.134 | 143.214% |
| xoshiro256 | 3.069 | 387.460% |
| pcg64 | 2.559 | 323.004% |
| pcg32 | 1.320 | 166.617% |

----------------------------------------

I thank these names:

Reini Urban

Dietrich Epp

Joshua Haberman

Tommy Ettinger

Daniel Lemire

Otmar Ertl

cocowalla

leo-yuriev

Diego Barrios Romero

paulie-g 

dumblob
