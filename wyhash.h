/*	Author: Wang Yi <godspeed_china@yeah.net>	*/
#ifndef wyhash_version_4
#define wyhash_version_4
#include	<stdint.h>
#include	<string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma	intrinsic(_umul128)
#endif
const	uint64_t	_wyp0=0xa0761d6478bd642full,	_wyp1=0xe7037ed1a0b428dbull,	_wyp2=0x8ebc6af09c88c6e3ull,	_wyp3=0x589965cc75374cc3ull,	_wyp4=0x1d8e4e27c47d124full;
static	inline	uint64_t	_wyrotr(uint64_t v, unsigned k) {	return	(v>>k)|(v<<(64-k));	}
static	inline	uint64_t	_wymum(uint64_t	A,	uint64_t	B) {
#ifndef	WYHASH64
	uint64_t    hh=(A>>32)*(B>>32), hl=(A>>32)*(unsigned)B, lh=(unsigned)A*(B>>32), ll=(uint64_t)(unsigned)A*(unsigned)B;
	return  _wyrotr(hl,32)^_wyrotr(lh,32)^hh^ll;
#else
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B;	return	(r>>64)^r;
#elif	defined(_MSC_VER) && defined(_M_X64)
	A=_umul128(A, B, &B);	return	A^B;
#else
	uint64_t	ha=A>>32,	hb=B>>32,	la=(uint32_t)A,	lb=(uint32_t)B,	hi, lo;
	uint64_t	rh=ha*hb,	rm0=ha*lb,	rm1=hb*la,	rl=la*lb,	t=rl+(rm0<<32),	c=t<rl;
	lo=t+(rm1<<32);	c+=lo<t;hi=rh+(rm0>>32)+(rm1>>32)+c;	return hi^lo;
#endif
#endif
}
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t v;	memcpy(&v,  p,  8);	return  v;	}
static	inline	uint64_t	_wyr4(const	uint8_t	*p) {	uint32_t v;	memcpy(&v,	p,	4);	return	v;	}
static	inline	uint64_t	_wyr3(const	uint8_t	*p,	unsigned	k) {	return	(((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];	}
static	inline	uint64_t	wyhash(const void* key,	uint64_t	len,	uint64_t	seed) {
	const	uint8_t	*p=(const	uint8_t*)key;	uint64_t	i=len&63,	see1=seed;
	if(!i) {	if(len==i)	goto	ret;	}
	else	if(i<4){	seed=_wymum(_wyr3(p,i)^seed^_wyp0,seed^_wyp1);	if(len==i)	goto	ret;	}
	else	if(i<=8){	seed=_wymum(_wyr4(p)^seed^_wyp0,_wyr4(p+i-4)^seed^_wyp1);	if(len==i)	goto	ret;	}
	else	if(i<=16){	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+i-8)^seed^_wyp1);	if(len==i)	goto	ret;	}
	else	if(i<=24) {	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1);	see1=_wymum(_wyr8(p+i-8)^see1^_wyp2,see1^_wyp3);	if(len==i)	goto	ret;	} 
	else	if(i<=32){	seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1);	see1=_wymum(_wyr8(p+16)^see1^_wyp2,_wyr8(p+i-8)^see1^_wyp3);	if(len==i)	goto	ret;	}
	else{	
		seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1)^_wymum(_wyr8(p+16)^seed^_wyp2,_wyr8(p+24)^seed^_wyp3);	
		see1=_wymum(_wyr8(p+i-32)^see1^_wyp1,_wyr8(p+i-24)^see1^_wyp2)^_wymum(_wyr8(p+i-16)^see1^_wyp3,_wyr8(p+i-8)^see1^_wyp0);	
		if(len==i)	goto	ret;
	}
	for(p+=i,i=len-i;	i>=64; i-=64,p+=64) {	
		seed=_wymum(_wyr8(p)^seed^_wyp0,_wyr8(p+8)^seed^_wyp1)^_wymum(_wyr8(p+16)^seed^_wyp2,_wyr8(p+24)^seed^_wyp3);	
		see1=_wymum(_wyr8(p+32)^see1^_wyp1,_wyr8(p+40)^see1^_wyp2)^_wymum(_wyr8(p+48)^see1^_wyp3,_wyr8(p+56)^see1^_wyp0);	
	}
	ret:	return	_wymum(seed^see1,len^_wyp4);
}
static	inline	uint64_t	wyhash64(uint64_t	A, uint64_t	B) {	return	_wymum(_wymum(A^_wyp0,	B^_wyp1),	_wyp2);	}
static	inline	uint64_t	wyrand(uint64_t	*seed) {	*seed+=_wyp0;	return	_wymum(*seed^_wyp1,*seed);	}
static	inline	double	wy2u01(uint64_t	r) {	const	double	_wynorm=1.0/(1ull<<52);	return	(r>>11)*_wynorm;	}
static	inline	double	wy2gau(uint64_t	r) {	const	double	_wynorm=1.0/(1ull<<21);	return	((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;	}
#endif
