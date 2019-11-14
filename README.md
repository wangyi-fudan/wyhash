Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: solid, portable, fastest, simplest. wyhash passed SMHasher, wyrand passed BigCrush, practrand and designed to drop-in replace C rand(). See our [manuscript](manuscript.md). Currently wyhash is a hasher by default in a hash table in the great Zig language.

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


|key size | wyhash | XXH3_SCALAR| XXH3_SSE| XXH3_AVX2 | t1ha2_atonce |
| ---- | ---- | ---- | ---- | ---- | ---- |
|bulk:bytes/cycle|5.258 | 2.568|6.422|8.427|6.089|
|small:cycles/hash|18.698 |23.097 |23.097|23.097|31.609|
|hashmap:cycles/op|178.641 |182.231 |182.267|180.901|186.502|

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

Yann Collet

