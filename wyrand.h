/*Author: Wang Yi <godspeed_china@yeah.net>*/
#ifndef wyrand_20190324
#define wyrand_20190324
#if defined(_MSC_VER) && defined(_M_X64)
	#include <intrin.h>
	#pragma	intrinsic(_umul128)
#endif
static	inline	unsigned long long	_wymum(unsigned long long	A,	unsigned long long	B){
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B;	return	(r>>64)^r;
#elif	defined(_MSC_VER) && defined(_M_X64)
	A=_umul128(A, B, &B);	return	A^B;
#else
	unsigned long long	ha=A>>32,	hb=B>>32,	la=(unsigned int)A,	lb=(unsigned int)B,	hi, lo;
	unsigned long long	rh=ha*hb,	rm0=ha*lb,	rm1=hb*la,	rl=la*lb,	t=rl+(rm0<<32),	c=t<rl;
	lo=t+(rm1<<32);	c+=lo<t;	hi=rh+(rm0>>32)+(rm1>>32)+c;
	return hi^lo;
#endif
}
static	inline	unsigned long long	wyrng(unsigned long long *seed){	
	*seed+=11464284564125869423ull;	
	return	_wymum(*seed^14117165359962661627ull,*seed);	
}
#endif
