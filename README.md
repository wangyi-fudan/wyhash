Build by GNU C/C++ compiler 7.3 (self-check passed)

Testing t1ha2_atonce... Ok

Testing t1ha2_atonce128... Ok

Testing t1ha2_stream... Ok

Testing t1ha2_stream128... Ok

Testing t1ha1_64le... Ok

Testing t1ha1_64be... Ok

Testing t1ha0_32le... Ok

Testing t1ha0_32be... Ok

Testing t1ha0_ia32aes_noavx... Ok

Testing t1ha0_ia32aes_avx... Ok

Testing t1ha0_ia32aes_avx2... Ok

Testing wyhash... Ok

Testing HighwayHash64_portable_cxx... Ok

Testing HighwayHash64_sse41... Ok

Testing HighwayHash64_avx2... Ok

Testing StadtX... Ok



Preparing to benchmarking...

 - suggest enable rdpmc for usermode (echo 2 | sudo tee /sys/devices/cpu/rdpmc)

 - suggest enable perf for non-admin users (echo 2 | sudo tee /proc/sys/kernel/perf_event_paranoid)

 - running on CPU#1

 - use RDTSCP as clock source for benchmarking

 - assume it cheap and floating (RESULTS MAY VARY AND BE USELESS)

 - measure granularity and overhead: 36 cycles, 0.0277778 iteration/cycle



Bench for tiny keys (7 bytes):

t1ha2_atonce            :     12.078 cycle/hash,  1.725 cycle/byte,  0.580 byte/cycle,  1.739 GB/s @3.0GHz roughly

t1ha2_atonce128*        :     24.188 cycle/hash,  3.455 cycle/byte,  0.289 byte/cycle,  0.868 GB/s @3.0GHz roughly

t1ha2_stream*           :     57.000 cycle/hash,  8.143 cycle/byte,  0.123 byte/cycle,  0.368 GB/s @3.0GHz roughly

t1ha2_stream128*        :     72.250 cycle/hash, 10.321 cycle/byte,  0.097 byte/cycle,  0.291 GB/s @3.0GHz roughly

t1ha1_64le              :     12.797 cycle/hash,  1.828 cycle/byte,  0.547 byte/cycle,  1.641 GB/s @3.0GHz roughly

t1ha0                   :     11.344 cycle/hash,  1.621 cycle/byte,  0.617 byte/cycle,  1.851 GB/s @3.0GHz roughly

xxhash32                :     13.172 cycle/hash,  1.882 cycle/byte,  0.531 byte/cycle,  1.594 GB/s @3.0GHz roughly

xxhash64                :     17.875 cycle/hash,  2.554 cycle/byte,  0.392 byte/cycle,  1.175 GB/s @3.0GHz roughly

StadtX                  :     13.500 cycle/hash,  1.929 cycle/byte,  0.519 byte/cycle,  1.556 GB/s @3.0GHz roughly

wyhash                  :     10.734 cycle/hash,  1.533 cycle/byte,  0.652 byte/cycle,  1.956 GB/s @3.0GHz roughly

HighwayHash64_portable  :    345.500 cycle/hash, 49.357 cycle/byte,  0.020 byte/cycle,  0.061 GB/s @3.0GHz roughly

HighwayHash64_sse41     :     48.250 cycle/hash,  6.893 cycle/byte,  0.145 byte/cycle,  0.435 GB/s @3.0GHz roughly

HighwayHash64_avx2      :     40.500 cycle/hash,  5.786 cycle/byte,  0.173 byte/cycle,  0.519 GB/s @3.0GHz roughly



Bench for large keys (16384 bytes):

t1ha2_atonce            :   2530.000 cycle/hash,  0.154 cycle/byte,  6.476 byte/cycle, 19.428 GB/s @3.0GHz roughly

t1ha2_atonce128*        :   2528.000 cycle/hash,  0.154 cycle/byte,  6.481 byte/cycle, 19.443 GB/s @3.0GHz roughly

