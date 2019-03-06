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
#ifndef __wyhash__
#define __wyhash__
#include	<stdint.h>
//the following functions is should not be called outside the file
inline	uint64_t	wyhashmix64(uint64_t	A,	uint64_t	B){	__uint128_t	r=A^0x60bee2bee120fc15ull;	r*=B^0xa3b195354a39b70dull;	return	(r>>64)^r;	}
inline	unsigned	wyhashmix32(unsigned	A,	unsigned	B){	uint64_t	r=A^0x7b16763u;	r*=B^0xe4f5a905u;	return	(r>>32)^r;	}
inline	uint64_t	wyhashread64(const	void	*const	ptr){	return	*(uint64_t*)(ptr);	}
inline	uint64_t	wyhashread32(const	void	*const	ptr){	return	*(uint32_t*)(ptr);	}
inline	uint64_t	wyhashread16(const	void	*const	ptr){	return	*(uint16_t*)(ptr);	}
inline	uint64_t	wyhashread08(const	void	*const	ptr){	return	*(uint8_t*)(ptr);	}

//the following function is the general hash function to be called
inline	uint64_t	wyhash(const void* key,	uint64_t	len, uint64_t	seed){
	const	uint8_t	*ptr=(const	uint8_t*)key,	*const	end=ptr+len;
	while(ptr+8<=end){	seed=wyhashmix64(seed,	wyhashread64(ptr));	ptr+=8;	}
	switch(end-ptr){
		case	1:	seed=wyhashmix64(seed,	wyhashread08(ptr));	break;
		case	2:	seed=wyhashmix64(seed,	wyhashread16(ptr));	break;
		case	3:	seed=wyhashmix64(seed,	(wyhashread16(ptr)<<8)|wyhashread08(ptr+2));	break;
		case	4:	seed=wyhashmix64(seed,	wyhashread32(ptr));	break;
		case	5:	seed=wyhashmix64(seed,	(wyhashread32(ptr)<<8)|wyhashread08(ptr+4));	break;
		case	6:	seed=wyhashmix64(seed,	(wyhashread32(ptr)<<16)|wyhashread16(ptr+4));	break;
		case	7:	seed=wyhashmix64(seed,	(wyhashread32(ptr)<<24)|(wyhashread16(ptr+4)<<8)|wyhashread08(ptr+6));	break;
	}
	return	wyhashmix64(seed,	len);
}

//the following function is for 64bit integer hasing, the return value is consistant with the general funciton
inline	uint64_t	wyhash64(uint64_t	key, uint64_t	seed){	return	wyhashmix64(wyhashmix64(seed,	key),	8);	}

//the following function is for 32bit integer hashing, the return value is NOT consistant with the general funciton
inline	unsigned	wyhash32(unsigned	key, unsigned	seed){	return	wyhashmix32(wyhashmix32(seed,	key),	4);	}

#endif

