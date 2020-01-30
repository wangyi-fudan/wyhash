#include	"wyhash.h"
#include	<iostream>
#include	<vector>
using	namespace	std;

int	main(void){
	vector<string>	v={"","a","abc","message digest","abcdefghijklmnopqrstuvwxyz","ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789","12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
	for(size_t	i=0;	i<v.size();	i++){
		cout<<"wyhash(\""<<v[i]<<"\","<<i<<")="<<hex<<wyhash(v[i].c_str(),v[i].size(),i)<<'\n';
	}
	return	0;
}