t1ha2_stream*           :   2640.000 cycle/hash,  0.161 cycle/byte,  6.206 byte/cycle, 18.618 GB/s @3.0GHz roughly

t1ha2_stream128*        :   2648.000 cycle/hash,  0.162 cycle/byte,  6.187 byte/cycle, 18.562 GB/s @3.0GHz roughly

t1ha1_64le              :   2508.000 cycle/hash,  0.153 cycle/byte,  6.533 byte/cycle, 19.598 GB/s @3.0GHz roughly

t1ha0                   :    918.000 cycle/hash,  0.056 cycle/byte, 17.847 byte/cycle, 53.542 GB/s @3.0GHz roughly

xxhash32                :   5800.000 cycle/hash,  0.354 cycle/byte,  2.825 byte/cycle,  8.474 GB/s @3.0GHz roughly

xxhash64                :   2918.000 cycle/hash,  0.178 cycle/byte,  5.615 byte/cycle, 16.844 GB/s @3.0GHz roughly

StadtX                  :   2630.000 cycle/hash,  0.161 cycle/byte,  6.230 byte/cycle, 18.689 GB/s @3.0GHz roughly

wyhash                  :   8696.000 cycle/hash,  0.531 cycle/byte,  1.884 byte/cycle,  5.652 GB/s @3.0GHz roughly

HighwayHash64_portable  :  30654.000 cycle/hash,  1.871 cycle/byte,  0.534 byte/cycle,  1.603 GB/s @3.0GHz roughly

HighwayHash64_sse41     :   4526.000 cycle/hash,  0.276 cycle/byte,  3.620 byte/cycle, 10.860 GB/s @3.0GHz roughly

HighwayHash64_avx2      :   3156.000 cycle/hash,  0.193 cycle/byte,  5.191 byte/cycle, 15.574 GB/s @3.0GHz roughly



-------------------------------------------------------------------------------

--- Testing wyhash "wyhash (portable, aims 64-bit, little-endian)"



[[[ Sanity Tests ]]]



Verification value 0x7BBCE1EB : PASS

Running sanity check 1    ..........PASS

Running AppendedZeroesTest..........PASS



[[[ Speed Tests ]]]



Bulk speed test - 262144-byte keys

Alignment  7 -  1.858 bytes/cycle - 5317.13 MiB/sec @ 3 ghz

Alignment  6 -  1.858 bytes/cycle - 5317.12 MiB/sec @ 3 ghz

Alignment  5 -  1.858 bytes/cycle - 5317.12 MiB/sec @ 3 ghz

Alignment  4 -  1.859 bytes/cycle - 5317.30 MiB/sec @ 3 ghz

Alignment  3 -  1.859 bytes/cycle - 5317.32 MiB/sec @ 3 ghz

Alignment  2 -  1.821 bytes/cycle - 5209.08 MiB/sec @ 3 ghz

Alignment  1 -  1.804 bytes/cycle - 5160.90 MiB/sec @ 3 ghz

Alignment  0 -  1.814 bytes/cycle - 5188.78 MiB/sec @ 3 ghz

Average      -  1.841 bytes/cycle - 5268.09 MiB/sec @ 3 ghz



Small key speed test -    1-byte keys -    16.55 cycles/hash

Small key speed test -    2-byte keys -    16.51 cycles/hash

Small key speed test -    3-byte keys -    17.00 cycles/hash

Small key speed test -    4-byte keys -    16.00 cycles/hash

Small key speed test -    5-byte keys -    17.00 cycles/hash

Small key speed test -    6-byte keys -    17.00 cycles/hash

Small key speed test -    7-byte keys -    18.00 cycles/hash

Small key speed test -    8-byte keys -    23.00 cycles/hash

Small key speed test -    9-byte keys -    27.00 cycles/hash

Small key speed test -   10-byte keys -    27.00 cycles/hash

Small key speed test -   11-byte keys -    27.00 cycles/hash

Small key speed test -   12-byte keys -    27.00 cycles/hash

