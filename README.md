Simple Is Best
====

wyhash and wyrand are the ideal 64-bit hash function and PRNG respectively: solid, portable, fastest, simplest. wyhash passed SMHasher, wyrand passed BigCrush, practrand and designed to drop-in replace C rand(). See our [manuscript](manuscript.md). Currently wyhash is a hasher by default in a hash table in the great Zig language.

wyhash_v3
----

Dear users, wyhash now upgrades to version 3. 

* v3 provides double bulk speed compared to v2.

* v3 provides extra 60% speed for dynamic length short key compared to v2.

* v3 code size have been halfed. The big switch disappears, thanks to xxh3's idea for finalization.

* v3 comes up with the WYHASH32 macro that is a new 32-bit-machine efficient hash function. Ideal for real applications.

It closes to the perfection. Cheers!


----------------------------------------

wyrand code:
```C
inline	uint64_t	wyrand(uint64_t	*seed){    
	*seed+=0xa0761d6478bd642full;    
	__uint128_t	t=(__uint128_t)(*seed^0xe7037ed1a0b428dbull)*(*seed);    
	return	(t>>64)^t;    
}
```

Benchmarks
----

![](Clipboard01.png)
![](Clipboard02.png)
![](Clipboard03.png)
![](Clipboard04.png)
![](Clipboard05.png)

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

