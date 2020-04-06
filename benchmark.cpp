#define	XXH_VECTOR	0
#define	T1HA_SYS_UNALIGNED_ACCESS 0
#define T1HA_USE_FAST_ONESHOT_READ 0
#include	"wyhash.h"
#include	"xxHash/xxhash.c"
#include	"t1ha/t1ha.h"
#include	<sys/time.h>
#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<vector>
using	namespace	std;
vector<string>	v;	
struct	wy{	size_t	operator()(const	string	&s,	uint64_t seed)const{	return	wyhash(s.c_str(),s.size(),seed);	}};
struct	x3{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	XXH3_64bits_withSeed(s.c_str(),s.size(),seed);	}};
struct	xx{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	XXH64(s.c_str(),s.size(),seed);	}};
struct	t1{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	t1ha2_atonce(s.c_str(),s.size(),seed);	}};
template <class Hasher>
uint64_t	bench_hash(const	char	*name){
	Hasher	h;	string	s;	
	timeval	beg,	end;	uint64_t	dummy=0,	N=v.size(),	R=0x1000;
	cerr.precision(2);	cerr.setf(ios::fixed);	cerr<<'|'<<name<<(strlen(name)<8?"\t\t|":"\t|");

	for(size_t  i=0;    i<N;    i++)    dummy+=h(v[i],0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=h(v[i],r);
	gettimeofday(&end,NULL);
	cerr<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t\t|";

	s.resize(0x100);
	dummy+=h(s,0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<(R<<8);    r++)	dummy+=h(s,r);
	gettimeofday(&end,NULL);
	double	t=1e-9*(R<<8)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec));
	if(t>1024)	cerr<<"inf\t\t|";	else	cerr<<t<<"\t\t|";

	s.resize(0x10000);
	dummy+=h(s,0);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	dummy+=h(s,r);
	gettimeofday(&end,NULL);
	t=1e-9*R*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec));
	if(t>1024)	cerr<<"inf\t\t|\n";	else	cerr<<t<<"\t\t|\n";
	return	dummy;
}

int	main(void){
	string	file="/usr/share/dict/words";
	string	s;
	ifstream	fi(file.c_str());
	for(fi>>s;	!fi.eof();	fi>>s)	if(s.size())	v.push_back(s);
	fi.close();
	for(size_t	i=v.size()-1;	i;	i--)	swap(v[i],v[rand()%(i+1)]);
	uint64_t	r=0;
	cerr<<file<<'\n';
	cerr<<"|hash function\t|short hash/us\t|bulk_256B GB/s\t|bulk_64KB GB/s\t|\n";
	cerr<<"|----\t\t|----\t\t|----\t\t|----\t\t|\n";
	r+=bench_hash<wy>("wyhash");
	r+=bench_hash<x3>("xxh3");
	r+=bench_hash<xx>("xxHash64");
	r+=bench_hash<t1>("t1ha2_atonce");
	return	r;
}
