Every hash function is born equal. No hash function is perfect, but some are useful.
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on 64-bit machines, especially for short keys.
  
**simplest**: In the sense of code size.

Please read our ![manuscript](wyhash.docx) and help us to publish it on top journal.

Also I would like to introduce a new hash function "**FastestHash**" which is fastest in hashmap.

| Benchmarking | /usr/share/dict/words |         |       |          |         |       |
| ------------ | --------------------- | ------- | ----- | -------- | ------- | ----- |
| HashFunction | Words                 | Hashmap | 1K    | 256K     | 16M     | 1G    |
| std::hash    | 96.72                 | 35.43   | 6.89  | 7.38     | 7.36    | 6.49  |
| FastestHash  | 725.33                | 51.76   | 209.8 | 53771.11 | 3435974 | inf   |
| wyhash       | 268.39                | 45.95   | 24.33 | 24.33    | 22.31   | 10.96 |

**FastestHash offical code**:
```C
static inline uint64_t _wyr4(const uint8_t *p){ unsigned v; memcpy(&v, p, 4); return v; }
static inline uint64_t _wyr3(const uint8_t *p, unsigned k){ return (((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1]; }
static inline uint64_t FastestHash(const void *key, size_t len, uint64_t seed){
 const uint8_t *p=(const uint8_t*)key;
 return _likely_(len>=4)?(_wyr4(p)+_wyr4(p+len-4))*(_wyr4(p+(len>>1)-2)^seed):(_likely_(len)?_wyr3(p,len)*(_wyp[0]^seed):seed);
}
```

**Version Alpha is ready. call make_secret function first before hashing**

![](Clipboard01.png)
![](Clipboard02.png)

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
