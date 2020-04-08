//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_gamma
#define wyhash_version_gamma
//defines that change behavior
#define WYHASH_SAFE_MUM  0	//loss of entroy every 2^66 bytes
#define WYHASH_SAFE_READ 0	//may read up to 8 bytes before/after if len<8
#define WYHASH_32BIT_MUM 0	//faster on 32 bit system
//includes
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
  #include <intrin.h>
  #pragma intrinsic(_umul128)
#endif
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
  #define _likely_(x)	__builtin_expect(x,1)
#else
  #define _likely_(x) (x)
#endif
//mum function
static inline uint64_t _wyrot(uint64_t x) { return (x>>32)|(x<<32); }
static inline void _wymum(uint64_t *A, uint64_t *B){
#if(WYHASH_32BIT_MUM)
  uint64_t hh=(*A>>32)*(*B>>32), hl=(*A>>32)*(unsigned)*B, lh=(unsigned)*A*(*B>>32), ll=(uint64_t)(unsigned)*A*(unsigned)*B;
  #if(WYHASH_SAFE_MUM)
  *A|=_wyrot(hl)^hh; *B|=_wyrot(lh)^ll;
  #else
  *A=_wyrot(hl)^hh; *B=_wyrot(lh)^ll;
  #endif
#elif defined(__SIZEOF_INT128__)
  __uint128_t r=*A; r*=*B; 
  #if(WYHASH_SAFE_MUM)
  *A|=(uint64_t)r; *B|=(uint64_t)(r>>64);
  #else
  *A=(uint64_t)r; *B=(uint64_t)(r>>64);
  #endif
#elif defined(_MSC_VER) && defined(_M_X64)
  #if(WYHASH_SAFE_MUM)
  uint64_t  a,  b;
  a=_umul128(*A,*B,&b);
  *A|=a;  *B|=b;
  #else
  *A=_umul128(*A,*B,B);
  #endif
#else
  uint64_t ha=*A>>32, hb=*B>>32, la=(uint32_t)*A, lb=(uint32_t)*B, hi, lo;
  uint64_t rh=ha*hb, rm0=ha*lb, rm1=hb*la, rl=la*lb, t=rl+(rm0<<32), c=t<rl;
  lo=t+(rm1<<32); c+=lo<t; hi=rh+(rm0>>32)+(rm1>>32)+c;
  #if(WYHASH_SAFE_MUM)
  *A|=lo;  *B|=hi;
  #else
  *A=lo;  *B=hi;
  #endif
#endif
}
//read functions
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
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return __builtin_bswap64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return __builtin_bswap32(v);}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return _byteswap_uint64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { unsigned v; memcpy(&v, p, 4); return _byteswap_ulong(v);}
#endif
static inline uint64_t _wyr3(const uint8_t *p, unsigned k) { return (((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];}
//wyhash function
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed, const uint64_t *secret){
  const uint8_t *p=(const uint8_t *)key;
  uint64_t i=len, see1=seed; 
  start:
  if(_likely_(i<=16)){
    #if(WYHASH_SAFE_READ)
    if(_likely_(i<=8)){
      if(_likely_(i>=4)){ seed^=_wyr4(p)^secret[0]; see1^=_wyr4(p+i-4)^secret[1];}
      else if (_likely_(i)){ seed^=_wyr3(p,i)^secret[0]; see1^=secret[1];}
      else{ seed^=secret[0]; see1^=secret[1];}
    } 
    else{ seed^=_wyr8(p)^secret[0];  see1^=_wyr8(p+i-8)^secret[1];}
	#else
    uint64_t shift=(i<8)*((8-i)<<3);  
    seed^=(_wyr8(p)<<shift)^secret[0];  see1^=(_wyr8(p+i-8)>>shift)^secret[1];
    #endif
    _wymum(&seed, &see1); seed^=len; _wymum(&seed, &see1);
    return seed^see1;
  }
  seed^=_wyr8(p)^secret[0]; see1^=_wyr8(p+8)^secret[1]; _wymum(&seed, &see1);
  i-=16; p+=16; goto start;
}
//utility functions
const uint64_t _wyp[2]={0xa0761d6478bd642full, 0xe7037ed1a0b428dbull};
static inline uint64_t wyhash64(uint64_t A, uint64_t B){  A^=_wyp[0];	B^=_wyp[1];  _wymum(&A,&B);  _wymum(&A,&B);  return  A^B;}
static inline uint64_t wyrand(uint64_t *seed){  *seed+=_wyp[0]; uint64_t  a=*seed, b=*seed^_wyp[1]; _wymum(&a,&b); return  a^b;}
static inline double wy2u01(uint64_t r){ const double _wynorm=1.0/(1ull<<52); return (r>>12)*_wynorm;}
static inline double wy2gau(uint64_t r){ const double _wynorm=1.0/(1ull<<20); return ((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;}
static inline void make_secret(uint64_t seed, uint64_t secret[2]){
  uint8_t c[] = {15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60, 71, 75, 77, 78, 83, 85, 86, 89, 90, 92, 99, 101, 102, 105, 106, 108, 113, 114, 116, 120, 135, 139, 141, 142, 147, 149, 150, 153, 154, 156, 163, 165, 166, 169, 170, 172, 177, 178, 180, 184, 195, 197, 198, 201, 202, 204, 209, 210, 212, 216, 225, 226, 228, 232, 240 };
  for(size_t i=0;i<2;i++){
    uint8_t ok;
    do{
      ok=1; secret[i]=0;
      for(size_t j=0;j<64;j+=8) secret[i]|=((uint64_t)c[wyrand(&seed)%sizeof(c)])<<j;
      for(size_t j=0;j<i;j++)
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
        if(__builtin_popcountll(secret[i]^secret[j])!=32){ ok=0; break; }
#elif defined(_MSC_VER)
        if(_mm_popcnt_u64(secret[i]^secret[j])!=32){ ok=0; break; }
#endif
    }while(!ok);
  }
}
#endif
