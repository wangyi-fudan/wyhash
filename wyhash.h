//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_gamma
#define wyhash_version_gamma
#include <stdint.h>
#include <string.h>
static inline __uint128_t _wyread128(const void *p){ __uint128_t x; memcpy(&x,p,16); return x; }
static inline __uint128_t _wymix128(__uint128_t x){ return (x>>64)*(uint64_t)x; }
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed){
 const __uint128_t _wyp=(((__uint128_t)0xa0761d6478bd642full)<<64)|0xe7037ed1a0b428dbull;  
 const uint8_t *p=(const uint8_t *)key;
 uint64_t len0=len; 
 __uint128_t x=seed;
 for(;len>16;len-=16,p+=16) x=_wymix128(_wyread128(p)^x^_wyp);
 x=_wymix128(_wymix128((_wyread128(p)<<((16-len)<<3))^x^_wyp)^len0); 
 return (x>>64)^(uint64_t)x; 
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B){ __uint128_t r=A^0xa0761d6478bd642full; r*=B^0xe7037ed1a0b428dbull; r=(r>>64)*(uint64_t)r; return (r>>64)^(uint64_t)r;}
static inline uint64_t wyrand(uint64_t *seed){ __uint128_t r=(*seed+=0xa0761d6478bd642full); r*=*seed^0xe7037ed1a0b428dbull; return (r>>64)^(uint64_t)r;}
static inline double wy2u01(uint64_t r){ const double _wynorm=1.0/(1ull<<52); return (r>>11)*_wynorm;}
static inline double wy2gau(uint64_t r){ const double _wynorm=1.0/(1ull<<20); return ((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;}
#endif
