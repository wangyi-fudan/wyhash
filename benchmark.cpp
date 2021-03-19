#include	<sys/time.h>
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<stdint.h>
#include	<cstring>
#include	<vector>
#ifndef	XXH3
#include	"wyhash.h"
#else
#include	"../xxHash/xxh3.h"
#endif
using	namespace	std;
struct	ha{	
  size_t	operator()(const	string	&s,	uint64_t seed)const{
    #ifndef	XXH3
    return  wyhash(s.c_str(),s.size(),seed,_wyp);	
    #else
    return  XXH3_64bits_withSeed(s.c_str(),s.size(),seed);	
    #endif
  }
};

vector<string>	v;	
template <class Hasher>
uint64_t	bench_hash(const	char	*name){
	Hasher	h;	string	s;	timeval	beg,	end;	
	uint64_t	dummy=0;	const	uint64_t	N=v.size(),	R=0x1000;
	cerr.precision(2);	cerr.setf(ios::fixed);	cerr<<'|'<<name<<(strlen(name)<8?"\t\t|":"\t|");
	
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=h(v[i],r);
	gettimeofday(&end,NULL);
	cerr<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t\t|";

	s.resize(1<<8);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<(R<<14);    r++)	dummy+=h(s,r);
	gettimeofday(&end,NULL);
	cerr<<1e-9*(R<<14)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t\t|";

	s.resize(1<<16);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<(R<<6);    r++)	dummy+=h(s,r);
	gettimeofday(&end,NULL);
	cerr<<1e-9*(R<<6)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t\t|\n";
	return	dummy;
}

int	main(void){
	string	file="/usr/share/dict/words", s;
	ifstream	fi(file.c_str());
	for(fi>>s;	!fi.eof();	fi>>s)	if(s.size())	v.push_back(s);
	fi.close();
	//shuffle the array to benchmark random access
	for(size_t	i=v.size()-1;	i;	i--)	swap(v[i],v[rand()%(i+1)]);
	uint64_t	r=0;
	cerr<<file<<'\n';
	cerr<<"|hash function\t|short hash/us\t|bulk_256B GB/s\t|bulk_64KB GB/s\t|\n";
	cerr<<"|----\t\t|----\t\t|----\t\t|----\t\t|\n";
    #ifndef	XXH3
	r+=bench_hash<ha>("wyhash");
    #else
	r+=bench_hash<ha>("xxh3");
    #endif
	return	r;
}
