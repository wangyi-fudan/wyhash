#define	XXH_VECTOR 0
#include	<sys/time.h>
#include	<iostream>
#include	<fstream>
#include	<vector>
#include	"xxHash/xxh3.h"
#include	"t1ha/t1ha.h"
#include	"wyhash.h"
using	namespace	std;
struct	wy{	size_t	operator()(const	string	&s,	uint64_t seed)const{	return	wyhash(s.c_str(),s.size(),seed,_wyp);	}};
struct	x3{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	XXH3_64bits_withSeed(s.c_str(),s.size(),seed);	}};
struct	xx{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	XXH64(s.c_str(),s.size(),seed);	}};
struct	t1{	size_t	operator()(const	string	&s, uint64_t seed)const{	return	t1ha2_atonce(s.c_str(),s.size(),seed);	}};

vector<string>	v;	
template <class Hasher>
uint64_t	bench_hash(const	char	*name){
	Hasher	h;	string	s;	timeval	beg,	end;	
	uint64_t	dummy=0;	const	uint64_t	N=v.size(),	R=0x10000;
	cerr.precision(2);	cerr.setf(ios::fixed);	cerr<<'|'<<name<<(strlen(name)<8?"\t\t|":"\t|");
	
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=h(v[i],r);
	gettimeofday(&end,NULL);
	cerr<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t\t|\n";
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
	cerr<<"|hash function\t|short hash/us\t|\n";
	cerr<<"|----\t\t|----\t\t|\n";
	r+=bench_hash<wy>("wyhash");
	r+=bench_hash<x3>("xxh3");
	r+=bench_hash<xx>("xxHash64");
	r+=bench_hash<t1>("t1ha2_atonce");
	return	r;
}
