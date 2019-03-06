/* Copyright (c) 2019 Yi Wang <godspeed_china@yeah.net>

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#ifndef wyhash_included
#define wyhash_included
//the following functions should not be called outside the file
inline	unsigned long long	wyhashmix64(unsigned long long	A,	unsigned long long	B){	
#ifdef __SIZEOF_INT128__
	__uint128_t	r=A;	r*=B^0xa3b195354a39b70dull;	return	(r>>64)^r;	
#else
	// compromised for compatibility
	B^=0xa3b195354a39b70dull;
	unsigned long long	ha=A>>32,	hb=B>>32,	la=(unsigned int)A,	lb=(unsigned int)B,	hi, lo;
	unsigned long long	rh=ha*hb,	rm0=ha*lb,	rm1=hb*la,	rl=la*lb,	t=rl+(rm0<<32),	c=t<rl;
	lo=t+(rm1<<32);	c+=lo<t;	hi=rh+(rm0>>32)+(rm1>>32)+c;
	return hi^lo;
#endif
}
inline	unsigned int	wyhashmix32(unsigned int	A,	unsigned int	B){
	unsigned long long	r=(unsigned long long)A*(unsigned long long)B;	return	(r>>32)^r;	
}
inline	unsigned long long	wyhashread64(const	void	*const	ptr){	return	*(unsigned long long*)(ptr);	}
inline	unsigned long long	wyhashread32(const	void	*const	ptr){	return	*(unsigned int*)(ptr);	}
inline	unsigned long long	wyhashread16(const	void	*const	ptr){	return	*(unsigned short*)(ptr);	}
inline	unsigned long long	wyhashread08(const	void	*const	ptr){	return	*(unsigned char*)(ptr);	}
//the following function is the general hash function to be called
inline	unsigned long long	wyhash(const void* key,	unsigned long long	len, unsigned long long	seed){
	const	unsigned char	*ptr=(const	unsigned char*)key,	*const	end=ptr+len;
	for(seed^=0x60bee2bee120fc15ull;	ptr+8<=end;	ptr+=8)	seed=wyhashmix64(seed,wyhashread64(ptr));
	switch(end-ptr){
	case	1:	return	wyhashmix64(wyhashmix64(seed,wyhashread08(ptr)),len);
	case	2:	return	wyhashmix64(wyhashmix64(seed,wyhashread16(ptr)),len);
	case	3:	return	wyhashmix64(wyhashmix64(seed,(wyhashread16(ptr)<<8)|wyhashread08(ptr+2)),len);
	case	4:	return	wyhashmix64(wyhashmix64(seed,wyhashread32(ptr)),len);
	case	5:	return	wyhashmix64(wyhashmix64(seed,(wyhashread32(ptr)<<8)|wyhashread08(ptr+4)),len);
	case	6:	return	wyhashmix64(wyhashmix64(seed,(wyhashread32(ptr)<<16)|wyhashread16(ptr+4)),len);
	case	7:	return	wyhashmix64(wyhashmix64(seed,(wyhashread32(ptr)<<24)|(wyhashread16(ptr+4)<<8)|wyhashread08(ptr+6)),len);
	default:	return	wyhashmix64(seed,len);
	}
}
//the following function is specialized for very fast 32bit integer hashing.
inline	unsigned int	wyhash32(unsigned int	key, unsigned int	seed){
	return	wyhashmix32(wyhashmix32(seed^0x7b16763u,	key^0xe4f5a905u),	0x4a9e6939u);	
}
#endif
