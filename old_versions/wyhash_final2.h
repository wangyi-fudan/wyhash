// This is free and unencumbered software released into the public domain under The Unlicense (http://unlicense.org/)
// main repo: https://github.com/wangyi-fudan/wyhash
// author: 王一 Wang Yi <godspeed_china@yeah.net>
// contributors: Reini Urban, Dietrich Epp, Joshua Haberman, Tommy Ettinger, Daniel Lemire, Otmar Ertl, cocowalla, leo-yuriev, Diego Barrios Romero, paulie-g, dumblob, Yann Collet, ivte-ms, hyb, James Z.M. Gao, easyaspi314 (Devin), TheOneric

/* quick example:
   string s="fjsakfdsjkf";
   uint64_t hash=wyhash(s.c_str(), s.size(), 0, _wyp);
*/

#ifndef wyhash_final_version_2
#define wyhash_final_version_2

#ifndef WYHASH_CONDOM
//protections that produce different results:
//0: read 8 bytes before and after boundaries, dangerous but fastest
//1: normal valid behavior
//2: extra protection against entropy loss (probability=2^-63), aka. "blind multiplication"
#define WYHASH_CONDOM 1 
#endif

#ifndef WYHASH_32BIT_MUM
//0: normal version, slow on 32 bit systems
//1: faster on 32 bit systems but produces different results, incompatible with wy2u0k function
#define WYHASH_32BIT_MUM 0	
#endif

//includes
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
  #include <intrin.h>
  #pragma intrinsic(_umul128)
#endif

//likely and unlikely macros
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
  #define _likely_(x)	__builtin_expect(x,1)
  #define _unlikely_(x)	__builtin_expect(x,0)
#else
  #define _likely_(x) (x)
  #define _unlikely_(x) (x)
#endif

//128bit multiply function
static inline uint64_t _wyrot(uint64_t x) { return (x>>32)|(x<<32); }
static inline void _wymum(uint64_t *A, uint64_t *B){
#if(WYHASH_32BIT_MUM)
  uint64_t hh=(*A>>32)*(*B>>32), hl=(*A>>32)*(uint32_t)*B, lh=(uint32_t)*A*(*B>>32), ll=(uint64_t)(uint32_t)*A*(uint32_t)*B;
  #if(WYHASH_CONDOM>1)
  *A^=_wyrot(hl)^hh; *B^=_wyrot(lh)^ll;
  #else
  *A=_wyrot(hl)^hh; *B=_wyrot(lh)^ll;
  #endif
#elif defined(__SIZEOF_INT128__)
  __uint128_t r=*A; r*=*B; 
  #if(WYHASH_CONDOM>1)
  *A^=(uint64_t)r; *B^=(uint64_t)(r>>64);
  #else
  *A=(uint64_t)r; *B=(uint64_t)(r>>64);
  #endif
#elif defined(_MSC_VER) && defined(_M_X64)
  #if(WYHASH_CONDOM>1)
  uint64_t  a,  b;
  a=_umul128(*A,*B,&b);
  *A^=a;  *B^=b;
  #else
  *A=_umul128(*A,*B,B);
  #endif
#else
  uint64_t ha=*A>>32, hb=*B>>32, la=(uint32_t)*A, lb=(uint32_t)*B, hi, lo;
  uint64_t rh=ha*hb, rm0=ha*lb, rm1=hb*la, rl=la*lb, t=rl+(rm0<<32), c=t<rl;
  lo=t+(rm1<<32); c+=lo<t; hi=rh+(rm0>>32)+(rm1>>32)+c;
  #if(WYHASH_CONDOM>1)
  *A^=lo;  *B^=hi;
  #else
  *A=lo;  *B=hi;
  #endif
#endif
}

//multiply and xor mix function, aka MUM
static inline uint64_t _wymix(uint64_t A, uint64_t B){ _wymum(&A,&B); return A^B; }

//endian macros
#ifndef WYHASH_LITTLE_ENDIAN
  #if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    #define WYHASH_LITTLE_ENDIAN 1
  #elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define WYHASH_LITTLE_ENDIAN 0
  #else
    #warning could not determine endianness! Falling back to little endian.
    #define WYHASH_LITTLE_ENDIAN 1
  #endif
#endif

