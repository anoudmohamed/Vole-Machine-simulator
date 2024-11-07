#pragma once
#include <iostream>
using namespace std;

class Register {
    string memory[16] = {"00", "00", "00", "00", "00", "00", "00", "00", "00"
            ,"00", "00", "00", "00", "00", "00", "00"};
    int size = 16;
public:
    string getCell(const int address);
    void setCell(const int address,const string & value);
};



