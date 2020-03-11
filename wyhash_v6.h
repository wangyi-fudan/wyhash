// Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_6
#define wyhash_version_6
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#    include <intrin.h>
#    pragma intrinsic(_umul128)
#elif defined(__GNUC__) && defined(__SSE2__)
#    include <x86intrin.h>
#endif
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
#    define _likely_(x) __builtin_expect(x, 1)
#else
#    define _likely_(x) (x)
#endif
const uint64_t _wyp[10] = {0xb10f1ea5b4358d87ull, 0x2e63952eb46a7127ull,
                           0xd88be12db28d1769ull, 0xb8d2a6b2d21e6c55ull,
                           0xe43ad88ed1c9ac1bull, 0xe4a33a5336a35a1dull,
                           0xe85aca652dd266a5ull, 0x2e1d72638e6c2e4bull,
                           0x8ba6d4726c8db48dull, 0x935a749a3ae2478bull};
static inline uint64_t _wyrotr(uint64_t v, unsigned k) {
    return (v >> k) | (v << (64 - k));
}
static inline uint64_t _wymum(uint64_t A, uint64_t B) {
#ifdef UNOFFICIAL_WYHASH_32BIT  //	fast on 32 bit system
    uint64_t hh = (A >> 32) * (B >> 32), hl = (A >> 32) * (unsigned)B,
             lh = (unsigned)A * (B >> 32),
             ll = (uint64_t)(unsigned)A * (unsigned)B;
    return _wyrotr(hl, 32) ^ _wyrotr(lh, 32) ^ hh ^ ll;
#else
#    ifdef __SIZEOF_INT128__
    __uint128_t r = A;
    r *= B;
    return (r >> 64) ^ r;
#    elif defined(_MSC_VER) && defined(_M_X64)
    A = _umul128(A, B, &B);
    return A ^ B;
#    else
    uint64_t ha = A >> 32, hb = B >> 32, la = (uint32_t)A, lb = (uint32_t)B, hi,
             lo;
    uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb,
             t = rl + (rm0 << 32), c = t < rl;
    lo = t + (rm1 << 32);
    c += lo < t;
    hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
    return hi ^ lo;
#    endif
#endif
}
static inline uint64_t _wymix(uint64_t A, uint64_t B) {
    return (A ^ B) ^ _wymum(A, B);
}
static inline uint64_t _wymix32(uint64_t A) {
    return A ^ ((A >> 32) * (uint32_t)A);
}
static inline uint64_t wyhash64(uint64_t A, uint64_t B) {
    return _wymum(_wymum(A ^ _wyp[0], B ^ _wyp[1]), _wyp[2]);
}
static inline uint64_t wyrand(uint64_t *seed) {
    *seed += _wyp[0];
    return _wymum(*seed ^ _wyp[1], *seed);
}
static inline double wy2u01(uint64_t r) {
    const double _wynorm = 1.0 / (1ull << 52);
    return (r >> 11) * _wynorm;
}
static inline double wy2gau(uint64_t r) {
    const double _wynorm = 1.0 / (1ull << 20);
    return ((r & 0x1fffff) + ((r >> 21) & 0x1fffff) + ((r >> 42) & 0x1fffff)) *
               _wynorm -
           3.0;
}
#ifndef WYHASH_LITTLE_ENDIAN
#    if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || \
        (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#        define WYHASH_LITTLE_ENDIAN 1
#    elif defined(__BIG_ENDIAN__) || \
        (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#        define WYHASH_LITTLE_ENDIAN 0
#    endif
#endif
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(const uint8_t *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static inline uint64_t _wyr4(const uint8_t *p) {
    unsigned v;
    memcpy(&v, p, 4);
    return v;
}
#else
#    if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return __builtin_bswap64(v);
}
static inline uint64_t _wyr4(const uint8_t *p) {
    unsigned v;
    memcpy(&v, p, 4);
    return __builtin_bswap32(v);
}
#    elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return _byteswap_uint64(v);
}
static inline uint64_t _wyr4(const uint8_t *p) {
    unsigned v;
    memcpy(&v, p, 4);
    return _byteswap_ulong(v);
}
#    endif
#endif
static inline uint64_t _wyr3(const uint8_t *p, unsigned k) {
    return (((uint64_t)p[0]) << 16) | (((uint64_t)p[k >> 1]) << 8) | p[k - 1];
}
static inline uint64_t FastestHash(const void *key, size_t len, uint64_t seed) {
    const uint8_t *p = (const uint8_t *)key;
    return _likely_(len >= 4)
               ? (_wyr4(p) + _wyr4(p + len - 4)) *
                     (_wyr4(p + (len >> 1) - 2) ^ seed)
               : (_likely_(len) ? _wyr3(p, len) * (_wyp[0] ^ seed) : seed);
}

static inline uint64_t _wyhash(const void *key, uint64_t len, uint64_t seed,
                               const uint64_t secret[10]) {
    const uint8_t *p = (const uint8_t *)key;
    uint64_t i = len;
    seed ^= secret[8];
    if (_likely_(i <= 128)) {
    finalization:
        if (_likely_(i >= 8)) {
            if (_likely_(i <= 16))
                return _wymix(_wyr8(p) ^ secret[0], _wyr8(p + i - 8) ^ seed);
            else {
                seed = _wymix(_wyr8(p) ^ secret[0], _wyr8(p + 8) ^ seed);
                i -= 16;
                p += 16;
                goto finalization;
            }
        } else if (_likely_(i >= 4))
            return _wymix(_wyr4(p) ^ secret[0], _wyr4(p + i - 4) ^ seed);
        else if (_likely_(i))
            return _wymix(_wyr3(p, i) ^ secret[0], seed);
        else
            return _wymum(secret[0], seed);
    }
#if defined(__AVX2__)
    __m256i se[4] =
        {{(int64_t)seed, (int64_t)seed, (int64_t)seed, (int64_t)seed},
         {(int64_t)seed, (int64_t)seed, (int64_t)seed, (int64_t)seed},
         {(int64_t)seed, (int64_t)seed, (int64_t)seed, (int64_t)seed},
         {(int64_t)seed, (int64_t)seed, (int64_t)seed, (int64_t)seed}},
            ma[4] = {{(int64_t)secret[0] ^ (int64_t)secret[4],
                      (int64_t)secret[0] ^ (int64_t)secret[5],
                      (int64_t)secret[0] ^ (int64_t)secret[6],
                      (int64_t)secret[0] ^ (int64_t)secret[7]},
                     {(int64_t)secret[1] ^ (int64_t)secret[4],
                      (int64_t)secret[1] ^ (int64_t)secret[5],
                      (int64_t)secret[1] ^ (int64_t)secret[6],
                      (int64_t)secret[1] ^ (int64_t)secret[7]},
                     {(int64_t)secret[2] ^ (int64_t)secret[4],
                      (int64_t)secret[2] ^ (int64_t)secret[5],
                      (int64_t)secret[2] ^ (int64_t)secret[6],
                      (int64_t)secret[2] ^ (int64_t)secret[7]},
                     {(int64_t)secret[3] ^ (int64_t)secret[4],
                      (int64_t)secret[3] ^ (int64_t)secret[5],
                      (int64_t)secret[3] ^ (int64_t)secret[6],
                      (int64_t)secret[3] ^ (int64_t)secret[7]}};
    for (; i > 128; i -= 128, p += 128) {
        __m256i d[4] = {_mm256_loadu_si256((__m256i *)p),
                        _mm256_loadu_si256((__m256i *)(p + 32)),
                        _mm256_loadu_si256((__m256i *)(p + 64)),
                        _mm256_loadu_si256((__m256i *)(p + 96))};
        for (size_t j = 0; j < 4; j++) {
            se[j] = _mm256_xor_si256(_mm256_xor_si256(ma[j], d[j]), se[j]);
            se[j] = _mm256_xor_si256(
                se[j],
                _mm256_mul_epu32(se[j], _mm256_shuffle_epi32(se[j], 0x31)));
        }
    }
    for (size_t j = 0; j < 4; j++) {
        uint64_t *s = (uint64_t *)&se[j];
        seed ^= s[0] ^ s[1] ^ s[2] ^ s[3];
    }
#elif defined(__SSE2__)
    __m128i se[8] = {{(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed},
                     {(int64_t)seed, (int64_t)seed}},
            ma[8] = {{(int64_t)secret[0] ^ (int64_t)secret[4],
                      (int64_t)secret[0] ^ (int64_t)secret[5]},
                     {(int64_t)secret[0] ^ (int64_t)secret[6],
                      (int64_t)secret[0] ^ (int64_t)secret[7]},
                     {(int64_t)secret[1] ^ (int64_t)secret[4],
                      (int64_t)secret[1] ^ (int64_t)secret[5]},
                     {(int64_t)secret[1] ^ (int64_t)secret[6],
                      (int64_t)secret[1] ^ (int64_t)secret[7]},
                     {(int64_t)secret[2] ^ (int64_t)secret[4],
                      (int64_t)secret[2] ^ (int64_t)secret[5]},
                     {(int64_t)secret[2] ^ (int64_t)secret[6],
                      (int64_t)secret[2] ^ (int64_t)secret[7]},
                     {(int64_t)secret[3] ^ (int64_t)secret[4],
                      (int64_t)secret[3] ^ (int64_t)secret[5]},
                     {(int64_t)secret[3] ^ (int64_t)secret[6],
                      (int64_t)secret[3] ^ (int64_t)secret[7]}};
    for (; i > 128; i -= 128, p += 128) {
        __m128i d[8] = {_mm_loadu_si128((__m128i *)p),
                        _mm_loadu_si128((__m128i *)(p + 16)),
                        _mm_loadu_si128((__m128i *)(p + 32)),
                        _mm_loadu_si128((__m128i *)(p + 48)),
                        _mm_loadu_si128((__m128i *)(p + 64)),
                        _mm_loadu_si128((__m128i *)(p + 80)),
                        _mm_loadu_si128((__m128i *)(p + 96)),
                        _mm_loadu_si128((__m128i *)(p + 112))};
        for (size_t j = 0; j < 8; j++) {
            se[j] = _mm_xor_si128(_mm_xor_si128(ma[j], d[j]), se[j]);
            se[j] = _mm_xor_si128(
                se[j], _mm_mul_epu32(se[j], _mm_shuffle_epi32(se[j], 0x31)));
        }
    }
    for (size_t j = 0; j < 8; j++) {
        uint64_t *s = (uint64_t *)&se[j];
        seed ^= s[0] ^ s[1];
    }
#else
    uint64_t se[4][4] = {{seed, seed, seed, seed},
                         {seed, seed, seed, seed},
                         {seed, seed, seed, seed},
                         {seed, seed, seed, seed}};
    uint64_t ma[4][4] = {{secret[0] ^ secret[4], secret[0] ^ secret[5],
                          secret[0] ^ secret[6], secret[0] ^ secret[7]},
                         {secret[1] ^ secret[4], secret[1] ^ secret[5],
                          secret[1] ^ secret[6], secret[1] ^ secret[7]},
                         {secret[2] ^ secret[4], secret[2] ^ secret[5],
                          secret[2] ^ secret[6], secret[2] ^ secret[7]},
                         {secret[3] ^ secret[4], secret[3] ^ secret[5],
                          secret[3] ^ secret[6], secret[3] ^ secret[7]}};
    for (; i > 128; i -= 128, p += 128)
        for (size_t j = 0; j < 4; j++)
            for (size_t k = 0; k < 4; k++)
                se[j][k] =
                    _wymix32(_wyr8(p + (j * 4 + k) * 8) ^ se[j][k] ^ ma[j][k]);
    for (size_t j = 0; j < 4; j++)
        for (size_t k = 0; k < 4; k++) seed ^= se[j][k];
#endif
    goto finalization;
}
static inline uint64_t wyhash(const void *key, uint64_t len, uint64_t seed,
                              const uint64_t secret[10]) {
    uint64_t h = _wyhash(key, len, seed, secret);
    return _wymum(h ^ len, h ^ secret[9]);
}

static inline void make_secret(uint64_t seed, uint64_t secret[10]) {
    uint8_t c[] = {15,  23,  27,  29,  30,  39,  43,  45,  46,  51,  53,  54,
                   57,  58,  60,  71,  75,  77,  78,  83,  85,  86,  89,  90,
                   92,  99,  101, 102, 105, 106, 108, 113, 114, 116, 120, 135,
                   139, 141, 142, 147, 149, 150, 153, 154, 156, 163, 165, 166,
                   169, 170, 172, 177, 178, 180, 184, 195, 197, 198, 201, 202,
                   204, 209, 210, 212, 216, 225, 226, 228, 232, 240};
    for (size_t i = 0; i < 10; i++) {
        uint8_t ok;
        do {
            ok = 1;
            secret[i] = 0;
            for (size_t j = 0; j < 64; j += 8)
                secret[i] |= ((uint64_t)c[wyrand(&seed) % sizeof(c)]) << j;
            if (secret[i] % 2 == 0) {
                ok = 0;
                continue;
            }
            for (size_t j = 0; j < i; j++)
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
                if (__builtin_popcountll(secret[i] ^ secret[j]) != 32) {
                    ok = 0;
                    break;
                }
#elif defined(_MSC_VER)
                if (_mm_popcnt_u64(secret[i] ^ secret[j]) != 32) {
                    ok = 0;
                    break;
                }
#endif
            if (!ok) continue;
            for (uint64_t j = 3; j < 0x100000000ull; j += 2)
                if (secret[i] % j == 0) {
                    ok = 0;
                    break;
                }
        } while (!ok);
    }
}
#endif
