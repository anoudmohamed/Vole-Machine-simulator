
#include "Memory.h"

string Memory::getCell(const int address) {
    if (address >= 0 && address < size) {
        return memory[address];
    }
    cout << "Error: invalid address" << endl;
}
void Memory::setCell(const int address,const string & value) {
    if (address >= 0 && address < size) {
        memory[address] = value;
    }
    else {
        cout << "Error: invalid address" << endl;
    }
}