#if(WYHASH_LITTLE_ENDIAN)	
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return  v;	}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return  v;	}	
#else
	#if defined(__GNUC__) || defined(__INTEL_COMPILER)
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return   __builtin_bswap64(v);	}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return   __builtin_bswap32(v);	}	
	#elif	defined(_MSC_VER)
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return  _byteswap_uint64(v);}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return  _byteswap_ulong(v);	}	
	#endif
#endif
static	inline	uint64_t	_wyr3(const	uint8_t	*p,	unsigned	k) {	return	(((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];	}
static	inline	uint64_t	wyhash(const void* key,	uint64_t	len,	uint64_t	seed) {
	const	uint8_t	*p=(const	uint8_t*)key;	uint64_t	i=len&63;
	#if defined(__GNUC__) || defined(__INTEL_COMPILER)
		#define	_like_(x)	__builtin_expect(x,1)
		#define	_unlike_(x)	__builtin_expect(x,0)
	#else
		#define _like_(x)  (x)
		#define _unlike_(x)  (x)
	#endif
	if(_unlike_(!i)) {	}
	else	if(_unlike_(i<4))	seed=_wymum(_wyr3(p,i)^seed^_wyp0,seed^_wyp1);
	else	if(_like_(i<=8))	seed=_wymum(_wyr4(p)^seed^_wyp0,_wyr4(p+i-4)^seed^_wyp1);
	else	if(_like_(i<=16))	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+i-8)^seed^_wyp1);
	else	if(_like_(i<=24))	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1)^_wymum(_wyr8(p+i-8)^seed^_wyp2,seed^_wyp3);
	else	if(_like_(i<=32))	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1)^_wymum(_wyr8(p+16)^seed^_wyp2,_wyr8(p+i-8)^seed^_wyp3);
	else{	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1)^_wymum(_wyr8(p+16)^seed^_wyp2,_wyr8(p+24)^seed^_wyp3)^_wymum(_wyr8(p+i-32)^seed^_wyp1,_wyr8(p+i-24)^seed^_wyp2)^_wymum(_wyr8(p+i-16)^seed^_wyp3,_wyr8(p+i-8)^seed^_wyp0);	}
	if(_like_(i==len))	return	_wymum(seed,len^_wyp4);
	uint64_t	see1=seed,	see2=seed,	see3=seed;
	for(p+=i,i=len-i;	_like_(i>=64); i-=64,p+=64) {
		seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1);		see1=_wymum(_wyr8(p+16)^see1^_wyp2,_wyr8(p+24)^see1^_wyp3);	
		see2=_wymum(_wyr8(p+32)^see2^_wyp1,_wyr8(p+40)^see2^_wyp2);	see3=_wymum(_wyr8(p+48)^see3^_wyp3,_wyr8(p+56)^see3^_wyp0);	
	}
	return	_wymum(seed^see1^see2,see3^len^_wyp4);
}
