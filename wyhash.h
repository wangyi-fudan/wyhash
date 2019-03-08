//Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_included
#define wyhash_included
const	unsigned long long	wyhashp0=0x60bee2bee120fc15ull;
const	unsigned long long	wyhashp1=0x17a05355f18756b5ull;
inline	unsigned long long	wyhashmix(unsigned long long	A,	unsigned long long	B){	
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B^wyhashp1;	return	(r>>64)^r;	
#else
	B^=wyhashp1;
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
	const	unsigned char	*ptr=(const	unsigned char*)key,	*const	end=ptr+len;
	while(ptr+8<end){	seed=wyhashmix(seed^wyhashp0,wyhashread64(ptr));	ptr+=8;	}
	switch(len&7){
	case	0:	return	wyhashmix(wyhashmix(seed^wyhashp0,wyhashread64(ptr)),len);
	case	1:	return	wyhashmix(wyhashmix(seed^wyhashp0,wyhashread08(ptr)),len);
	case	2:	return	wyhashmix(wyhashmix(seed^wyhashp0,wyhashread16(ptr)),len);
	case	3:	return	wyhashmix(wyhashmix(seed^wyhashp0,(wyhashread16(ptr)<<8)|wyhashread08(ptr+2)),len);
	case	4:	return	wyhashmix(wyhashmix(seed^wyhashp0,wyhashread32(ptr)),len);
	case	5:	return	wyhashmix(wyhashmix(seed^wyhashp0,(wyhashread32(ptr)<<8)|wyhashread08(ptr+4)),len);
	case	6:	return	wyhashmix(wyhashmix(seed^wyhashp0,(wyhashread32(ptr)<<16)|wyhashread16(ptr+4)),len);
	case	7:	return	wyhashmix(wyhashmix(seed^wyhashp0,(wyhashread32(ptr)<<24)|(wyhashread16(ptr+4)<<8)|wyhashread08(ptr+6)),len);
	}
}
#endif