Small key speed test -   13-byte keys -    27.00 cycles/hash

Small key speed test -   14-byte keys -    27.00 cycles/hash

Small key speed test -   15-byte keys -    27.00 cycles/hash

Small key speed test -   16-byte keys -    27.00 cycles/hash

Small key speed test -   17-byte keys -    31.00 cycles/hash

Small key speed test -   18-byte keys -    31.51 cycles/hash

Small key speed test -   19-byte keys -    31.28 cycles/hash

Small key speed test -   20-byte keys -    31.42 cycles/hash

Small key speed test -   21-byte keys -    31.24 cycles/hash

Small key speed test -   22-byte keys -    31.75 cycles/hash

Small key speed test -   23-byte keys -    31.27 cycles/hash

Small key speed test -   24-byte keys -    31.00 cycles/hash

Small key speed test -   25-byte keys -    36.00 cycles/hash

Small key speed test -   26-byte keys -    36.00 cycles/hash

Small key speed test -   27-byte keys -    36.00 cycles/hash

Small key speed test -   28-byte keys -    36.00 cycles/hash

Small key speed test -   29-byte keys -    36.00 cycles/hash

Small key speed test -   30-byte keys -    36.00 cycles/hash

Small key speed test -   31-byte keys -    36.00 cycles/hash

Average                                    27.726 cycles/hash



[[[ Differential Tests ]]]



Testing 8303632 up-to-5-bit differentials in 64-bit keys -> 64 bit hashes.

1000 reps, 8303632000 total tests, expecting 0.00 random collisions..........

0 total collisions, of which 0 single collisions were ignored



Testing 11017632 up-to-4-bit differentials in 128-bit keys -> 64 bit hashes.

1000 reps, 11017632000 total tests, expecting 0.00 random collisions..........

0 total collisions, of which 0 single collisions were ignored



Testing 2796416 up-to-3-bit differentials in 256-bit keys -> 64 bit hashes.

1000 reps, 2796416000 total tests, expecting 0.00 random collisions..........

0 total collisions, of which 0 single collisions were ignored





[[[ Avalanche Tests ]]]



Testing  32-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.711333%

Testing  40-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.636667%

Testing  48-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.643333%

Testing  56-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.673333%

Testing  64-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.654667%

Testing  72-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.691333%

Testing  80-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.626667%

Testing  88-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.709333%

Testing  96-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.627333%

Testing 104-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.734667%

Testing 112-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.627333%

Testing 120-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.696667%

Testing 128-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.768667%

Testing 136-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.668667%

Testing 144-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.642667%

Testing 152-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.645333%



[[[ Keyset 'Cyclic' Tests ]]]



Keyset 'Cyclic' - 8 cycles of 8 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  38 - 0.054%



Keyset 'Cyclic' - 8 cycles of 9 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  59 - 0.032%



Keyset 'Cyclic' - 8 cycles of 10 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  55 - 0.029%



Keyset 'Cyclic' - 8 cycles of 11 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  39 - 0.036%



Keyset 'Cyclic' - 8 cycles of 12 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  10 - 0.039%





[[[ Keyset 'TwoBytes' Tests ]]]



Keyset 'TwoBytes' - up-to-4-byte keys, 652545 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  16-bit window at bit   0 - 0.120%



Keyset 'TwoBytes' - up-to-8-byte keys, 5471025 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  39 - 0.052%



Keyset 'TwoBytes' - up-to-12-byte keys, 18616785 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   2 - 0.019%



Keyset 'TwoBytes' - up-to-16-byte keys, 44251425 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   9 - 0.008%



Keyset 'TwoBytes' - up-to-20-byte keys, 86536545 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  25 - 0.003%





[[[ Keyset 'Sparse' Tests ]]]



Keyset 'Sparse' - 32-bit keys with up to 6 bits set - 1149017 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  17-bit window at bit  37 - 0.081%



Keyset 'Sparse' - 40-bit keys with up to 6 bits set - 4598479 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  42 - 0.045%



