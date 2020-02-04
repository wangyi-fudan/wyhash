//	Author: Wang Yi <godspeed_china@yeah.net>
#ifndef wyhash_version_5
#define wyhash_version_5
#include	<stdint.h>
#include	<string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma	intrinsic(_umul128)
#endif
static	inline	uint64_t	_wyrotr(uint64_t v, unsigned k) {	return	(v>>k)|(v<<(64-k));	}
static	inline	uint64_t	_wymum(uint64_t	A,	uint64_t	B) {
#ifdef	WYHASH32
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
static	inline	uint64_t	wyrand(uint64_t	*seed) {	*seed+=0xa0761d6478bd642full;	return	_wymum(*seed^0xe7037ed1a0b428dbull,*seed);	}
#ifndef WYHASH_LITTLE_ENDIAN
	#if	defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)		
		#define WYHASH_LITTLE_ENDIAN 1
	#elif	defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)	
		#define WYHASH_LITTLE_ENDIAN 0
	#endif
#endif
#if(WYHASH_LITTLE_ENDIAN)	
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return  v;	}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return  v;	}	
#else
	#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return   __builtin_bswap64(v);	}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return   __builtin_bswap32(v);	}	
	#elif	defined(_MSC_VER)
static	inline	uint64_t	_wyr8(const	uint8_t	*p)	{	uint64_t	v;	memcpy(&v,  p,  8);	return  _byteswap_uint64(v);}	
static	inline	uint64_t	_wyr4(const	uint8_t	*p)	{	unsigned	v;	memcpy(&v,  p,  4);	return  _byteswap_ulong(v);	}	
	#endif
