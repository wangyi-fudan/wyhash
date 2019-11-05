#include	<sys/time.h>
#include	"wyhash/wyhash.h"
#include	"xxHash/xxh3.h"
#include	"hashes.h"
#include	<iostream>
#include	<vector>
using	namespace	std;
const	size_t	R=0x1000;
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

	for(size_t	i=0;	i<N;	i++)	dummy+=FNV1A_Pippip_Yurii(v[i].c_str(),	v[i].size(),0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=FNV1A_Pippip_Yurii(v[i].c_str(), v[i].size(),r);
	gettimeofday(&end,NULL);
	dt=end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec);
	cerr<<"FNV1A_Pippip_Yurii\t"<<1e-6*R*N/dt<<"\thashes/us\n";
	return	dummy;
}
