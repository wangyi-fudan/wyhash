#include <iostream>
#include <vector>
#include "wyhash.h"
using namespace std;

int main(void) {
    vector<string> v = {
        "",
        "a",
        "abc",
        "message digest",
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
        "1234567890123456789012345678901234567890123456789012345678901234567890"
        "1234567890"};
    for (size_t i = 0; i < v.size(); i++) {
        cout << "wyhash(\"" << v[i] << "\"," << i << ")=" << hex
             << wyhash(v[i].c_str(), v[i].size(), i, _wyp) << '\n';
    }
    return 0;
}
