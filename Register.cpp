
#include "Register.h"

string Register::getCell(const int address) {
    if (address >= 0 && address < size) {
        return memory[address];
    }
    cout << "Invalid address!";
}
void Register::setCell(const int address,const string & value) {
    if (address >= 0 && address < size) {
        memory[address] = value;
    }
    else {
        cout << "Invalid address!";
    }
}