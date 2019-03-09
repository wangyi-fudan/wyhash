| key_bytes | wyhash/ns | t1ha/ns | speedup |
| ---- | ---- | ---- | ---- |
| 1 | 1.9134 | 2.5444 | 32.98% |
| 2 | 1.9451 | 2.4922 | 28.13% |
| 3 | 2.184 | 2.9889 | 36.85% |
| 4 | 1.9265 | 2.537 | 31.69% |
| 5 | 2.1751 | 2.9715 | 36.61% |
| 6 | 2.2272 | 2.8976 | 30.10% |
| 7 | 2.3586 | 3.0906 | 31.04% |
| 8 | 1.9245 | 2.531 | 31.51% |
| 9 | 2.977 | 3.0344 | 1.93% |
| 10 | 2.9098 | 3.0358 | 4.33% |
| 11 | 2.9058 | 3.5734 | 22.97% |
| 12 | 2.9957 | 3.1061 | 3.69% |
| 13 | 3.056 | 3.6361 | 18.98% |
| 14 | 3.0384 | 3.3444 | 10.07% |
| 15 | 3.1655 | 3.9832 | 25.83% |
| 16 | 2.9889 | 3.2552 | 8.91% |
| 17 | 3.6753 | 3.949 | 7.45% |
| 18 | 3.6936 | 3.953 | 7.02% |
| 19 | 3.8645 | 4.4521 | 15.21% |
| 20 | 3.7631 | 3.9717 | 5.54% |
| 21 | 3.9273 | 4.2792 | 8.96% |
| 22 | 3.906 | 4.1234 | 5.57% |
| 23 | 4.2244 | 4.5007 | 6.54% |
| 24 | 3.916 | 4.0555 | 3.56% |
| 25 | 5.5308 | 4.619 | -16.49% |
| 26 | 5.5205 | 4.6201 | -16.31% |
| 27 | 5.2732 | 5.0482 | -4.27% |
| 28 | 5.0298 | 4.6225 | -8.10% |
| 29 | 5.2393 | 4.9736 | -5.07% |
| 30 | 5.3512 | 4.9262 | -7.94% |
| 31 | 5.2337 | 5.2108 | -0.44% |


-------------------------------------------------------------------------------

--- Testing wyhash "wyhash, 64-bit"



[[[ Sanity Tests ]]]



Verification value 0xDDA7C9C3 : PASS

Running sanity check 1    ..........PASS

Running AppendedZeroesTest..........PASS



[[[ Speed Tests ]]]



Bulk speed test - 262144-byte keys

Alignment  7 -  2.329 bytes/cycle - 6664.15 MiB/sec @ 3 ghz

Alignment  6 -  2.329 bytes/cycle - 6664.21 MiB/sec @ 3 ghz

Alignment  5 -  2.329 bytes/cycle - 6664.17 MiB/sec @ 3 ghz

Alignment  4 -  2.329 bytes/cycle - 6664.10 MiB/sec @ 3 ghz

Alignment  3 -  2.329 bytes/cycle - 6664.09 MiB/sec @ 3 ghz

Alignment  2 -  2.329 bytes/cycle - 6664.07 MiB/sec @ 3 ghz

Alignment  1 -  2.329 bytes/cycle - 6664.11 MiB/sec @ 3 ghz

Alignment  0 -  2.366 bytes/cycle - 6768.98 MiB/sec @ 3 ghz

Average      -  2.334 bytes/cycle - 6677.24 MiB/sec @ 3 ghz



Small key speed test -    1-byte keys -    16.00 cycles/hash

Small key speed test -    2-byte keys -    16.00 cycles/hash

Small key speed test -    3-byte keys -    17.00 cycles/hash

Small key speed test -    4-byte keys -    16.00 cycles/hash

Small key speed test -    5-byte keys -    17.00 cycles/hash

Small key speed test -    6-byte keys -    17.00 cycles/hash

Small key speed test -    7-byte keys -    18.00 cycles/hash

Small key speed test -    8-byte keys -    23.00 cycles/hash

Small key speed test -    9-byte keys -    25.00 cycles/hash

Small key speed test -   10-byte keys -    24.96 cycles/hash

Small key speed test -   11-byte keys -    24.96 cycles/hash

Small key speed test -   12-byte keys -    24.89 cycles/hash

Small key speed test -   13-byte keys -    24.97 cycles/hash

Small key speed test -   14-byte keys -    24.99 cycles/hash

Small key speed test -   15-byte keys -    25.00 cycles/hash

Small key speed test -   16-byte keys -    24.00 cycles/hash

Small key speed test -   17-byte keys -    25.00 cycles/hash

Small key speed test -   18-byte keys -    25.00 cycles/hash

Small key speed test -   19-byte keys -    25.00 cycles/hash

Small key speed test -   20-byte keys -    25.00 cycles/hash

Small key speed test -   21-byte keys -    25.00 cycles/hash

Small key speed test -   22-byte keys -    25.00 cycles/hash

Small key speed test -   23-byte keys -    25.00 cycles/hash

Small key speed test -   24-byte keys -    25.00 cycles/hash