Keyset 'Sparse' - 48-bit keys with up to 5 bits set - 1925357 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  22 - 0.099%



Keyset 'Sparse' - 56-bit keys with up to 5 bits set - 4216423 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  20 - 0.061%



Keyset 'Sparse' - 64-bit keys with up to 5 bits set - 8303633 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit   8 - 0.039%



Keyset 'Sparse' - 96-bit keys with up to 4 bits set - 3469497 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  16 - 0.043%



Keyset 'Sparse' - 256-bit keys with up to 3 bits set - 2796417 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  32 - 0.123%



Keyset 'Sparse' - 2048-bit keys with up to 2 bits set - 2098177 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  20 - 0.075%





[[[ Keyset 'Combination Lowbits' Tests ]]]



Keyset 'Combination' - up to 8 blocks from a set of 8 - 19173960 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  35 - 0.013%





[[[ Keyset 'Combination Highbits' Tests ]]]



Keyset 'Combination' - up to 8 blocks from a set of 8 - 19173960 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   8 - 0.019%





[[[ Keyset 'Combination 0x8000000' Tests ]]]



Keyset 'Combination' - up to 20 blocks from a set of 2 - 2097150 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  36 - 0.093%





[[[ Keyset 'Combination 0x0000001' Tests ]]]



Keyset 'Combination' - up to 20 blocks from a set of 2 - 2097150 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit   8 - 0.069%





[[[ Keyset 'Combination Hi-Lo' Tests ]]]



Keyset 'Combination' - up to 6 blocks from a set of 15 - 12204240 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   2 - 0.037%





[[[ Keyset 'Window' Tests ]]]



Keyset 'Windowed' - 128-bit key,  20-bit window - 128 tests, 1048576 keys per test

Window at   0 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   1 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   2 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   3 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   4 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   5 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   6 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   7 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   8 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at   9 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  10 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  11 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  12 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  13 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  14 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  15 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  16 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  17 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  18 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  19 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  20 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  21 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  22 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  23 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  24 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  25 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  26 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  27 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  28 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  29 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  30 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  31 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  32 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  33 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  34 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  35 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  36 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  37 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  38 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  39 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  40 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  41 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  42 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  43 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  44 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  45 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  46 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  47 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  48 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  49 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  50 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  51 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  52 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  53 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  54 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  55 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  56 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  57 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  58 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  59 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  60 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  61 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  62 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  63 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  64 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  65 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  66 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  67 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  68 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  69 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  70 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  71 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  72 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  73 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  74 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  75 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  76 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  77 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  78 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  79 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  80 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  81 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  82 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  83 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  84 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  85 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  86 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  87 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  88 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  89 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  90 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  91 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  92 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  93 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  94 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  95 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  96 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  97 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  98 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at  99 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 100 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 101 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 102 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 103 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 104 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 105 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 106 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 107 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 108 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 109 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 110 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 111 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 112 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 113 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 114 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 115 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 116 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 117 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 118 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 119 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 120 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 121 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 122 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 123 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 124 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 125 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 126 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 127 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Window at 128 - Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)



[[[ Keyset 'Text' Tests ]]]



Keyset 'Text' - keys of form "Foo[XXXX]Bar" - 14776336 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  19 - 0.024%



Keyset 'Text' - keys of form "FooBar[XXXX]" - 14776336 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  63 - 0.023%



Keyset 'Text' - keys of form "[XXXX]FooBar" - 14776336 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  10 - 0.020%





[[[ Keyset 'Zeroes' Tests ]]]



Keyset 'Zeroes' - 65536 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  13-bit window at bit  18 - 0.337%





[[[ Keyset 'Seed' Tests ]]]



Keyset 'Seed' - 1000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  17-bit window at bit  21 - 0.089%







Input vcode 0x00000001, Output vcode 0x00000001, Result vcode 0x00000001

Verification value is 0x00000001 - Testing took 755.187224 seconds

-------------------------------------------------------------------------------
