Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on all machines, exspecially for short keys.
  
**simplest**: In the sense of code size.

Currently wyhash has 13 language ports and is the default hasher for a hash table of the great Zig and V language.

Please read our ![manuscript](manuscript.docx) and help us to publish it on top journal.

**Version 5 is ready. call make_secret function first before hashing**

Benchmark /usr/share/dict/words

|HashFunction|Plain|Hashmap|64KB|16MB|
|----|----|----|----|----|
|std::hash|97.08|37.05|7.33|7.37|
|wyhash|260.69|45.25|26.37|21.86|
|_wyhash|278.10|49.41|26.86|22.33|
|xxHash64|109.37|35.69|14.71|14.59|
|XXH3_scalar|191.42|43.51|13.11|13.11|
|t1ha2_atonce|127.26|36.17|16.59|16.29|

Benchmark enwik8

|HashFunction|Plain|Hashmap|64KB|16MB|
|----|----|----|----|----|
|std::hash|70.27|23.63|7.28|7.36|
|wyhash|148.43|26.12|26.03|21.88|
|_wyhash|151.90|27.86|26.06|22.29|
|xxHash64|91.02|23.13|14.65|14.55|
|XXH3_scalar|122.93|25.73|13.12|13.05|
|t1ha2_atonce|128.41|23.49|16.59|16.14|

----------------------------------------

Language Ports:

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

**Swift**  https://github.com/jeudesprits/SwiftWyhash

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
