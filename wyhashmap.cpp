#include	<vector>
#include	"wyhash.h"
using	namespace	std;

template <typename KeyType, typename ValueType, typename Hasher, size_t	log2capa>
struct	wyhashmap{
	const	size_t	mask=(1ull<<log2capa)-1;
	vector<std::pair<uint64_t,ValueType>	>	data;
	wyhashmap(){	data.resize(1ull<<log2capa);	}
	void	clear(void){	std::vector<std::pair<uint64_t,ValueType> >(1ull<<log2capa).swap(data);	}
	ValueType&	operator[](KeyType	&key){
		Hasher	hasher;
		size_t	i=1; uint64_t	s;	do{	s=hasher(key,i);	i++;	}while(_unlikely_(!s));
		for(i=hasher(key,0)&mask;data[i].first&&data[i].first!=s;i=(i+1)&mask);
		if(!data[i].first)	data[i].first=s;	
		return	data[i].second;
	}
	size_t	find(KeyType  &key){
		Hasher	hasher;
		size_t	i=1; uint64_t	s;	do{	s=hasher(key,i);	i++;	}while(_unlikely_(!s));
		for(i=hasher(key,0)&mask;data[i].first&&data[i].first!=s;i=(i+1)&mask);
		if(!data[i].first)	return	1ull<<log2capa;
		return	i;
	}
};
