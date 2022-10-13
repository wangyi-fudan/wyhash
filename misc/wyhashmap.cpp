#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "wyhash.h"

/*  This is world's fastest hash map: 2x faster than bytell_hash_map.
    It does not store the keys, but only the hash/signature of keys.
    First we use pos=hash1(key) to approximately locate the bucket.
    Then we search signature=hash2(key) from pos linearly.
    If we find a bucket with matched signature we report the bucket
    Or if we meet a bucket whose signature=0, we report a new position to insert
    The signature collision probability is very low as we usually searched N~10 buckets.
    By combining hash1 and hash2, we acturally have 128 bit anti-collision strength.
    hash1 and hash2 can be the same function, resulting lower collision resistance but faster.
    The signature is 64 bit, but can be modified to 32 bit if necessary for save space.
    The above two can be activated by define WYHASHMAP_WEAK_SMALL_FAST
    simple examples:
*/

#ifdef WYHASHMAP_WEAK_SMALL_FAST // for small hashmaps whose size < 2^24 and acceptable collision
typedef uint32_t wyhashmap_t;
#else
typedef uint64_t wyhashmap_t;
#endif

///static inline size_t wyhashmap(wyhashmap_t *idx, size_t idx_size, const void *key, size_t key_size, uint8_t insert, uint64_t *secret){
static inline size_t wyhashmap(wyhashmap_t *idx, size_t idx_size, const void *key, size_t key_size, uint8_t insert, const uint64_t secret[]){
    size_t i=1; uint64_t h2; wyhashmap_t sig;
    do{ sig=h2=wyhash(key,key_size,i,secret); i++; }while(_unlikely_(!sig));
#ifdef WYHASHMAP_WEAK_SMALL_FAST
    size_t i0=wy2u0k(h2,idx_size);
#else
    size_t i0=wy2u0k(wyhash(key,key_size,0,secret),idx_size);
#endif
    for(i=i0; i<idx_size&&idx[i]&&idx[i]!=sig; i++);
    if(_unlikely_(i==idx_size)){
        for(i=0; i<i0&&idx[i]&&idx[i]!=sig;  i++);
        if(i==i0) return idx_size;
    }
    if(!idx[i]){
        if(insert) idx[i]=sig;
        else return idx_size;
    }
    return i;
}
//#endif

#if 1 //WYHASHMAP_TEST
int main()
{
    const size_t size = 213432;
    std::vector<wyhashmap_t> idx(size); // allocate the index of fixed size. idx MUST be zeroed.
    std::vector<value_class> value(size); // we only care about the index, user should maintain his own value vectors.
    std::string key = "dhskfhdsj"; // the object to be inserted into idx
    size_t pos = wyhashmap(idx.data(), idx.size(), key.c_str(), key.size(), 1, _wyp); // get the position and insert
    if(pos<size)
        value[pos]++; // we process the vallue
    else
        std::cerr<<"map is full\n";
    pos = wyhashmap(idx.data(), idx.size(), key.c_str(), key.size(), 0, _wyp); // just lookup by setting insert=0
    if(pos<size)
        value[pos]++; // we process the vallue
    else
        std::cerr<<"the key does not exist\n";
}
#endif /* WYHASHMAP_TEST */

