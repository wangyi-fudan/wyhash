// Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_beta
#define wyhash_version_beta
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(_umul128)
#endif
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
#define _likely_(x) __builtin_expect(x, 1)
#define _unlikely_(x) __builtin_expect(x, 0)
#else
#define _likely_(x) (x)
#define _unlikely_(x) (x)
#endif
const uint64_t _wyp[4] = {0xa0761d6478bd642full, 0xe7037ed1a0b428dbull, 0x8ebc6af09c88c6e3ull, 0x589965cc75374cc3ull};
static inline uint64_t _wyrotr(uint64_t v, unsigned k) {	return (v >> k) | (v << (64 - k));}
static inline uint64_t _wymum(uint64_t A, uint64_t B) {
#ifdef UNOFFICIAL_WYHASH_32BIT
	uint64_t hh = (A >> 32) * (B >> 32), hl = (A >> 32) * (unsigned)B, lh = (unsigned)A * (B >> 32), ll = (uint64_t)(unsigned)A * (unsigned)B;
	return _wyrotr(hl, 32) ^ _wyrotr(lh, 32) ^ hh ^ ll;
#else
#ifdef __SIZEOF_INT128__
	__uint128_t r = A;
	r *= B;
	return (r >> 64) ^ r;
#elif defined(_MSC_VER) && defined(_M_X64)
	A = _umul128(A, B, &B);
	return A ^ B;
#else
	uint64_t ha = A >> 32, hb = B >> 32, la = (uint32_t)A, lb = (uint32_t)B, hi, lo;
	uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb, t = rl + (rm0 << 32), c = t < rl;
	lo = t + (rm1 << 32);	c += lo < t;	hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
	return hi ^ lo;
#endif
#endif
}
static inline void _wymix(uint64_t A, uint64_t B,	uint64_t	*C,	uint64_t	*D) {
	A^=*C;	B^=*D;
#ifdef UNOFFICIAL_WYHASH_32BIT
	uint64_t hh = (A >> 32) * (B >> 32), hl = (A >> 32) * (unsigned)B, lh = (unsigned)A * (B >> 32), ll = (uint64_t)(unsigned)A * (unsigned)B;
#ifdef	UNOFFICIAL_WYHASH_CONDOM
	*C^=_wyrotr(hl, 32) ^ hh;	*D^=_wyrotr(lh, 32) ^ ll;
#else
	*C=_wyrotr(hl, 32) ^ hh;	*D=_wyrotr(lh, 32) ^ ll;
#endif
#else
#ifdef __SIZEOF_INT128__
	__uint128_t r = A;	r *= B;
#ifdef	UNOFFICIAL_WYHASH_CONDOM
	*C^=(uint64_t)(r>>64);	*D^=(uint64_t)r;
#else
	*C=(uint64_t)(r>>64);	*D=(uint64_t)r;
#endif
#elif defined(_MSC_VER) && defined(_M_X64)
	A = _umul128(A, B, &B);	
#ifdef	UNOFFICIAL_WYHASH_CONDOM
	*C^=A;	*D^=B;
#else
	*C=A;	*D=B;
#endif
#else
	uint64_t ha = A >> 32, hb = B >> 32, la = (uint32_t)A, lb = (uint32_t)B, hi, lo;
	uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb, t = rl + (rm0 << 32), c = t < rl;
	lo = t + (rm1 << 32);	c += lo < t;	hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
#ifdef	UNOFFICIAL_WYHASH_CONDOM
	*C^= hi;	*D^= lo;
#else
	*C= hi;	*D= lo;
#endif
#endif
#endif
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B) {	return _wymum(_wymum(A ^ *_wyp, B ^ _wyp[1]), *_wyp);}
static inline uint64_t wyrand(uint64_t *seed) {	*seed += *_wyp;	return _wymum(*seed ^ _wyp[1], *seed);}
static inline double wy2u01(uint64_t r) {	const double _wynorm = 1.0 / (1ull << 52);	return (r >> 11) * _wynorm;}
static inline double wy2gau(uint64_t r) {	const double _wynorm = 1.0 / (1ull << 20);	return ((r & 0x1fffff) + ((r >> 21) & 0x1fffff) + ((r >> 42) & 0x1fffff)) * _wynorm - 3.0;}
#ifndef WYHASH_LITTLE_ENDIAN
#if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 0
#endif
#endif
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(const uint8_t *p) {	uint64_t v;	memcpy(&v, p, 8);	return v^0x5555555555555555ull;}
static inline uint64_t _wyr4(const uint8_t *p) {	unsigned v;	memcpy(&v, p, 4);	return v^0x5555555555555555ull;}
#else
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) {	uint64_t v;	memcpy(&v, p, 8);	return __builtin_bswap64(v)^0x5555555555555555ull;}
static inline uint64_t _wyr4(const uint8_t *p) {	unsigned v;	memcpy(&v, p, 4);	return __builtin_bswap32(v)^0x5555555555555555ull;}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) {	uint64_t v;	memcpy(&v, p, 8);	return _byteswap_uint64(v)^0x5555555555555555ull;}
static inline uint64_t _wyr4(const uint8_t *p) {	unsigned v;	memcpy(&v, p, 4);	return _byteswap_ulong(v)^0x5555555555555555ull;}
#endif
#endif
static inline uint64_t _wyr3(const uint8_t *p, unsigned k) {	return ((((uint64_t)p[0]) << 16) | (((uint64_t)p[k >> 1]) << 8) | p[k - 1])^0x5555555555555555ull;}
static inline uint64_t FastestHash(const void *key, size_t len, uint64_t seed) {
	const uint8_t *p = (const uint8_t *)key;
	return _likely_(len >= 4) ? (_wyr4(p) + _wyr4(p + len - 4)) * (_wyr4(p + (len >> 1) - 2) ^ seed) : (_likely_(len) ? _wyr3(p, len) * (*_wyp ^ seed) : seed);
}
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed, const uint64_t secret[4]) {
	const uint8_t *p = (const uint8_t *)key;	uint64_t i = len,	see1=seed^*secret,	see2=seed^secret[1],	see3=seed^secret[2];	seed^=secret[3];
	start:
	if(_likely_(i<=32)) {
		if(_likely_(i<=8)) {
			if(_likely_(i>=4))  _wymix(_wyr4(p), _wyr4(p+i-4),&seed,&see1);
			else if (_likely_(i))  _wymix(_wyr3(p, i), secret[3],&seed,&see1);
			else  _wymix(secret[1], secret[2],&seed,&see1);
		} 
		else if(_likely_(i<=16)) _wymix(_wyr8(p), _wyr8(p+i-8),&seed,&see1);
		else {	_wymix(_wyr8(p), _wyr8(p+8),&seed,&see1);	_wymix(_wyr8(p+i-16), _wyr8(p+i-8),&see2,&see3);	}
		return _wymum(seed^see2^len,see1^see3^len);
	} 
	else {	_wymix(_wyr8(p), _wyr8(p+8),&seed,&see1);	_wymix(_wyr8(p+16), _wyr8(p+24),&see2,&see3);	i-=32;	p+=32;	goto start;	}
}
#endif
