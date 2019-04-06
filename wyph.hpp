//Author:	Wang Yi
#include	<algorithm>
#include	<vector>
#include	<cstdio>

template	<class	Type,	class	Hash,	unsigned	Bits>
class	wyph{
public:
	unsigned char	keys[1u<<Bits];
	unsigned char	estimate(const	Type	*P,	unsigned	N);
public:
	//return 0 if fails (try to increase Bits), otherwise return maximum key used	
	unsigned	construct(const	Type    *P, unsigned    N);

	bool	save(const	char	*F){
		FILE	*f=fopen(F,	"wb");
		if(f==NULL)	return	false;
		unsigned	n=Bits;	fwrite(&n,	4,	1,	f);	fwrite(keys,	(1u<<Bits)*sizeof(unsigned char),	1,	f);
		fclose(f);
		return	true;
	}

	bool	load(const	char	*F){
		FILE	*f=fopen(F,	"rb");
		if(f==NULL)	return	false;
		unsigned	n;	if(fread(&n,	4,	1,	f)!=1)	return	false;	if(fread(keys,	(1u<<Bits)*sizeof(unsigned char),	1,	f)!=1)	return	false;
		fclose(f);
		return	true;
	}

	inline	unsigned	operator()(const	Type	&T){
		Hash	h;	unsigned long long	a=h(T,0),	b=h(T,keys[a>>(64-Bits)]);
		return	((a>>(64-Bits))<<(32-Bits))|(b&((1u<<(32-Bits))-1u));
	}
};

template	<class	Type,	class	Hash,	unsigned	Bits>
unsigned char	wyph<Type,Hash,Bits>::estimate(const	Type	*P,	unsigned	N){
	unsigned	*p=new	unsigned[N],	r=0;	Hash	h;
	for(unsigned char	i=1;	i;	i++){
		for(unsigned	j=0;	j<N;	j++)	p[j]=h(P[j],i)&((1u<<(32-Bits))-1u);
		std::sort(p,	p+N);	bool	d=false;
		for(unsigned	j=1;	j<N;	j++)	if(p[j]==p[j-1]){	d=true;	break;	}
		if(!d){	r=i;	break;	}
	}
	delete	[]	p;
	return	r;
}

template	<class	Type,	class	Hash,	unsigned	Bits>
unsigned	wyph<Type,Hash,Bits>::construct(const	Type    *P, unsigned    N){
	std::vector<Type>	v[1u<<Bits];	Hash	h;
	for(unsigned	i=0;	i<N;	i++)	v[h(P[i],0)>>(64-Bits)].push_back(P[i]);
	#pragma omp parallel for
	for(unsigned	i=0;	i<(1u<<Bits);	i++)	keys[i]=v[i].size()?estimate(v[i].data(),	v[i].size()):1;
	unsigned char	m=1;
	for(unsigned    i=0;    i<(1u<<Bits);   i++)	if(!keys[i])	return	0;	else	if(keys[i]>m)	m=keys[i];
	return	m;
}
/*	example code
#include	<iostream>
#include	<vector>
#include	"wyhash.h"
using	namespace	std;

struct	Hasher{
	unsigned long long	operator()(const	string	&K,	unsigned long long	S){	return	wyhash(K.c_str(),	K.size(),	S);	}
};

int	main(void){
	vector<string>	v;	string	s;
	for(cin>>s;	!cin.eof();	cin>>s)	v.push_back(s);
	wyph<string,	Hasher,	17>	ph;
	cout<<ph.construct(v.data(),	v.size())<<'\n';
	vector<unsigned>	u(v.size());
	for(size_t	i=0;	i<v.size();	i++)	u[i]=ph(v[i]);
	sort(u.begin(),	u.end());
	unsigned	d=0;
	for(size_t	i=1;	i<u.size();	i++)	d+=(u[i]==u[i-1]);
	cout<<d<<'\n';
	ph.save("biomedical.wyph");
	return	0;
}
*/
