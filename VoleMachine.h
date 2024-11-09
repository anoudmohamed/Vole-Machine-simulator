#ifndef VOLE_MACHINE_H
#define VOLE_MACHINE_H

#include <bits/stdc++.h>
using namespace std;

class Memory {
    string memory[256] = { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"};
    int size = 256;
public:
    string getCell(const int address);
    void setCell(const int address, const string & value);
    Memory& reset();
};

class Register {
    string memory[16] = { "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00" };
    int size = 16;
public:
    string getCell(const int address);
    void setCell(const int address, const string & value);
    void reset();
};

class ALU {
public:
    string hexToDec(string hexValue);
    string decToHex(int num);
    string add(int idx1, int idx2, int idx3, Register &reg);
};

class CU {
public:
    static bool haltFlag;
    static void load(const int REG, int MEM_AD_h_to_d, Register& register_, Memory& memory);
    static void load(const int REG, const string & MEM_h_to_d, Register& register_);
    static void print_and_restore(const int REG, Register &register_, Memory &memory);
    static void store(const int REG, const int MEM, Register& register_, Memory &memory);
    static void move(const int R, const int S, Register& register_);
    static void jump(const int R, const int value, Register& register_, int & ProgramCounter, int & jumpCount);
    static void halt();
};

class CPU {
    static int ProgramCounter;
    static int jumpCount;
    CU cu;
    ALU alu_;
    Register register_;
    Memory memory_;
public:
    string InstructionRegister;
    void Fetch(Memory& memory);
    void Decode_And_Execute();
    int getProgramcounter();
    void resetRegisters();
    void resetMemory();
    void setMemory(const Memory& memory);
    Register& getRegister();
    static void resetProgramCounter();
    static void restjumpcount();
};

class Machine {
    CPU cpu;
    Memory memory;
    Register register_;
    vector<string> program;
    static int i;
public:
    void loadProgramFile();
    void resetIndex();
    void run_whole();
    void run_step_by_step();
    void loadProgramToMemory(const string& Instruction);
    void outputMemory();
    void outputRegister();
};

class MainUI {
    Machine machine;
public:
    void start();
    bool detect_choice();
    static char inputChoice();
    static void displayMenu();
};

#endif // VOLE_MACHINE_H
