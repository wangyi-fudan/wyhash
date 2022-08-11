#include <stdint.h>
#include <iostream>
#include <vector>
#define WYTRNG
#include "wyhash.h"
using namespace std;

int main(void) {
    vector<string> msgs_v = {
        "",
        "a",
        "abc",
        "message digest",
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
        "1234567890123456789012345678901234567890123456789012345678901234567890"
        "1234567890"
    };
    vector<uint64_t> etalons_v = {
        0x42bc986dc5eec4d3,
        0x84508dc903c31551,
        0x0bc54887cfc9ecb1,
        0x6e2ff3298208a67c,
        0x9a64e42e897195b9,
        0x9199383239c32554,
        0x7c1ccf6bba30f5a5
    };
    uint64_t hash;
    for (size_t i = 0; i < msgs_v.size(); i++) {
        hash = wyhash(msgs_v[i].c_str(), msgs_v[i].size(), i, _wyp);
        cout << "wyhash(\"" << msgs_v[i] << "\"," << i << ")=" << hex  << hash << hex << "\n";
    }
    return 0;
}