//read functions
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return v;}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v;}
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return __builtin_bswap64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return __builtin_bswap32(v);}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return _byteswap_uint64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return _byteswap_ulong(v);}
#else
static inline uint64_t _wyr8(const uint8_t *p) {
  uint64_t v; memcpy(&v, p, 8);
  return (((v >> 56) & 0xff)| ((v >> 40) & 0xff00)| ((v >> 24) & 0xff0000)| ((v >>  8) & 0xff000000)| ((v <<  8) & 0xff00000000)| ((v << 24) & 0xff0000000000)| ((v << 40) & 0xff000000000000)| ((v << 56) & 0xff00000000000000));
}
static inline uint64_t _wyr4(const uint8_t *p) {
  uint32_t v; memcpy(&v, p, 4);
  return (((v >> 24) & 0xff)| ((v >>  8) & 0xff00)| ((v <<  8) & 0xff0000)| ((v << 24) & 0xff000000));
}
#endif
static inline uint64_t _wyr3(const uint8_t *p, size_t k) { return (((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];}

//wyhash main function
static inline uint64_t wyhash(const void *key, size_t len, uint64_t seed, const uint64_t *secret){
  const uint8_t *p=(const uint8_t *)key; uint64_t a,b; seed^=*secret;
  if(_likely_(len<=16)){
#if(WYHASH_CONDOM>0)
    if(_likely_(len<=8)){
      if(_likely_(len>=4)){ a=_wyr4(p); b=_wyr4(p+len-4); }
      else if (_likely_(len>0)){ a=_wyr3(p,len); b=0; }
      else a=b=0;
    } 
    else{ a=_wyr8(p); b=_wyr8(p+len-8); }
#else
    size_t s=(len<8)*((8-len)<<3);
    a=_wyr8(p)<<s;	b=_wyr8(p+len-8)>>s;
#endif
  }
  else{
    size_t i=len;
    if(_unlikely_(i>48)){
      uint64_t see1=seed, see2=seed;
      do{
        seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);
        see1=_wymix(_wyr8(p+16)^secret[2],_wyr8(p+24)^see1);
        see2=_wymix(_wyr8(p+32)^secret[3],_wyr8(p+40)^see2);
        p+=48; i-=48;
      }while(i>48);
      seed^=see1^see2;
    }
    while(_unlikely_(i>16)){	seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);	i-=16; p+=16;	}
    a=_wyr8(p+i-16); b=_wyr8(p+i-8);
  }
  return _wymix(secret[1]^len,_wymix(a^secret[1], b^seed));
}

//the default secret parameters
static const uint64_t _wyp[4] = {0xa0761d6478bd642full, 0xe7037ed1a0b428dbull, 0x8ebc6af09c88c6e3ull, 0x589965cc75374cc3ull};

//a useful 64bit-64bit mix function to produce deterministic pseudo random numbers that can pass BigCrush and PractRand
static inline uint64_t wyhash64(uint64_t A, uint64_t B){ A^=_wyp[0]; B^=_wyp[1]; _wymum(&A,&B); return _wymix(A^_wyp[0],B^_wyp[1]);}

//The wyrand PRNG that pass BigCrush and PractRand
static inline uint64_t wyrand(uint64_t *seed){ *seed+=_wyp[0]; return _wymix(*seed,*seed^_wyp[1]);}

//convert any 64 bit pseudo random numbers to uniform distribution [0,1). It can be combined with wyrand, wyhash64 or wyhash.
static inline double wy2u01(uint64_t r){ const double _wynorm=1.0/(1ull<<52); return (r>>12)*_wynorm;}

