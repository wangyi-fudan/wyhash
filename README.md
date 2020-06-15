No hash function is perfect, but some are useful.
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Efficient on 64-bit machines, especially for short keys.
  
**simplest**: In the sense of code size.

----------------------------------------

g++-9 benchmark.cpp t1ha/src/t1ha2.c -o benchmark -Ofast -s  -Wall -march=native

/usr/share/dict/words

|hash function  |short hash/us  |bulk_256B GB/s |bulk_64KB GB/s |
|----           |----           |----           |----           |
|wyhash:safety=0|444.31         |18.86          |24.35          |
|wyhash:safety=1|195.42         |17.97          |23.44          |
|wyhash:safety=2|181.56         |14.33          |15.97          |
|xxh3:avx2      |147.33         |9.73           |45.39          |
|xxh3:sse2      |154.30         |11.53          |27.15          |
|xxh3:scalar    |153.61         |8.49           |13.05          |
|xxHash64       |83.10          |10.89          |14.72          |
|t1ha2_atonce   |115.12         |12.96          |17.64          |

----------------------------------------
wyhash is the default hasher for a hash table of the great Zig and V language.

**C#**  https://github.com/cocowalla/wyhash-dotnet

**C++**  https://github.com/tommyettinger/waterhash

**GO**  https://github.com/dgryski/go-wyhash

**GO**  https://github.com/orisano/wyhash

**GO** https://github.com/littleli/go-wyhash16

**GO** https://github.com/zeebo/wyhash

**GO** https://github.com/lonewolf3739/wyhash-go

**Java** https://github.com/OpenHFT/Zero-Allocation-Hashing

**Rust**  https://github.com/eldruin/wyhash-rs

**Swift** https://github.com/lemire/SwiftWyhash

**Swift**  https://github.com/lemire/SwiftWyhashBenchmark

**Swift**  https://github.com/jeudesprits/PSWyhash

**V** https://github.com/vlang/v/tree/master/vlib/hash/wyhash (v4)

**Zig** https://github.com/ManDeJan/zig-wyhash

----------------------------------------

I thank these names:

Reini Urban

Dietrich Epp

Joshua Haberman

Tommy Ettinger

Daniel Lemire

Otmar Ertl

cocowalla

leo-yuriev

Diego Barrios Romero

paulie-g 

dumblob

Yann Collet

ivte-ms

hyb

James Z.M. Gao

easyaspi314 (Devin)

