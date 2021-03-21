#include  <vector>
#include  "wyhash.h"

namespace  wy{
template <typename KeyType, typename ValueType, typename Hasher, typename Equal=std::equal_to<KeyType>  >
class  hashmap{
private:
  uint64_t  mask;
  void  double_size(void){
    mask=(capa*2)-1;
    std::vector<std::pair<KeyType,ValueType>  >  data1(mask+1);
    std::vector<uint8_t>  flag1(mask+1);
    Hasher  hasher;
    for(size_t  o=0;  o<capa;  o++)  if(flag[o]){
      uint64_t  h0=hasher(data[o].first), h=h0, i;  uint8_t  f=h>>56;
      for(uint64_t  i=0;  !f;  i++){  h=wyhash64(h0,i);  f=h>>56;  }
      for(i=h&mask;flag1[i];i=(i+1)&mask);
      flag1[i]=f;  data1[i]=std::move(data[o]);
    }
    capa*=2;  swap(data,data1);  swap(flag,flag1);
  }
public:
  std::vector<std::pair<KeyType,ValueType>  >  data;
  std::vector<uint8_t>  flag;	// non-zero indicates used; zero indicates empty
  uint64_t  capa, size;

  hashmap(size_t  log2capacity=4){  
    capa=1ull<<log2capacity; if(capa<16) capa=16;  mask=capa-1;  
    data.resize(capa);  flag.resize(capa);
    size=0;
  }

  void  clear(void){
    std::vector<uint8_t>(capa).swap(flag);
    std::vector<std::pair<KeyType,ValueType> >(capa).swap(flag);
    size=0;
  }

  ValueType&  operator[](KeyType  &key){
    Hasher  hasher; Equal equal; 
    uint64_t  h0=hasher(key), h=h0, i;  uint8_t  f=h>>56;
    for(uint64_t  i=0;  !f;  i++){  h=wyhash64(h0,i);  f=h>>56;  }
    for(i=h&mask;flag[i]&&(flag[i]!=f||!equal(data[i].first,key));i=(i+1)&mask);
    if(flag[i])  return  data[i].second;
    if(size<0.9*capa){  flag[i]=f;  data[i].first=key;  size++;  return  data[i].second;  }
    double_size();
    for(i=h&mask;flag[i];i=(i+1)&mask);
    flag[i]=f;  data[i].first=key;  size++;  return  data[i].second;
  }

  // return capa if not found
  uint64_t find(KeyType &key){
    Hasher  hasher; Equal equal; 
    uint64_t  h0=hasher(key), h=h0, i;  uint8_t  f=h>>56;
    for(uint64_t  i=0;  !f;  i++){  h=wyhash64(h0,i);  f=h>>56;  }
    for(i=h&mask;flag[i]&&(flag[i]!=f||!equal(data[i].first,key));i=(i+1)&mask);
    return flag[i]?i:capa;
  }

  void erase(uint64_t pos){ if(pos<capa&&flag[pos]){ flag[pos]=0; std::pair<KeyType,ValueType>().swap(data[pos]); size--; }  }

};
}
