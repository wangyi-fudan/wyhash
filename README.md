Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on all machines, exspecially for short keys.
  
**simplest**: In the sense of code size.

Currently wyhash has 13 language ports and is the default hasher for a hash table of the great Zig and V language.

Please read our ![manuscript](manuscript.docx) and help us to publish it on top journal.

```
wyhash("",0)=bc98efd7661a7a1
wyhash("a",1)=99782e84a7cee30
wyhash("abc",2)=973ed17dfbe006d7
wyhash("message digest",3)=c0189aa4012331f5
wyhash("abcdefghijklmnopqrstuvwxyz",4)=da133f940b62e516
wyhash("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",5)=e062dfda99413626
wyhash("12345678901234567890123456789012345678901234567890123456789012345678901234567890",6)=77092dd38803d1fa
```

----------------------------------------

**Version 4 is ready!**

big endian support. half code size. faster short key hashing, faster bulk key hashing.

corpus: /usr/share/dict/words

|hash|short|hashmap|bulk16M|
|----|----|----|----|
|wyhash |265.961|49.510|17.233|
|XXH64|106.359|34.983|14.577|
|XXH3_scalar|186.166|43.474|13.092|

**Good Boy Only Benchmark** 

XXH3 was not included as it fails two tests according to SMHasher.

```C
#define XXH_INLINE_ALL
#define XXH_FORCE_MEMORY_ACCESS 0
```
![](Clipboard03.png)
![](Clipboard04.png)
![](Clipboard01.png)
![](Clipboard02.png)

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
