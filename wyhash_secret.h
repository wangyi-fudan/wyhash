// This is free and unencumbered software released into the public domain under The Unlicense (http://unlicense.org/)
// main repo: https://github.com/wangyi-fudan/wyhash
// This is a helper file for wyhash that can generate whole new secret (set of unique, primal seeds).
// Can be included with `#include wyhash_secret.h`.
// Can be compiled as standalone executable with definition of `WYHASH_SECRET_TESTX` and forcing C-lang form compiler (`cc -cx`).

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wyhash.h"

#ifndef wyhash_secret_standal1
#define wyhash_secret_standal1

// Miller-Rabin primality test from https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#C
static uint64_t mul_mod(uint64_t a, uint64_t b, const uint64_t mod)
{
    uint64_t res = 0, c; // return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (c = b) >= mod - b ? c -= mod : 0, b += c);
    return res % mod;
}

static uint64_t pow_mod(uint64_t n, uint64_t exp, const uint64_t mod)
{
    uint64_t res = 1; // return (n ^ exp) % mod
    for (n %= mod; exp; exp & 1 ? res = mul_mod(res, n, mod) : 0, n = mul_mod(n, n, mod), exp >>= 1);
    return res;
}

static int is_prime_mr(uint64_t N)
{
    // Perform a Miller-Rabin test, it should be a deterministic version.
    const uint64_t n_primes = 9, primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (uint64_t i = 0; i < n_primes; ++i)
        if (N % primes[i] == 0)
            return N == primes[i];
    if (N < primes[n_primes - 1])
        return 0;
    int res = 1, s = 0;
    uint64_t t;
    for (t = N - 1; ~t & 1; t >>= 1, ++s);
    for (uint64_t i = 0; i < n_primes && res; ++i)
    {
        uint64_t B = pow_mod(primes[i], t, N);
        if (B != 1) {
            for (int b = s; b-- && (res = B + 1 != N);)
                B = mul_mod(B, B, N);
            res = !res;
        }
    }
    return res;
}

//make your own secret
static inline void make_secret(uint64_t seed, uint64_t *secret){
    uint8_t c[] = {15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60, 71, 75, 77, 78, 83, 85, 86, 89, 90, 92, 99, 101, 102, 105, 106, 108, 113, 114, 116, 120, 135, 139, 141, 142, 147, 149, 150, 153, 154, 156, 163, 165, 166, 169, 170, 172, 177, 178, 180, 184, 195, 197, 198, 201, 202, 204, 209, 210, 212, 216, 225, 226, 228, 232, 240 };
    for(size_t i=0;i<4;i++) {
        uint8_t ok;
        do {
            ok=1;
            secret[i]=0;
            for(size_t j=0;j<64;j+=8)
                secret[i]|=((uint64_t)c[wyrand(&seed)%sizeof(c)])<<j;
            if(secret[i]%2==0) {
                ok=0;
                continue;
            }
            for(size_t j=0;j<i;j++) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
                if(__builtin_popcountll(secret[j]^secret[i])!=32) {
                    ok=0;
                    break;
                }
#elif defined(_MSC_VER) && defined(_M_X64)
                if(_mm_popcnt_u64(secret[j]^secret[i])!=32){
                    ok=0;
                    break;
                }
#else
                //manual popcount
                uint64_t x = secret[j]^secret[i];
                x -= (x >> 1) & 0x5555555555555555;
                x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
                x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
                x = (x * 0x0101010101010101) >> 56;
                if(x!=32) {
                    ok=0;
                    break;
                }
#endif
            }
            if(ok)
                if(!is_prime_mr(secret[i]))
                    ok=0;
        } while(!ok);
    }
}

#ifdef WYHASH_SECRET_TESTX
int main(int argc, char* argv[])
{
    uint64_t secret5[5];
    uint64_t ix, i;
    if(argc<2)
    {
        printf("wyhash make secret with 'seed' (integer)\n"
                "usage:\n"
                "%s <number>\n", argv[0]);
        return 0;
    }
    else
    {
        ix = strtoull(argv[1], NULL, 0);
        printf("seed=%llu (0x%016llx)\n", ix, ix);
        make_secret(ix, secret5);
        printf("secret:\n");
        for(i=0; i<5; i++)
        {
            printf("0x%016llx\n", secret5[i]);
        }
    }
    return 0;
}
#endif /* WYHASH_SECRET_TESTX */

#endif /* wyhash_secret_standal1 */
