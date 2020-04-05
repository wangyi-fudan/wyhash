//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_gamma
#define wyhash_version_gamma
#include <stdint.h>
#include <string.h>
const	uint64_t	_wyp0=0xa0761d6478bd642full,	_wyp1=0xe7037ed1a0b428dbull;
static inline __uint128_t _wyread128(const void *p){ __uint128_t x; memcpy(&x,p,16); return x; }
static inline __uint128_t _wymix128(__uint128_t x){ return (x>>64)*(uint64_t)x; }
static inline uint64_t wyhash(const void *key, uint64_t len, __uint128_t seed){
 const __uint128_t _wyp=(((__uint128_t)_wyp0)<<64)|_wyp1; const uint8_t *p=(const uint8_t *)key; uint64_t len0=len; start:
 if(len<=16){ seed=_wymix128(_wymix128((_wyread128(p)<<((16-len)<<3))^seed^_wyp)^len0); return (seed>>64)^(uint64_t)seed; }
 else{ seed=_wymix128(_wyread128(p)^seed^_wyp); len-=16; p+=16; goto start; }
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B){ __uint128_t r=A^_wyp0; r*=B^_wyp1; r=(r>>64)*(uint64_t)r; return (r>>64)^(uint64_t)r;}
static inline uint64_t wyrand(uint64_t *seed){ __uint128_t r=(*seed+=_wyp0); r*=*seed^_wyp1; return (r>>64)^(uint64_t)r;}
static inline double wy2u01(uint64_t r){ const double _wynorm=1.0/(1ull<<52); return (r>>11)*_wynorm;}
static inline double wy2gau(uint64_t r){ const double _wynorm=1.0/(1ull<<20); return ((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;}
#endif
