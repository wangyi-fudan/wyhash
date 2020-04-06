Every hash function is born equal. No hash function is perfect, but some are useful.
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on 64-bit machines, especially for short keys.
  
**simplest**: In the sense of code size.

Please read our ![manuscript](wyhash.docx) and help us to publish it on top journal.

**Version Gamma** is ready. Don't trust benchmark, try it yourself!

/usr/share/dict/words
|hash function  |short hash/us  |bulk_256B GB/s |bulk_64KB GB/s |
|----           |----           |----           |----           |
|wyhash         |325.26         |12.94          |11.76          |
|xxh3_scalar    |152.70         |7.08           |12.68          |
|xxh3_avx2      |137.51         |8.71           |30.36          |
|xxHash64       |99.82          |7.43           |14.65          |
|t1ha2_atonce   |107.90         |12.94          |17.02          |

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

