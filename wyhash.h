//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_gamma
#define wyhash_version_gamma
#include <stdint.h>
#include <string.h>
const uint64_t _wyp0=0xa0761d6478bd642full, _wyp1=0xe7037ed1a0b428dbull;
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
#define _likely_(x) __builtin_expect(x, 1)
#else
#define _likely_(x) (x)
#endif
#ifndef WYHASH_LITTLE_ENDIAN
#if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 0
#endif
#endif
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return v;}
static inline uint64_t _wyr4(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return v;}
#else
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return __builtin_bswap64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return __builtin_bswap32(v);}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return _byteswap_uint64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return _byteswap_ulong(v);}
#endif
#endif
static inline uint64_t _wyr3(const uint8_t *p, unsigned k) { return (((uint64_t)p[0]) << 16) | (((uint64_t)p[k >> 1]) << 8) | p[k - 1];}

static inline uint64_t _wyrot32(uint64_t x){ return (x>>32)|(x<<32); }

static inline uint64_t _wymix64(uint64_t x){ return x*_wyrot32(x); }

static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed){
	const uint8_t *p=(const uint8_t *)key;
	uint64_t i=len, see1=seed; 
	loop:
	if(_likely_(i<=16)){
	#ifndef	WYHASH_CONDOM
		uint64_t shift=(i<8)*((8-i)<<3);
		seed=_wymix64(((_wyr8(p)<<shift)^_wyp0)^seed); 
		see1=_wymix64(((_wyr8(p+i-8)>>shift)^_wyp1)^see1);
	#else
		if(_likely_(i<=8)){
			if(_likely_(i>=4))
				seed=_wymix64(((_wyr4(p)<<32)|_wyr4(p+i-4))^seed^_wyp0);
			else if (_likely_(i))
				seed=_wymix64(_wyr3(p,i)^seed^_wyp0);
			else
				seed=_wymix64(seed^_wyp0);
		} 
  		else{
			seed=_wymix64(_wyr8(p)^seed^_wyp0);
			see1=_wymix64(_wyr8(p+i-8)^see1^_wyp1);
		}
	#endif
		return	_wyrot32(_wymix64(len^seed^see1)) ^ _wymix64(_wyp1^_wyrot32(seed)^see1);
	}
	seed=_wymix64((_wyr8(p)^_wyp0)^seed);
	see1=_wymix64((_wyr8(p+8)^_wyp1)^see1);
	i-=16;	p+=16;
	goto loop;
}

static inline unsigned wyhash2(unsigned A,	unsigned	B){ 
	uint64_t	c=(((uint64_t)A)<<32)|B;	
	c=_wymix64(_wymix64(c^_wyp0));
	return	(c>>32)^(unsigned)c;
}

static inline unsigned wyrand(uint64_t *seed){
	*seed+=_wyp0;	
	uint64_t x=_wymix64(*seed^_wyp1);
	return	(x>>32)^(unsigned)x;
}

static inline float wy2u01(unsigned r){
	const float _wynorm=1.0f/(1ull<<23); 
	return (r>>9)*_wynorm;
}

static inline float wy2gau(unsigned r){
	const float _wynorm=1.0f/(1ull<<9); 
	return ((r&0x3ff)+((r>>10)&0x3ff)+((r>>20)&0x3ff))*_wynorm-3.0f;
}
#endif
