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

|HashFunction|Plain(h/us)|Hashmap(h/us)|64KB(GB/s)|16MB(GB/s)|Limitations|
|----|----|----|----|----|----|
|FastestHash|287.09|51.06|14198.24|3435973.84|fail many tests|
|std::hash|74.80|35.36|7.33|7.37|fail many tests|
|_wyhash|210.86|48.01|26.03|21.53|fail many tests|
|**wyhash**|202.01|44.04|26.02|23.01|62 bit uniqueness strength, loss entropy after 67,108,864 TB data|
|xxHash64|92.74|35.00|14.71|14.59||
|XXH3_scalar|152.29|42.42|13.11|13.11|Moment Chi2 14974, BIC,unaligned memory access|
|XXH3_SSE2|150.94|42.26|23.44|22.07|Moment Chi2 14974, BIC,SSE2,unaligned memory access|
|XXH3_AVX2|152.37|42.24|28.08|25.20|Moment Chi2 14974, BIC,AVX2,unaligned memory access|
|t1ha2_atonce|106.08|35.19|16.59|16.29|unaligned memory access(default),one-shot read(default)|

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

hyb

James Z.M. Gao
