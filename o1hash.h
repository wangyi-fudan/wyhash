/*
  Author: Wang Yi <godspeed_china@yeah.net>
  This is a quick and dirty hash function designed for O(1) speed.
  It makes your hash table application fly in most cases.
  It samples first, middle and last 4 bytes to produce the hash.
  Do not use it in any serious applications as it's not secure.
*/
static inline uint64_t o1hash(const void *key, size_t len) {
  const uint8_t *p=(const uint8_t*)key;
  if(len>=4) {
    unsigned first, middle, last;
    memcpy(&first,p,4);
    memcpy(&middle,p+(len>>1)-2,4);
    memcpy(&last,p+len-4,4);
    return (uint64_t)(first+last)*middle;
  }
  if(len){
    uint64_t tail=((((unsigned)p[0])<<16) | (((unsigned)p[len>>1])<<8) | p[len-1]);
    return tail*tail*tail;
  }
  return  0;
}
