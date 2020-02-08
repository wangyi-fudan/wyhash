static inline uint64_t _wyhash(const void* key, uint64_t len, uint64_t seed, const uint64_t s[6]) {
 const uint8_t *p=(const uint8_t*)key; uint64_t i=len; seed^=s[4];
 if(_like_(i<=64)){
  label:
  if(_like_(i>=8)){
   if(_like_(i<=16)) return  _wymum(_wyr8(p)^s[0],_wyr8(p+i-8)^seed);
   else if(_like_(i<=32)) 
    return  _wymum(_wyr8(p)^s[0],_wyr8(p+8)^seed)^_wymum(_wyr8(p+i-16)^s[1],_wyr8(p+i-8)^seed);
   else return _wymum(_wyr8(p)^s[0],_wyr8(p+8)^seed)^_wymum(_wyr8(p+16)^s[1],_wyr8(p+24)^seed)
   ^_wymum(_wyr8(p+i-32)^s[2],_wyr8(p+i-24)^seed)^_wymum(_wyr8(p+i-16)^s[3],_wyr8(p+i-8)^seed);
  }
  else{
   if(_like_(i>=4)) return  _wymum(_wyr4(p)^s[0],_wyr4(p+i-4)^seed);
   else return _wymum((_like_(i)?_wyr3(p,i):0)^s[0],seed);
  }
 }
 uint64_t see1=seed, see2=seed, see3=seed;
 for(; i>=64; i-=64,p+=64){
  seed=_wymum(_wyr8(p)^s[0],_wyr8(p+8)^seed);  see1=_wymum(_wyr8(p+16)^s[1],_wyr8(p+24)^see1);
  see2=_wymum(_wyr8(p+32)^s[2],_wyr8(p+40)^see2); see3=_wymum(_wyr8(p+48)^s[3],_wyr8(p+56)^see3);
 }
 seed^=see1^see2^see3;
 goto label;
}
static inline uint64_t wyhash(const void* key, uint64_t len, uint64_t seed, const uint64_t s[6]) {
 return _wymum(_wyhash(key,len,seed,s),len^s[5]);
}
