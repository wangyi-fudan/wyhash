//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_included
#define wyhash_included
#ifndef UNLIKELY
#if defined(__GNUC__) || defined(__INTEL_COMPILER)
#define UNLIKELY(x) (__builtin_expect(!!(x), 0))
#else
#define UNLIKELY(x) (x)
#endif
#endif
const	unsigned long long	wyhashp0=0x60bee2bee120fc15ull;
const	unsigned long long	wyhashp1=0xa3b195354a39b70dull;
const	unsigned long long	wyhashp2=0x1b03738712fad5c9ull;
const	unsigned long long	wyhashp3=0xd985068bc5439bd7ull;
const	unsigned long long	wyhashp4=0x897f236fb004a8e7ull;
inline	unsigned long long	wyhashmix(unsigned long long	A,	unsigned long long	B){	
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B^wyhashp0;	return	(r>>64)^r;	
#else
	B^=wyhashp0;
	unsigned long long	ha=A>>32,	hb=B>>32,	la=(unsigned int)A,	lb=(unsigned int)B,	hi, lo;
	unsigned long long	rh=ha*hb,	rm0=ha*lb,	rm1=hb*la,	rl=la*lb,	t=rl+(rm0<<32),	c=t<rl;
	lo=t+(rm1<<32);	c+=lo<t;	hi=rh+(rm0>>32)+(rm1>>32)+c;
	return hi^lo;
#endif
}
inline	unsigned long long	wyhashread64(const	void	*const	ptr){	return	*(unsigned long long*)(ptr);	}
inline	unsigned long long	wyhashread32(const	void	*const	ptr){	return	*(unsigned int*)(ptr);	}
inline	unsigned long long	wyhashread16(const	void	*const	ptr){	return	*(unsigned short*)(ptr);	}
inline	unsigned long long	wyhashread08(const	void	*const	ptr){	return	*(unsigned char*)(ptr);	}
inline	unsigned long long	wyhash(const void* key,	unsigned long long	len, unsigned long long	seed){
	const	unsigned char	*ptr=(const	unsigned char*)key;
	if(UNLIKELY(len>32)){
		unsigned long long i;
		for(i=0;	i+32<len;	i+=32,	ptr+=32)	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,wyhashread64(ptr+24));
	}
	switch(len&31){
	case	0:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,wyhashread64(ptr+24));	break;
	case	1:	seed=wyhashmix(seed^wyhashp1,wyhashread08(ptr));	break;	
	case	2:	seed=wyhashmix(seed^wyhashp1,wyhashread16(ptr));	break;
	case	3:	seed=wyhashmix(seed^wyhashp1,(wyhashread16(ptr)<<8)|wyhashread08(ptr+2));	break;
	case	4:	seed=wyhashmix(seed^wyhashp1,wyhashread32(ptr));	break;
	case	5:	seed=wyhashmix(seed^wyhashp1,(wyhashread32(ptr)<<8)|wyhashread08(ptr+4));	break;
	case	6:	seed=wyhashmix(seed^wyhashp1,(wyhashread32(ptr)<<16)|wyhashread16(ptr+4));	break;
	case	7:	seed=wyhashmix(seed^wyhashp1,(wyhashread32(ptr)<<24)|(wyhashread16(ptr+4)<<8)|wyhashread08(ptr+6));	break;
	case	8:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr));	break;
	case	9:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread08(ptr+8));	break;	
	case	10:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread16(ptr+8));	break;
	case	11:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,(wyhashread16(ptr+8)<<8)|wyhashread08(ptr+8+2));	break;
	case	12:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread32(ptr+8));	break;
	case	13:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,(wyhashread32(ptr+8)<<8)|wyhashread08(ptr+8+4));	break;
	case	14:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,(wyhashread32(ptr+8)<<16)|wyhashread16(ptr+8+4));	break;
	case	15:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,(wyhashread32(ptr+8)<<24)|(wyhashread16(ptr+8+4)<<8)|wyhashread08(ptr+8+6));	break;
	case	16:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8));	break;
	case	17:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread08(ptr+16));	break;	
	case	18:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread16(ptr+16));	break;
	case	19:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,(wyhashread16(ptr+16)<<8)|wyhashread08(ptr+16+2));	break;
	case	20:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread32(ptr+16));	break;
	case	21:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,(wyhashread32(ptr+16)<<8)|wyhashread08(ptr+16+4));	break;
	case	22:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,(wyhashread32(ptr+16)<<16)|wyhashread16(ptr+16+4));	break;
	case	23:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,(wyhashread32(ptr+16)<<24)|(wyhashread16(ptr+16+4)<<8)|wyhashread08(ptr+16+6));	break;
	case	24:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16));	break;
	case	25:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,wyhashread08(ptr+24));	break;	
	case	26:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,wyhashread16(ptr+24));	break;
	case	27:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,(wyhashread16(ptr+24)<<8)|wyhashread08(ptr+24+2));	break;
	case	28:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,wyhashread32(ptr+24));	break;
	case	29:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,(wyhashread32(ptr+24)<<8)|wyhashread08(ptr+24+4));	break;
	case	30:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,(wyhashread32(ptr+24)<<16)|wyhashread16(ptr+24+4));	break;
	case	31:	seed=wyhashmix(seed^wyhashp1,wyhashread64(ptr))^wyhashmix(seed^wyhashp2,wyhashread64(ptr+8))^wyhashmix(seed^wyhashp3,wyhashread64(ptr+16))^wyhashmix(seed^wyhashp4,(wyhashread32(ptr+24)<<24)|(wyhashread16(ptr+24+4)<<8)|wyhashread08(ptr+24+6));	break;
	}
	return	wyhashmix(seed,	len);
}
inline	unsigned int	wyhashmix32(unsigned int	A,	unsigned int	B){	
	unsigned long long	r=(unsigned long long)A*(unsigned long long)B;	return	(r>>32)^r;	
}
inline	unsigned int	wyhash32(unsigned int	A, unsigned int	B){	
	return	wyhashmix32(wyhashmix32(A^0x7b16763u,	B^0xe4f5a905u),	0x4a9e6939u);	
}
inline	unsigned long long	wyrngmix(unsigned long long	A,	unsigned long long	B){	
	__uint128_t	r=A;	r*=B;	return	(r>>64)^r;	
}	
inline	unsigned long long	wyrng(unsigned long long *seed){	
	*seed+=wyhashp0;	return	wyrngmix(wyrngmix(*seed,	wyhashp1),	wyhashp2);	
}
#endif
