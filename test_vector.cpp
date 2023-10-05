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
    uint64_t hash;
    cout << "# wyhash         message,  seed" << "\n";
    for (size_t i = 0; i < msgs_v.size(); i++) {
        hash = wyhash(msgs_v[i].c_str(), msgs_v[i].size(), i, _wyp);
        cout << hex << hash << " \"" << msgs_v[i] << "\",  " << i << "\n";
    }
    return 0;
}
