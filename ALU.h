#include <bits/stdc++.h>
#include "Register.h"
using namespace std;
class ALU {
public:
    string hexToDec(string hexValue);

    string decToHex(int num);

    void add(int idx1, int idx2, int idx3, Register& reg);
};



