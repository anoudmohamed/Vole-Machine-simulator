#pragma once
#include <iostream>
using namespace std;

class Memory {

    string memory[256] = { "00", "00", "00", "00", "00", "00", "00", "00"
            ,"00", "00", "00", "00", "00", "00", "00", "00", "00", "00"};
    int size = 256;
public:
    string getCell(const int address);
    void setCell(const int address,const string & value);
};




