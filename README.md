Simple Is Best
========

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: solid, portable, fastest, simplest. wyhash passed SMHasher, wyrand passed BigCrush, practrand and designed to drop-in replace C rand(). See our [manuscript](manuscript.md).

Updated to version 3
----
Dear user and developers, for a hard night work, I propose wyhash version 3 draft. Version 3 provides double bulk hash speed and slightly faster for short keys compared to version 2. Hope you like it.

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

|bulk:bytes/cycle|9.888|15.500|7.872|
|samll:cycles | wyhash | XXH3 | t1ha2_atonce |
| ---- | ---- | ---- | ---- |
| 1-byte | 16.00 | 19.00 | 29.00 |
| 2-byte | 16.00 | 19.00 | 29.00 |
| 3-byte | 17.00 | 19.00 | 29.00 | 
| 4-byte | 16.00 | 17.00 | 29.00 | 
| 5-byte | 17.00 | 24.00 | 29.00 | 
| 6-byte | 17.00 | 24.00 | 29.00 | 
| 7-byte | 18.00 | 24.00 | 29.00 | 
| 8-byte | 17.00 | 17.00 | 29.00 | 
| 9-byte | 17.00 | 25.00 | 32.00 | 
| 10-byte | 17.00 | 25.00 | 32.58 |
| 11-byte | 17.00 | 25.00 | 32.52 |
| 12-byte | 17.00 | 25.00 | 32.40 |
| 13-byte | 17.00 | 25.00 | 32.59 |
| 14-byte | 17.15 | 25.00 | 32.53 |
| 15-byte | 17.00 | 25.00 | 32.41 |
| 16-byte | 17.00 | 25.00 | 32.00 |
| 17-byte | 18.00 | 28.00 | 36.80 |
| 18-byte | 18.00 | 28.00 | 36.78 |
| 19-byte | 18.00 | 28.00 | 36.98 |
| 20-byte | 18.00 | 27.00 | 37.03 |
| 21-byte | 18.00 | 27.31 | 37.07 |
| 22-byte | 18.00 | 27.60 | 36.93 |
| 23-byte | 18.00 | 27.51 | 36.71 |
| 24-byte | 18.00 | 27.00 | 36.34 |
| 25-byte | 18.00 | 27.62 | 40.77 |
| 26-byte | 18.00 | 27.79 | 40.51 |
| 27-byte | 18.00 | 27.78 | 40.54 |
| 28-byte | 18.00 | 27.58 | 40.00 |
| 29-byte | 18.00 | 27.57 | 40.72 |
| 30-byte | 18.00 | 27.66 | 40.56 |
| 31-byte | 18.00 | 27.69 | 40.61 |

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
