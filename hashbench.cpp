#include	<sys/time.h>
#include	"wyhash/wyhash.h"
#include	"xxHash/xxh3.h"
#include	<iostream>
#include	<vector>
using	namespace	std;
const	size_t	R=0x1000;

// Kaze was here
#include <stdint.h> // uint8_t needed
#define _PADr_KAZE(x, n) ( ((x) << (n))>>(n) )
// Many thanks go to Yurii 'Hordi' Hordiienko, he lessened with 3 instructions the original 'Pippip', thus:
//#include <stdlib.h>
//#include <stdint.h>
uint32_t FNV1A_Pippip_Yurii(const char *str, size_t wrdlen) {
	const uint32_t PRIME = 591798841; uint32_t hash32; uint64_t hash64 = 14695981039346656037;
	size_t Cycles, NDhead;
if (wrdlen > 8) {
	Cycles = ((wrdlen - 1)>>4) + 1; NDhead = wrdlen - (Cycles<<3);
        for(; Cycles--; str += 8) {
		hash64 = ( hash64 ^ (*(uint64_t *)(str)) ) * PRIME;        
		hash64 = ( hash64 ^ (*(uint64_t *)(str+NDhead)) ) * PRIME;        
	}
} else
	hash64 = ( hash64 ^ _PADr_KAZE(*(uint64_t *)(str+0), (8-wrdlen)<<3) ) * PRIME;        
hash32 = (uint32_t)(hash64 ^ (hash64>>32)); return hash32 ^ (hash32 >> 16);
} // Last update: 2019-Oct-30, 14 C lines strong, Kaze.

int	main(void){
	vector<string>	v;	string	s;	for(cin>>s;	!cin.eof();	cin>>s)	v.push_back(s);
	timeval	beg,	end;	uint64_t	dummy=0,	N=v.size();	double	dt;
	
	for(size_t	i=0;	i<N;	i++)	dummy+=XXH3_64bits_withSeed(v[i].c_str(),	v[i].size(),	0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=XXH3_64bits_withSeed(v[i].c_str(), v[i].size(),    r);
	gettimeofday(&end,NULL);
	dt=end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec);
	cerr<<"xxh3\t"<<1e-6*R*N/dt<<"\thashes/us\n";

	for(size_t	i=0;	i<N;	i++)	dummy+=wyhash(v[i].c_str(),	v[i].size(),	0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=wyhash(v[i].c_str(), v[i].size(),    r);
	gettimeofday(&end,NULL);
	dt=end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec);
	cerr<<"wyhash_v3\t"<<1e-6*R*N/dt<<"\thashes/us\n";

	for(size_t	i=0;	i<N;	i++)	dummy+=FNV1A_Pippip_Yurii(v[i].c_str(),	v[i].size());
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=FNV1A_Pippip_Yurii(v[i].c_str(), v[i].size());
	gettimeofday(&end,NULL);
	dt=end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec);
	cerr<<"FNV1A_Pippip_Yurii\t"<<1e-6*R*N/dt<<"\thashes/us\n";
	return	dummy;
}
