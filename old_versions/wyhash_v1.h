/*	Author: Wang Yi <godspeed_china@yeah.net>	*/
#ifndef wyhash_version_1
#define wyhash_version_1
#include <math.h>
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#    include <intrin.h>
#    pragma intrinsic(_umul128)
#endif
const uint64_t _wyp0 = 0xa0761d6478bd642full, _wyp1 = 0xe7037ed1a0b428dbull,
               _wyp2 = 0x8ebc6af09c88c6e3ull;
const uint64_t _wyp3 = 0x589965cc75374cc3ull, _wyp4 = 0x1d8e4e27c47d124full,
               _wyp5 = 0xeb44accab455d165ull;
static inline uint64_t _wymum(uint64_t A, uint64_t B) {
#ifdef __SIZEOF_INT128__
    __uint128_t r = A;
    r *= B;
    return (r >> 64) ^ r;
#elif defined(_MSC_VER) && defined(_M_X64)
    A = _umul128(A, B, &B);
    return A ^ B;
#else
    uint64_t ha = A >> 32, hb = B >> 32, la = (uint32_t)A, lb = (uint32_t)B, hi,
             lo;
    uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb,
             t = rl + (rm0 << 32), c = t < rl;
    lo = t + (rm1 << 32);
    c += lo < t;
    hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
    return hi ^ lo;
#endif
}
static inline uint64_t _wyr08(const uint8_t *p) {
    uint8_t v;
    memcpy(&v, p, 1);
    return v;
}
static inline uint64_t _wyr16(const uint8_t *p) {
    uint16_t v;
    memcpy(&v, p, 2);
    return v;
}
static inline uint64_t _wyr32(const uint8_t *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static inline uint64_t _wyr64(const uint8_t *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static inline uint64_t __wyr64(const uint8_t *p) {
    return (_wyr32(p) << 32) | _wyr32(p + 4);
}
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed) {
    const uint8_t *p = (const uint8_t *)key;
    uint64_t i;
    for (i = 0; i + 32 <= len; i += 32, p += 32)
        seed =
            _wymum(seed ^ _wyp0,
                   _wymum(_wyr64(p) ^ _wyp1, _wyr64(p + 8) ^ _wyp2) ^
                       _wymum(_wyr64(p + 16) ^ _wyp3, _wyr64(p + 24) ^ _wyp4));
    seed ^= _wyp0;
    switch (len & 31) {
        case 1:
            seed = _wymum(seed, _wyr08(p) ^ _wyp1);
            break;
        case 2:
            seed = _wymum(seed, _wyr16(p) ^ _wyp1);
            break;
        case 3:
            seed = _wymum(seed, ((_wyr16(p) << 8) | _wyr08(p + 2)) ^ _wyp1);
            break;
        case 4:
            seed = _wymum(seed, _wyr32(p) ^ _wyp1);
            break;
        case 5:
            seed = _wymum(seed, ((_wyr32(p) << 8) | _wyr08(p + 4)) ^ _wyp1);
            break;
        case 6:
            seed = _wymum(seed, ((_wyr32(p) << 16) | _wyr16(p + 4)) ^ _wyp1);
            break;
        case 7:
            seed = _wymum(seed, ((_wyr32(p) << 24) | (_wyr16(p + 4) << 8) |
                                 _wyr08(p + 6)) ^
                                    _wyp1);
            break;
        case 8:
            seed = _wymum(seed, __wyr64(p) ^ _wyp1);
            break;
        case 9:
            seed = _wymum(__wyr64(p) ^ seed, _wyr08(p + 8) ^ _wyp2);
            break;
        case 10:
            seed = _wymum(__wyr64(p) ^ seed, _wyr16(p + 8) ^ _wyp2);
            break;
        case 11:
            seed = _wymum(__wyr64(p) ^ seed,
                          ((_wyr16(p + 8) << 8) | _wyr08(p + 8 + 2)) ^ _wyp2);
            break;
        case 12:
            seed = _wymum(__wyr64(p) ^ seed, _wyr32(p + 8) ^ _wyp2);
            break;
        case 13:
            seed = _wymum(__wyr64(p) ^ seed,
                          ((_wyr32(p + 8) << 8) | _wyr08(p + 8 + 4)) ^ _wyp2);
            break;
        case 14:
            seed = _wymum(__wyr64(p) ^ seed,
                          ((_wyr32(p + 8) << 16) | _wyr16(p + 8 + 4)) ^ _wyp2);
            break;
        case 15:
            seed = _wymum(__wyr64(p) ^ seed,
                          ((_wyr32(p + 8) << 24) | (_wyr16(p + 8 + 4) << 8) |
                           _wyr08(p + 8 + 6)) ^
                              _wyp2);
            break;
        case 16:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2);
            break;
        case 17:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed, _wyr08(p + 16) ^ _wyp3);
            break;
        case 18:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed, _wyr16(p + 16) ^ _wyp3);
            break;
        case 19:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed,
                          ((_wyr16(p + 16) << 8) | _wyr08(p + 16 + 2)) ^ _wyp3);
            break;
        case 20:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed, _wyr32(p + 16) ^ _wyp3);
            break;
        case 21:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed,
                          ((_wyr32(p + 16) << 8) | _wyr08(p + 16 + 4)) ^ _wyp3);
            break;
        case 22:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed, ((_wyr32(p + 16) << 16) | _wyr16(p + 16 + 4)) ^
                                    _wyp3);
            break;
        case 23:
            seed =
                _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                _wymum(seed, ((_wyr32(p + 16) << 24) |
                              (_wyr16(p + 16 + 4) << 8) | _wyr08(p + 16 + 6)) ^
                                 _wyp3);
            break;
        case 24:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(seed, __wyr64(p + 16) ^ _wyp3);
            break;
        case 25:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed, _wyr08(p + 24) ^ _wyp4);
            break;
        case 26:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed, _wyr16(p + 24) ^ _wyp4);
            break;
        case 27:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed,
                          ((_wyr16(p + 24) << 8) | _wyr08(p + 24 + 2)) ^ _wyp4);
            break;
        case 28:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed, _wyr32(p + 24) ^ _wyp4);
            break;
        case 29:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed,
                          ((_wyr32(p + 24) << 8) | _wyr08(p + 24 + 4)) ^ _wyp4);
            break;
        case 30:
            seed =
                _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                _wymum(__wyr64(p + 16) ^ seed,
                       ((_wyr32(p + 24) << 16) | _wyr16(p + 24 + 4)) ^ _wyp4);
            break;
        case 31:
            seed = _wymum(__wyr64(p) ^ seed, __wyr64(p + 8) ^ _wyp2) ^
                   _wymum(__wyr64(p + 16) ^ seed,
                          ((_wyr32(p + 24) << 24) | (_wyr16(p + 24 + 4) << 8) |
                           _wyr08(p + 24 + 6)) ^
                              _wyp4);
            break;
    }
    return _wymum(seed, len ^ _wyp5);
}
static inline uint64_t wyhash256(const void *key) {
    const uint8_t *p = (const uint8_t *)key;
    return _wymum(_wymum(_wyr64(p) ^ _wyp1, _wyr64(p + 8) ^ _wyp2),
                  _wymum(_wyr64(p + 16) ^ _wyp3, _wyr64(p + 24) ^ _wyp4));
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B) {
    return _wymum(_wymum(A ^ _wyp0, B ^ _wyp1), _wyp2);
}
static inline double wy2u01(uint64_t r) {
    const double _wynorm = 1.0 / (1ull << 52);
    return (r & 0x000fffffffffffffull) * _wynorm;
}
static inline float wy2gau(uint64_t r) {
    const float _wynorm1 = 1.0f / (1ull << 20);
    return ((r & 0x1fffff) + ((r >> 21) & 0x1fffff) + (r >> 43)) * _wynorm1 -
           3.0f;
}
static inline uint64_t wyrand(uint64_t *seed) {
    *seed += _wyp0;
    return _wymum(*seed ^ _wyp1, *seed);
}
static uint64_t _wyrand_seed = 0;
#define WYRAND_MAX 0xffffffffffffffffull
static inline void wysrand(uint64_t seed) { _wyrand_seed = seed; }
static inline uint64_t wyrand(void) {
    uint64_t s;
#if defined(_OPENMP)
#    pragma omp atomic capture
#endif
    {
        _wyrand_seed += _wyp0;
        s = _wyrand_seed;
    }
    return _wymum(s ^ _wyp1, s);
}
#endif
