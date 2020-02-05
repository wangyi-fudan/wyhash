#include	"parallel-hashmap/parallel_hashmap/phmap.h"
#include	"wyhash/wyhash.h"
#include	"xxHash/xxhash.c"
#include	"t1ha/t1ha.h"
#include	<sys/time.h>
#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<vector>
using	namespace	std;
uint64_t	secret[6];
struct	wy{	size_t	operator()(const	string	&s)const{	return	wyhash(s.c_str(),s.size(),34432,secret);	}};
struct	xx{	size_t	operator()(const	string	&s)const{	return	XXH64(s.c_str(),s.size(),34432);	}};
struct	xx3{	size_t	operator()(const	string	&s)const{	return	XXH3_64bits_withSeed(s.c_str(),s.size(),34432);	}};
struct	t1ha2{	size_t	operator()(const	string	&s)const{	return	t1ha2_atonce(s.c_str(),s.size(),34432);	}};

template	<typename	Hasher>
uint64_t	bench_hash(vector<string>	&v,	string	name){
	Hasher	h;
	timeval	beg,	end;	uint64_t	dummy=0,	N=v.size(),	R=0x10000000ull/N;
	cout.precision(2);	cout.setf(ios::fixed);	cout<<name<<(name.size()<8?"\t\t":"\t");
	for(size_t  i=0;    i<N;    i++)    dummy+=h(v[i]);
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=h(v[i]);
	gettimeofday(&end,NULL);
	cout<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	phmap::flat_hash_map<string,unsigned,Hasher>	ma;
	for(size_t	i=0;	i<N;	i++)	ma[v[i]]++;
	gettimeofday(&beg,NULL);
	for(size_t  r=0;    r<R;    r++)	for(size_t	i=0;	i<N;	i++)	dummy+=ma[v[i]]++;
	gettimeofday(&end,NULL);
	cout<<1e-6*R*N/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	string	s;	
	s.resize(0x10000ull);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<(1ull<<18);	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*(1ull<<18)*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\t";
	s.resize(0x1000000ull);	dummy+=h(s);
	gettimeofday(&beg,NULL);
	for(size_t	r=0;	r<1024;	r++){	dummy+=h(s);	s[0]++;	}
	gettimeofday(&end,NULL);
	cout<<1e-9*1024*s.size()/(end.tv_sec-beg.tv_sec+1e-6*(end.tv_usec-beg.tv_usec))<<"\n";
	return	dummy;
}

int	main(int	ac,	char	**av){
	make_secret(time(NULL),secret);
	vector<string>	v;	string	s;
	ifstream	fi("/usr/share/dict/words");
	for(fi>>s;	!fi.eof();	fi>>s)	v.push_back(s);
	fi.close();
	uint64_t	r=0;
	for(size_t	i=v.size();	i;	i--)	swap(v[i],v[wyrand(&r)%(i+1)]);
	cout<<"HashFunction\tWords\tHashmap\tBulk64K\tBulk16M\n";
	r+=bench_hash<std::hash<string>	>(v,"std::hash");
	r+=bench_hash<wy>(v,"wyhash");
	r+=bench_hash<xx>(v,"xxHash64");
	r+=bench_hash<xx3>(v,"XXH3_scalar");
	r+=bench_hash<t1ha2>(v,"t1ha2_atonce");
	return	r;
}