#endif
static	inline	uint64_t	_wyr3(const	uint8_t	*p,	unsigned	k) {	return	(((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];	}
static	inline	uint64_t	_wyhash(const void* key,	uint64_t	len,	uint64_t	seed,	const	uint64_t	secret[6]) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
	#define	_like_(x)	__builtin_expect(x,1)
	#define	_unlike_(x)	__builtin_expect(x,0)
#else
	#define _like_(x)  (x)
	#define _unlike_(x)  (x)
#endif
	const	uint8_t	*p=(const	uint8_t*)key;	uint64_t	i=len;	seed^=secret[4];
	if(_like_(i<=64)){
		label:
		if(_unlike_(i<4))	return	_wymum((_like_(i)?_wyr3(p,i):0)^secret[0],seed);
		else	if(_like_(i<=8))	return	_wymum(_wyr4(p)^secret[0],_wyr4(p+i-4)^seed);
		else	if(_like_(i<=16))	return	_wymum(_wyr8(p)^secret[0],_wyr8(p+i-8)^seed);
		else	if(_like_(i<=32))	return	_wymum(_wyr8(p)^secret[0],_wyr8(p+8)^seed)^_wymum(_wyr8(p+i-16)^secret[1],_wyr8(p+i-8)^seed);
		else	return	_wymum(_wyr8(p)^secret[0],_wyr8(p+8)^seed)^_wymum(_wyr8(p+16)^secret[1],_wyr8(p+24)^seed)^_wymum(_wyr8(p+i-32)^secret[2],_wyr8(p+i-24)^seed)^_wymum(_wyr8(p+i-16)^secret[3],_wyr8(p+i-8)^seed);
	}
	uint64_t	see1=seed,	see2=seed,	see3=seed;
	for(;	_like_(i>=64); i-=64,p+=64){
		seed=_wymum(_wyr8(p)^secret[0],_wyr8(p+8)^seed);		see1=_wymum(_wyr8(p+16)^secret[1],_wyr8(p+24)^see1);
		see2=_wymum(_wyr8(p+32)^secret[2],_wyr8(p+40)^see2);	see3=_wymum(_wyr8(p+48)^secret[3],_wyr8(p+56)^see3);
	}
	seed^=see1^see2^see3;
	goto	label;
}
static	inline	uint64_t	wyhash(const void* key,	uint64_t	len,	uint64_t	seed,	const	uint64_t	secret[6]) {
	return	_wymum(_wyhash(key,len,seed,secret),len^secret[5]);
}
static	inline	void	make_secret(uint64_t	seed,	uint64_t	secret[6]){
	for(size_t	i=0;	i<6;	i++){
		uint8_t	ok;
		do{	ok=1;	secret[i]=0;
			for(size_t	j=0;	j<64;	j+=2)	secret[i]|=1ull<<((wyrand(&seed)&1)+j);
			for(size_t	j=0;	j<i;	j++)	
	#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
				if(__builtin_popcountll(secret[i]^secret[j])!=32)	ok=0;
	#elif	defined(_MSC_VER)
				if(_mm_popcnt_u64(secret[i]^secret[j])!=32)	ok=0;
	#endif	
		}while(!ok);
	}
}
static	inline	uint64_t	wyhash64(uint64_t	A, uint64_t	B) {	return	_wymum(_wymum(A^0xa0761d6478bd642full,B^0xe7037ed1a0b428dbull),0x8ebc6af09c88c6e3ull);	}
static	inline	double	wy2u01(uint64_t	r) {	const	double	_wynorm=1.0/(1ull<<52);	return	(r>>11)*_wynorm;	}
static	inline	double	wy2gau(uint64_t	r) {	const	double	_wynorm=1.0/(1ull<<20);	return	((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;	}
#ifdef WYHASH_EXTRA
#include	<vector>
template	<uint64_t	Bits,	typename	KeyT,	typename	HashT,	typename	EqT>	//  the minimum fast hash table/set
static	inline	size_t	key2pos(const	KeyT	&key,	std::vector<KeyT>	&keys,	std::vector<bool>	&used){
	HashT	hasher;		EqT	equaler;	uint64_t	h=hasher(key);
	for(uint64_t	j=1,r=h;	j;	j++,	r=wyhash64(h,j)){
		for(size_t	j=0;	j<16;	j++){	size_t	p=_wyrotr(r,j<<2)>>(64-Bits);	if(equaler(key,keys[p])||!used[p])	return	p;	}
	}
	return	~0ull;
}
/*	hashmap/hashset example
#include	<iostream>
#include	"wyhash.h"
using	namespace	std;
struct	hasher{	size_t	operator()(const	string	&s)const{	return	wyhash(s.c_str(),s.size(),0);	}};
int	main(void){
	std::vector<string>	keys(1ull<<20);	std::vector<bool>	used(1ull<<20);	std::vector<unsigned>	values(1ull<<20);
	string	s;	size_t	pos=0;
	for(cin>>s;	!cin.eof();	cin>>s){
		pos=key2pos<20,string,	hasher>(s,keys,used);
		if(!used[pos]){	keys[pos]=s;	used[pos]=true;	values[pos]=0;	}
		else	values[pos]++;
	}
	return	pos;
}*/
//  the minimum bloom filter. paramters calculator: https://hur.st/bloomfilter/
static	inline	void	bfpush(uint64_t	hash_of_key,	std::vector<bool>	&bitset,	size_t	size,	size_t	round){
	for(size_t	i=0;	i<round;	i++)	bitset[(((__uint128_t)wyhash64(hash_of_key,i))*size)>>64]=true;
}
static	inline	size_t	bftest(uint64_t	hash_of_key,	std::vector<bool>	&bitset,	size_t	size,	size_t	round){
	for(size_t	i=0;	i<round;	i++)	if(!bitset[(((__uint128_t)wyhash64(hash_of_key,i))*size)>>64])	return	false;
	return	true;
}
/*bloom filter example
#include	<iostream>
#include	"wyhash.h"
using	namespace	std;
int	main(void){
	size_t	size=0x2000000;	std::vector<bool>	bits(size);
	string	s;
	for(cin>>s;	!cin.eof();	cin>>s)		bfpush(wyhash(s.c_str(),s.size(),0),bits,size,4);
	cout<<bftest(wyhash("abc",3,0),bits,size,4)<<'\n';
	cout<<bftest(wyhash("abcdshk",7,0),bits,size,4)<<'\n';
}*/
#endif
#endif
