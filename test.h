static inline uint64_t r8(const uint8_t *p) { uint64_t v; memcpy(&v,  p,  8); return  v; } 
static inline uint64_t r4(const uint8_t *p) { unsigned v; memcpy(&v,  p,  4); return  v; } 
static inline uint64_t r3(const uint8_t *p, unsigned k) {  return (((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1]; }
static inline uint64_t wyhash(const void* key, uint64_t len, uint64_t seed) {
 const uint8_t *p=(const uint8_t*)key; uint64_t i=len&63;
 if(!i) { }
 else if(i<4) seed=mum(r3(p,i)^seed^p0,seed^p1);
 else if(i<=8) seed=mum(r4(p)^seed^p0,r4(p+i-4)^seed^p1);
 else if(i<=16) seed=mum(r8(p)^seed^p0,r8(p+i-8)^seed^p1);
 else if(i<=24) seed=mum(r8(p)^seed^p0,r8(p+8)^seed^p1)^mum(r8(p+i-8)^seed^p2,seed^p3);
 else if(i<=32) seed=mum(r8(p)^seed^p0,r8(p+8)^seed^p1)^mum(r8(p+16)^seed^p2,r8(p+i-8)^seed^p3);
 else seed=mum(r8(p)^seed^p0,r8(p+8)^seed^p1)^mum(r8(p+16)^seed^p2,r8(p+24)^seed^p3)
          ^mum(r8(p+i-32)^seed^p1,r8(p+i-24)^seed^p2)^mum(r8(p+i-16)^seed^p3,r8(p+i-8)^seed^p0);
 if(i==len) return mum(seed,len^p4);
 uint64_t see1=seed, see2=seed, see3=seed;
 for(p+=i,i=len-i; _like_(i>=64); i-=64,p+=64) {
  seed=mum(r8(p)^seed^p0,r8(p+8)^seed^p1);  see1=mum(r8(p+16)^see1^p2,r8(p+24)^see1^p3); 
  see2=mum(r8(p+32)^see2^p1,r8(p+40)^see2^p2); see3=mum(r8(p+48)^see3^p3,r8(p+56)^see3^p0); 
 }
 return mum(seed^see1^see2,see3^len^p4);
}