Small key speed test -   25-byte keys -    26.91 cycles/hash

Small key speed test -   26-byte keys -    26.86 cycles/hash

Small key speed test -   27-byte keys -    26.85 cycles/hash

Small key speed test -   28-byte keys -    26.91 cycles/hash

Small key speed test -   29-byte keys -    26.87 cycles/hash

Small key speed test -   30-byte keys -    27.00 cycles/hash

Small key speed test -   31-byte keys -    26.89 cycles/hash

Average                                    23.454 cycles/hash



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



Testing  32-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.855333%

Testing  40-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.586000%

Testing  48-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.646000%

Testing  56-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.724667%

Testing  64-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.618000%

Testing  72-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.744667%

Testing  80-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.614000%

Testing  88-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.693333%

Testing  96-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.697333%

Testing 104-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.695333%

Testing 112-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.712000%

Testing 120-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.701333%

Testing 128-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.714000%

Testing 136-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.812000%

Testing 144-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.728000%

Testing 152-bit keys ->  64-bit hashes,   300000 reps.......... worst bias is 0.719333%



[[[ Keyset 'Cyclic' Tests ]]]



Keyset 'Cyclic' - 8 cycles of 8 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   1 - 0.028%



Keyset 'Cyclic' - 8 cycles of 9 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  28 - 0.033%



Keyset 'Cyclic' - 8 cycles of 10 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  28 - 0.041%



Keyset 'Cyclic' - 8 cycles of 11 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   4 - 0.024%



Keyset 'Cyclic' - 8 cycles of 12 bytes - 10000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  40 - 0.030%





[[[ Keyset 'TwoBytes' Tests ]]]



Keyset 'TwoBytes' - up-to-4-byte keys, 652545 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  16-bit window at bit   6 - 0.095%



Keyset 'TwoBytes' - up-to-8-byte keys, 5471025 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  47 - 0.056%



Keyset 'TwoBytes' - up-to-12-byte keys, 18616785 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   6 - 0.012%



Keyset 'TwoBytes' - up-to-16-byte keys, 44251425 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  24 - 0.007%



Keyset 'TwoBytes' - up-to-20-byte keys, 86536545 total keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  21 - 0.004%





[[[ Keyset 'Sparse' Tests ]]]



Keyset 'Sparse' - 32-bit keys with up to 6 bits set - 1149017 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  17-bit window at bit  61 - 0.093%



Keyset 'Sparse' - 40-bit keys with up to 6 bits set - 4598479 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  44 - 0.049%



Keyset 'Sparse' - 48-bit keys with up to 5 bits set - 1925357 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  36 - 0.099%



Keyset 'Sparse' - 56-bit keys with up to 5 bits set - 4216423 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  57 - 0.053%



Keyset 'Sparse' - 64-bit keys with up to 5 bits set - 8303633 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  19 - 0.044%



Keyset 'Sparse' - 96-bit keys with up to 4 bits set - 3469497 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  52 - 0.052%



Keyset 'Sparse' - 256-bit keys with up to 3 bits set - 2796417 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  19-bit window at bit  19 - 0.058%



Keyset 'Sparse' - 2048-bit keys with up to 2 bits set - 2098177 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  52 - 0.083%





[[[ Keyset 'Combination Lowbits' Tests ]]]



Keyset 'Combination' - up to 8 blocks from a set of 8 - 19173960 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   2 - 0.020%





[[[ Keyset 'Combination Highbits' Tests ]]]



Keyset 'Combination' - up to 8 blocks from a set of 8 - 19173960 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  53 - 0.015%





[[[ Keyset 'Combination 0x8000000' Tests ]]]



Keyset 'Combination' - up to 20 blocks from a set of 2 - 2097150 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  25 - 0.096%





[[[ Keyset 'Combination 0x0000001' Tests ]]]



Keyset 'Combination' - up to 20 blocks from a set of 2 - 2097150 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  18-bit window at bit  58 - 0.062%





[[[ Keyset 'Combination Hi-Lo' Tests ]]]



Keyset 'Combination' - up to 6 blocks from a set of 15 - 12204240 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  47 - 0.023%





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

Testing distribution - Worst bias is the  20-bit window at bit  25 - 0.026%



Keyset 'Text' - keys of form "FooBar[XXXX]" - 14776336 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit   3 - 0.023%



Keyset 'Text' - keys of form "[XXXX]FooBar" - 14776336 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  20-bit window at bit  34 - 0.025%





[[[ Keyset 'Zeroes' Tests ]]]



Keyset 'Zeroes' - 65536 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  13-bit window at bit  40 - 0.377%





[[[ Keyset 'Seed' Tests ]]]



Keyset 'Seed' - 1000000 keys

Testing collisions   - Expected     0.00, actual     0.00 ( 0.00x)

Testing distribution - Worst bias is the  17-bit window at bit  13 - 0.153%







Input vcode 0x00000001, Output vcode 0x00000001, Result vcode 0x00000001

Verification value is 0x00000001 - Testing took 778.755481 seconds

-------------------------------------------------------------------------------
