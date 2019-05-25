Simple Is Best
========

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: solid, portable, fastest, simplest. wyhash passed SMHasher, wyrand passed BigCrush, practrand and designed to drop-in replace C rand().

wyhash test vectors:
```
wyhash("",0)=f961f936e29c9345
wyhash("a",1)=6dc395f88b363baa
wyhash("abc",2)=3bc9d7844798ddaa
wyhash("message digest",3)=b31238dc2c500cd3
wyhash("abcdefghijklmnopqrstuvwxyz",4)=ea0f542c58cddfe4
wyhash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",5)=1799aca591fe73b4
wyhash("12345678901234567890123456789012345678901234567890123456789012345678901234567890",6)=7f0d02f53d64c1f9
```
wyrand code:
```
inline	uint64_t	wyrand(uint64_t	*seed){    
	*seed+=0xa0761d6478bd642full;    
	__uint128_t	t=(__uint128_t)(*seed^0xe7037ed1a0b428dbull)*(*seed);    
	return	(t>>64)^t;    
}
```

The speed benchmarks are as follow:

https://github.com/rurban/smhasher

| key/cycles | wyhash | XXH3 | t1ha2_atonce | t1ha1_64le | t1ha0_aes_noavx | speedup |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 1-byte | 16.00 | 19.00 | 29.00 | 30.64 | 29.28 | 18.75% |
| 2-byte | 16.00 | 19.00 | 29.00 | 30.67 | 29.00 | 18.75% |
| 3-byte | 17.00 | 19.00 | 29.00 | 30.65 | 29.00 | 11.76% |
| 4-byte | 16.00 | 17.00 | 29.00 | 30.65 | 29.41 | 6.25% |
| 5-byte | 17.00 | 24.00 | 29.00 | 30.69 | 29.33 | 41.18% |
| 6-byte | 17.00 | 24.00 | 29.00 | 30.71 | 29.28 | 41.18% |
| 7-byte | 18.00 | 24.00 | 29.00 | 30.65 | 29.33 | 33.33% |
| 8-byte | 17.00 | 17.00 | 29.00 | 30.32 | 29.00 | 0.00% |
| 9-byte | 17.00 | 25.00 | 32.00 | 30.00 | 32.00 | 47.06% |
| 10-byte | 17.00 | 25.00 | 32.58 | 30.55 | 32.26 | 47.06% |
| 11-byte | 17.00 | 25.00 | 32.52 | 30.00 | 32.00 | 47.06% |
| 12-byte | 17.00 | 25.00 | 32.40 | 26.99 | 32.70 | 47.06% |
| 13-byte | 17.00 | 25.00 | 32.59 | 26.99 | 32.79 | 47.06% |
| 14-byte | 17.15 | 25.00 | 32.53 | 26.99 | 32.70 | 45.77% |
| 15-byte | 17.00 | 25.00 | 32.41 | 26.99 | 32.73 | 47.06% |
| 16-byte | 17.00 | 25.00 | 32.00 | 26.66 | 32.27 | 47.06% |
| 17-byte | 18.00 | 28.00 | 36.80 | 34.00 | 36.00 | 55.56% |
| 18-byte | 18.00 | 28.00 | 36.78 | 34.00 | 36.00 | 55.56% |
| 19-byte | 18.00 | 28.00 | 36.98 | 34.00 | 36.58 | 55.56% |
| 20-byte | 18.00 | 27.00 | 37.03 | 34.00 | 37.25 | 50.00% |
| 21-byte | 18.00 | 27.31 | 37.07 | 34.11 | 37.21 | 51.72% |
| 22-byte | 18.00 | 27.60 | 36.93 | 34.00 | 36.63 | 53.33% |
| 23-byte | 18.00 | 27.51 | 36.71 | 34.00 | 36.00 | 52.83% |
| 24-byte | 18.00 | 27.00 | 36.34 | 34.00 | 36.00 | 50.00% |
| 25-byte | 18.00 | 27.62 | 40.77 | 27.11 | 40.97 | 50.61% |
| 26-byte | 18.00 | 27.79 | 40.51 | 27.00 | 40.97 | 50.00% |
| 27-byte | 18.00 | 27.78 | 40.54 | 27.00 | 40.99 | 50.00% |
| 28-byte | 18.00 | 27.58 | 40.00 | 27.00 | 40.98 | 50.00% |
| 29-byte | 18.00 | 27.57 | 40.72 | 27.00 | 40.87 | 50.00% |
| 30-byte | 18.00 | 27.66 | 40.56 | 27.00 | 40.96 | 50.00% |
| 31-byte | 18.00 | 27.69 | 40.61 | 27.00 | 40.87 | 50.00% |

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
