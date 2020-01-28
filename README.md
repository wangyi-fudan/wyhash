Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on all machines, exspecially for short keys.
  
**simplest**: In the sense of code size.

Currently wyhash has 13 language ports and is the default hasher for a hash table of the great Zig language.

----------------------------------------

**Version 4 is ready!**

big endian support. half code size. faster short key hashing, faster bulk key hashing.

![](Clipboard05.png)
![](Clipboard06.png)

**Good Boy Only Benchmark** 

XXH3 was not included as it fails two tests according to SMHasher.

```C
#define T1HA_SYS_UNALIGNED_ACCESS 0
#define T1HA_USE_FAST_ONESHOT_READ 0
#define XXH_INLINE_ALL
#define XXH_FORCE_MEMORY_ACCESS 0
```
![](Clipboard03.png)
![](Clipboard04.png)
![](Clipboard01.png)
![](Clipboard02.png)

----------------------------------------

Language Ports:

**V** (v4) https://github.com/vlang/v/tree/master/vlib/hash/wyhash

**GO**  https://github.com/dgryski/go-wyhash

**GO**  https://github.com/orisano/wyhash

**GO** https://github.com/littleli/go-wyhash16

**GO** https://github.com/zeebo/wyhash

**GO** https://github.com/lonewolf3739/wyhash-go

**Swift** https://github.com/lemire/SwiftWyhash

**Swift**  https://github.com/lemire/SwiftWyhashBenchmark

**Swift**  https://github.com/jeudesprits/SwiftWyhash

**Zig** https://github.com/ManDeJan/zig-wyhash

**Java** https://github.com/OpenHFT/Zero-Allocation-Hashing

**Rust**  https://github.com/eldruin/wyhash-rs

**C#**  https://github.com/cocowalla/wyhash-dotnet

**C++**  https://github.com/tommyettinger/waterhash

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
