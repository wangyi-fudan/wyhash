// Author: Wang Yi <godspeed_china@yeah.net>
#include <stdint.h>
#include <string.h>
static inline uint64_t FastestHash(const void *key, size_t len) {
  const uint8_t *p = (const uint8_t *)key;
  if(len>=4) {
    unsigned  first,  middle,  last;
    memcpy(&first,p,4);
    memcpy(&middle,p+(len>>1)-2,4);
    memcpy(&last,p+len-4,4);
    return  (uint64_t)(first+last)*middle;
  }
  if(len)  return  ((((unsigned)p[0])<<16) | (((unsigned)p[len>>1])<<8) | p[len-1])*0xa0761d6478bd642full;
  return  0;
}
