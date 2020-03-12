Every hash function is born equal. No hash function is perfect, but some are useful.
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: 

**solid**:  wyhash passed SMHasher, wyrand passed BigCrush, practrand.

**portable**: 64-bit/32-bit system, big/little endian.
  
**fastest**:  Effecient on 64-bit machines, especially for short keys.
  
**simplest**: In the sense of code size.

Please read our ![manuscript](wyhash.docx) and help us to publish it on top journal.

**Version Beta** is ready. This version solve the problem of 62 bit uniqueness strength mentioned by Yann Collet.

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

Also I would like to introduce a new hash function **o1hash** (aka. FastestHash) which is fastest in hashmap but not secure. It is used in V language now.

| Benchmarking | /usr/share/dict/words |         |       |          |         |       |
| ------------ | --------------------- | ------- | ----- | -------- | ------- | ----- |
| HashFunction | Words                 | Hashmap | 1K    | 256K     | 16M     | 1G    |
| std::hash    | 96.72                 | 35.43   | 6.89  | 7.38     | 7.36    | 6.49  |
| o1hash       | 725.33                | 53.60   | 209.8 | 53771.11 | 3435974 | inf   |
| wyhash       | 277.49                | 46.71   | 23.36 | 23.98    | 21.23   | 10.63 |

**o1hash official code**:
```C
/*
  Author: Wang Yi <godspeed_china@yeah.net>
  This is a quick and dirty hash function designed for O(1) speed.
  It makes your hash table application fly in most cases.
  It samples first, middle and last 4 bytes to produce the hash.
  Do not use it in any serious applications as it's not secure.
*/
static inline uint64_t o1hash(const void *key, size_t len) {
  const uint8_t *p=(const uint8_t*)key;
  if(len>=4) {
    unsigned first, middle, last;
    memcpy(&first,p,4);
    memcpy(&middle,p+(len>>1)-2,4);
    memcpy(&last,p+len-4,4);
    return  (uint64_t)(first+last)*middle;
  }
  if(len) return ((((unsigned)p[0])<<16) | (((unsigned)p[len>>1])<<8) | p[len-1])*0xa0761d6478bd642full;
  return  0;
}
```

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

