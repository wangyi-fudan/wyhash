As working on machine learning, I desire a dream hash and PRNG. t1ha helps me very much, however, I am just too thirsty to perfection ...

The main insight of my hash and PRNG is the following method (learnt from https://github.com/vnmakarov/mum-hash):

uint64_t	mix(uint64_t	A,	uint64_t	B){

	__uint128_t	r=A^p0;	r*=B^p1;
	
	return	(r>>64)^r;
	
}

Only two rounds of such mix operation completely randomized the bits.


https://github.com/rurban/smhasher

| key/cycles | wyhash | t1ha2_atonce | t1ha1_64le | t1ha0_aes_noavx | speedup |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 1-byte | 16.29 | 29.00 | 30.64 | 29.28 | 78% |
| 2-byte | 16.47 | 29.00 | 30.67 | 29.00 | 76% |
| 3-byte | 18.00 | 29.00 | 30.65 | 29.00 | 61% |
| 4-byte | 16.00 | 29.00 | 30.65 | 29.41 | 81% |
| 5-byte | 18.00 | 29.00 | 30.69 | 29.33 | 61% |
| 6-byte | 18.00 | 29.00 | 30.71 | 29.28 | 61% |
| 7-byte | 18.81 | 29.00 | 30.65 | 29.33 | 54% |
| 8-byte | 24.00 | 29.00 | 30.32 | 29.00 | 21% |
| 9-byte | 25.00 | 32.00 | 30.00 | 32.00 | 20% |
| 10-byte | 25.00 | 32.58 | 30.55 | 32.26 | 22% |
| 11-byte | 25.00 | 32.52 | 30.00 | 32.00 | 20% |
| 12-byte | 25.23 | 32.40 | 26.99 | 32.70 | 7% |
| 13-byte | 25.00 | 32.59 | 26.99 | 32.79 | 8% |
| 14-byte | 25.00 | 32.53 | 26.99 | 32.70 | 8% |
| 15-byte | 25.14 | 32.41 | 26.99 | 32.73 | 7% |
| 16-byte | 24.96 | 32.00 | 26.66 | 32.27 | 7% |
| 17-byte | 26.00 | 36.80 | 34.00 | 36.00 | 31% |
| 18-byte | 26.00 | 36.78 | 34.00 | 36.00 | 31% |
| 19-byte | 26.11 | 36.98 | 34.00 | 36.58 | 30% |
| 20-byte | 26.00 | 37.03 | 34.00 | 37.25 | 31% |
| 21-byte | 26.00 | 37.07 | 34.11 | 37.21 | 31% |
| 22-byte | 26.00 | 36.93 | 34.00 | 36.63 | 31% |
| 23-byte | 26.12 | 36.71 | 34.00 | 36.00 | 30% |
| 24-byte | 26.00 | 36.34 | 34.00 | 36.00 | 31% |
| 25-byte | 27.28 | 40.77 | 27.11 | 40.97 | -1% |
| 26-byte | 27.41 | 40.51 | 27.00 | 40.97 | -1% |
| 27-byte | 27.00 | 40.54 | 27.00 | 40.99 | 0% |
| 28-byte | 27.28 | 40.00 | 27.00 | 40.98 | -1% |
| 29-byte | 27.00 | 40.72 | 27.00 | 40.87 | 0% |
| 30-byte | 27.00 | 40.56 | 27.00 | 40.96 | 0% |
| 31-byte | 27.59 | 40.61 | 27.00 | 40.87 | -2% |

----------------------------------------
https://github.com/leo-yuriev/t1ha

Build by GNU C/C++ compiler 7.3 (self-check passed)

Testing t1ha2_atonce... Ok

Testing t1ha2_atonce128... Ok

Testing t1ha2_stream... Ok

Testing t1ha2_stream128... Ok

Testing t1ha1_64le... Ok

Testing t1ha1_64be... Ok

Testing t1ha0_32le... Ok

Testing t1ha0_32be... Ok

Testing t1ha0_ia32aes_noavx... Ok

Testing t1ha0_ia32aes_avx... Ok

Testing t1ha0_ia32aes_avx2... Ok

Testing wyhash... Ok

Testing HighwayHash64_portable_cxx... Ok

Testing HighwayHash64_sse41... Ok

Testing HighwayHash64_avx2... Ok

Testing StadtX... Ok



Preparing to benchmarking...

 - running on CPU#6

 - use RDPMC_40000001 as clock source for benchmarking

 - assume it cheap and stable

 - measure granularity and overhead: 54 cycles, 0.0185185 iteration/cycle



Bench for tiny keys (7 bytes):

t1ha2_atonce            :     17.266 cycle/hash,  2.467 cycle/byte,  0.405 byte/cycle,  1.216 GB/s @3.0GHz 

t1ha2_atonce128*        :     34.781 cycle/hash,  4.969 cycle/byte,  0.201 byte/cycle,  0.604 GB/s @3.0GHz 

t1ha2_stream*           :     80.812 cycle/hash, 11.545 cycle/byte,  0.087 byte/cycle,  0.260 GB/s @3.0GHz 

t1ha2_stream128*        :    101.688 cycle/hash, 14.527 cycle/byte,  0.069 byte/cycle,  0.207 GB/s @3.0GHz 

t1ha1_64le              :     18.266 cycle/hash,  2.609 cycle/byte,  0.383 byte/cycle,  1.150 GB/s @3.0GHz 

t1ha0                   :     15.133 cycle/hash,  2.162 cycle/byte,  0.463 byte/cycle,  1.388 GB/s @3.0GHz 

xxhash32                :     18.677 cycle/hash,  2.668 cycle/byte,  0.375 byte/cycle,  1.124 GB/s @3.0GHz 

xxhash64                :     25.203 cycle/hash,  3.600 cycle/byte,  0.278 byte/cycle,  0.833 GB/s @3.0GHz 

StadtX                  :     19.266 cycle/hash,  2.752 cycle/byte,  0.363 byte/cycle,  1.090 GB/s @3.0GHz 

wyhash                  :     15.164 cycle/hash,  2.166 cycle/byte,  0.462 byte/cycle,  1.385 GB/s @3.0GHz 

HighwayHash64_portable  :    492.500 cycle/hash, 70.357 cycle/byte,  0.014 byte/cycle,  0.043 GB/s @3.0GHz 

HighwayHash64_sse41     :     67.875 cycle/hash,  9.696 cycle/byte,  0.103 byte/cycle,  0.309 GB/s @3.0GHz 

HighwayHash64_avx2      :     56.844 cycle/hash,  8.121 cycle/byte,  0.123 byte/cycle,  0.369 GB/s @3.0GHz 



Bench for large keys (16384 bytes):

t1ha2_atonce            :   3543.000 cycle/hash,  0.216 cycle/byte,  4.624 byte/cycle, 13.873 GB/s @3.0GHz 

t1ha2_atonce128*        :   3566.000 cycle/hash,  0.218 cycle/byte,  4.595 byte/cycle, 13.784 GB/s @3.0GHz 

t1ha2_stream*           :   3706.000 cycle/hash,  0.226 cycle/byte,  4.421 byte/cycle, 13.263 GB/s @3.0GHz 

t1ha2_stream128*        :   3716.000 cycle/hash,  0.227 cycle/byte,  4.409 byte/cycle, 13.227 GB/s @3.0GHz 

t1ha1_64le              :   3534.000 cycle/hash,  0.216 cycle/byte,  4.636 byte/cycle, 13.908 GB/s @3.0GHz 

t1ha0                   :   1379.000 cycle/hash,  0.084 cycle/byte, 11.881 byte/cycle, 35.643 GB/s @3.0GHz 

xxhash32                :   8198.000 cycle/hash,  0.500 cycle/byte,  1.999 byte/cycle,  5.996 GB/s @3.0GHz 

xxhash64                :   4119.000 cycle/hash,  0.251 cycle/byte,  3.978 byte/cycle, 11.933 GB/s @3.0GHz 

StadtX                  :   3628.000 cycle/hash,  0.221 cycle/byte,  4.516 byte/cycle, 13.548 GB/s @3.0GHz 

wyhash                  :   9047.000 cycle/hash,  0.552 cycle/byte,  1.811 byte/cycle,  5.433 GB/s @3.0GHz 

HighwayHash64_portable  :  43949.609 cycle/hash,  2.682 cycle/byte,  0.373 byte/cycle,  1.118 GB/s @3.0GHz 

HighwayHash64_sse41     :   6418.000 cycle/hash,  0.392 cycle/byte,  2.553 byte/cycle,  7.658 GB/s @3.0GHz 

HighwayHash64_avx2      :   4524.000 cycle/hash,  0.276 cycle/byte,  3.622 byte/cycle, 10.865 GB/s @3.0GHz 

----------------------------------------

https://github.com/lemire/testingRNG

| PRNG |  cycles per byte |
| ---- | ---- |
| xorshift_k4 | 1.65 |
| xorshift_k5 | 1.72 |
| mersennetwister | 2.52 |
| mitchellmoore | 3.04 |
| widynski | 1.83 |
| xorshift32 | 2.03 |
| pcg32 | 1.68 |
| rand | 5.02 |
| aesdragontamer | 0.85 |
| aesctr | 0.83 |
| lehmer64 | 0.84 |
| xorshift128plus | 0.83 |
| xoroshiro128plus | 0.93 |
| splitmix64 | 0.83 |
| pcg64 | 1.12 |
| xorshift1024star | 1.24 |
| xorshift1024plus | 0.88 |
| wyrng | 0.74 |