//convert any 64 bit pseudo random numbers to APPROXIMATE Gaussian distribution. It can be combined with wyrand, wyhash64 or wyhash.
static inline double wy2gau(uint64_t r){ const double _wynorm=1.0/(1ull<<20); return ((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;}

#if(!WYHASH_32BIT_MUM)
//fast range integer random number generation on [0,k) credit to Daniel Lemire. May not work when WYHASH_32BIT_MUM=1. It can be combined with wyrand, wyhash64 or wyhash.
static inline uint64_t wy2u0k(uint64_t r, uint64_t k){ _wymum(&r,&k); return k; }
#endif

//make your own secret
static inline void make_secret(uint64_t seed, uint64_t *secret){
  uint8_t c[] = {15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60, 71, 75, 77, 78, 83, 85, 86, 89, 90, 92, 99, 101, 102, 105, 106, 108, 113, 114, 116, 120, 135, 139, 141, 142, 147, 149, 150, 153, 154, 156, 163, 165, 166, 169, 170, 172, 177, 178, 180, 184, 195, 197, 198, 201, 202, 204, 209, 210, 212, 216, 225, 226, 228, 232, 240 };
  for(size_t i=0;i<4;i++){
    uint8_t ok;
    do{
      ok=1; secret[i]=0;
      for(size_t j=0;j<64;j+=8) secret[i]|=((uint64_t)c[wyrand(&seed)%sizeof(c)])<<j;
      if(secret[i]%2==0){ ok=0; continue; }
      for(size_t j=0;j<i;j++) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
        if(__builtin_popcountll(secret[j]^secret[i])!=32){ ok=0; break; }
#elif defined(_MSC_VER) && defined(_M_X64)
        if(_mm_popcnt_u64(secret[j]^secret[i])!=32){ ok=0; break; }
#else
        //manual popcount
        uint64_t x = secret[j]^secret[i];
        x -= (x >> 1) & 0x5555555555555555;
        x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
        x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
        x = (x * 0x0101010101010101) >> 56;
        if(x!=32){ ok=0; break; }
#endif
      }
       if(!ok)continue;
       for(uint64_t j=3;j<0x100000000ull;j+=2) if(secret[i]%j==0){ ok=0; break; }
    }while(!ok);
  }
}
/*  This is world's fastest hash map: 2X~3X faster than bytell_hash_map.
    It is a probabilistic hashmap with very low error rate, please DO NOT use it in any serious tasks.
    It does not store the keys, but only the hash of keys.
    If hash(key1)==hash(key2), we are almost sure that key1==key2.
    Prob(Collision)=2^-64 * N * (N-1)/2, where N the number of objects stored. 
    For 1 million keys,   Prob(Colision)=2^-25, which is very safe
    For 16 million keys,  Prob(Colision)=2^-17, which is safe
    For 256 million keys, Prob(Colision)=2^-9, a bit worry
    For 1 billion keys,   Prob(Colision)=2^-5,  worry but not die
    For more keys, define wyhashmap128 and use double hash functions to construct 128 bit keys which is very safe
    example code:
    const  uint64_t  size=1ull<<20;	//	we use fixed memory unlike auto increasing ones. it thus maximize memory usage. A power-2 size will be fastest
    wyhashmap_t  *idx=(wyhashmap_t*)calloc(size,sizeof(wyhashmap_t));	//	allocate the index and set it to zero.
    vector<value_class>	value(size);	//	we only care about the index, user should maintain his own value vectors.
    vector<string>	keys(size);	//	also you can maintain your own real keys
    string  key="dhskfhdsj"	//	the object to be inserted into idx
    wyhashmap_t hash_of_key=wyhash(key.c_str(),key.size(),0,_wyp);	//	use double hash if wyhashmap_t is 128 bit
    uint64_t	pos=wyhashmap(idx,size,hash_of_key);	//	get the position to insert
    if(idx[pos])	value[pos]++;	//	if the key is found
    else{	idx[pos]=hash_of_key;	keys[pos]=key;	value[pos]=0; }	//	if the key is new. you may insert the key or not if it is just a lookup
    free(idx);	//	free the index
*/
#if defined(__SIZEOF_INT128__) && defined(wyhashmap128)
typedef	__uint128_t	wyhashmap_t;
#else
typedef	uint64_t	wyhashmap_t;
#endif

static  inline  uint64_t  wyhashmap(wyhashmap_t *keys,  uint64_t size, wyhashmap_t hash){
  uint64_t  i0=wy2u0k(hash,size), i;
  for(i=i0;i<size&&keys[i]&&keys[i]!=hash;i++);
  if(i<size) return  i;
  for(i=0;i<i0&&keys[i]&&keys[i]!=hash;i++);
  return i<i0?i:size;	//	return size if out of capacity
}
#endif

/* test vectors for portability test
wyhash("",0,_wyp)=42bc986dc5eec4d3
wyhash("a",1,_wyp)=84508dc903c31551
wyhash("abc",2,_wyp)=bc54887cfc9ecb1
wyhash("message digest",3,_wyp)=adc146444841c430
wyhash("abcdefghijklmnopqrstuvwxyz",4,_wyp)=9a64e42e897195b9
wyhash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",5,_wyp)=9199383239c32554
wyhash("12345678901234567890123456789012345678901234567890123456789012345678901234567890",6,_wyp)=7c1ccf6bba30f5a5
*/

/* The Unlicense
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/
