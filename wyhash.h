//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_gamma
#define wyhash_version_gamma
#include <stdint.h>
#include <string.h>
const uint64_t _wyp0=0xa0761d6478bd642full, _wyp1=0xe7037ed1a0b428dbull;
#ifndef WYHASH_LITTLE_ENDIAN
#if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 0
#endif
#endif
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyread64(const uint8_t *p){ uint64_t v; memcpy(&v, p, 8); return v;}
#else
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyread64(const uint8_t *p){ uint64_t v; memcpy(&v, p, 8); return __builtin_bswap64(v);}
#elif defined(_MSC_VER)
static inline uint64_t _wyread64(const uint8_t *p){ uint64_t v; memcpy(&v, p, 8); return _byteswap_uint64(v);}
#endif
#endif

static inline uint64_t _wyrot32(uint64_t x){ return (x>>32)|(x<<32); }

static inline uint64_t _wymix64(uint64_t x){ return x*_wyrot32(x); }

static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed){
	const uint8_t *p=(const uint8_t *)key;
	uint64_t see1=seed, len0=len; 
	for(;len>16;len-=16,p+=16){
		seed=_wymix64(_wyread64(p)^seed^_wyp0);
		see1=_wymix64(_wyread64(p+8)^see1^_wyp1);
	}
	//intended unsafe read, trade for great speed.
	uint64_t d0=_wyread64(p), d1=_wyread64(p+len-8);
	len=(len<8)*((8-len)<<3);
	d0<<=len;  d1>>=len;
	seed=_wymix64(d0^seed^_wyp0); 
	see1=_wymix64(d1^see1^_wyp1);
	return	 _wyrot32(_wymix64(len0^seed^see1))
			^_wymix64(_wyp1^_wyrot32(seed)^see1);
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
