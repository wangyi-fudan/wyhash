#include	"parallel-hashmap/parallel_hashmap/phmap.h"
#include	"smhasher/meow_hash_x64_aesni.h"
#include	"wyhash/wyhash.h"
#include	"xxHash/xxhash.c"
#include	"t1ha/t1ha.h"
#include	<sys/time.h>
#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<vector>
using	namespace	std;
//struct	hasher{	size_t	operator()(const	string	&s)const{	return	wyhash(s.c_str(),s.size(),34432,_wyp);	}};
//struct	full_hasher{	size_t	operator()(void	*p,	uint64_t	len,	uint64_t	seed)const{	return	wyhash(p,len,seed,_wyp);	}};

struct	hasher{	size_t	operator()(const	string	&s)const{	return	XXH3_64bits_withSeed(s.c_str(),s.size(),34432);	}};
struct	full_hasher{	size_t	operator()(void	*p,	uint64_t	len,	uint64_t	seed)const{	return	XXH3_64bits_withSeed(p,len,seed);	}};

uint64_t	bench_hash(vector<string>	&v,	string	name){
	hasher	h;	full_hasher	f;
	timeval	beg,	end;	uint64_t	dummy=0,	N=v.size(),	R=0x10000000ull/N;
	cout.precision(2);	cout.setf(ios::fixed);	cout<<name<<(name.size()<8?"\t\t":"\t");
	for(size_t  i=0;    i<N;    i++)    dummy+=h(v[i]);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=h(v[i]);
	gettimeofday(&end,NULL);
	cout<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	phmap::flat_hash_map<string,unsigned,hasher>	ma;
	for(size_t	i=0;	i<N;	i++)	ma[v[i]]++;
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=ma[v[i]]++;
	gettimeofday(&end,NULL);
	cout<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	char	temp[128];
	gettimeofday(&beg,NULL);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Modify here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++){	dummy+=f(temp,dummy&31,i);	(*temp)++;	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gettimeofday(&end,NULL);
	cout<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	string	s;	
	s.resize(1024);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<(1ull<<26);	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*(1ull<<26)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	s.resize(0x40000ull);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<(1ull<<20);	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*(1ull<<20)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	s.resize(0x1000000ull);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<4096;	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*4096*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	s.resize(0x40000000ull);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<64;	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*64*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\n";
	return	dummy;
}

int	main(int	ac,	char	**av){
	string	file="/usr/share/dict/words";
	if(ac>1)	file=av[1];
	vector<string>	v;	string	s;
	ifstream	fi(file.c_str());
	for(fi>>s;	!fi.eof();	fi>>s)	if(s.size())	v.push_back(s);
	fi.close();
	uint64_t	r=0;
	cout<<"Benchmarking\t"<<file<<'\n';
	cout<<"HashFunction\tWords\tHashmap\tRand32\t1K\t256K\t16M\t1G\n";
	r+=bench_hash(v,"");
	return	r;
}
