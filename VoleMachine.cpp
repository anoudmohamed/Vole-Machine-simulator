#include "VoleMachine.h"

string Memory::getCell(const int address) {
    if (address >= 0 && address < size) {
        return memory[address];
    }
    cout << "Error: invalid address" << endl;
    return "";
}

void Memory::setCell(const int address, const string & value) {
    if (address >= 0 && address < size) {
        memory[address] = value;
    } else {
        cout << "Error: invalid address" << endl;
    }
}

Memory& Memory::reset() {
    for (int i = 0; i < size; ++i) {
        memory[i] = "00";
    }
    return *this;
}

string Register::getCell(const int address) {
    if (address >= 0 && address < size) {
        return memory[address];
    }
    cout << "Invalid address!";
    return "";
}

void Register::setCell(const int address, const string & value) {
    if (address >= 0 && address < size) {
        memory[address] = value;
    } else {
        cout << "Invalid address!";
    }
}

void Register::reset() {
    for (int i = 0; i < size; ++i) {
        memory[i] = "00";
    }
}

string ALU::hexToDec(string hexValue) {
    int decValue = 0;
    int base = 1;

    for (int i = hexValue.size() - 1; i >= 0; i--) {
        if (hexValue[i] >= '0' && hexValue[i] <= '9') {
            decValue += (int(hexValue[i]) - '0') * base;
        } else if (hexValue[i] >= 'A' && hexValue[i] <= 'F') {
            decValue += (int(hexValue[i]) - 'A' + 10 ) * base;
        }
        base *= 16;
    }

    return to_string(decValue);
}

string ALU::decToHex(int num) {
    if (num == 0) {
        return "00";
    }

    string hexDeciNum;
    while (num != 0) {
        int temp = num % 16;
        if (temp < 10) {
            hexDeciNum += (temp + '0');
        } else {
            hexDeciNum += (temp + 'A' - 10);
        }
        num /= 16;
    }
    reverse(hexDeciNum.begin(), hexDeciNum.end());

    if (hexDeciNum.size() == 1) {
        hexDeciNum = "0" + hexDeciNum;
    }
    return hexDeciNum;
}

string ALU::add(int idx1, int idx2, int idx3, Register &reg) {
    bool isFloatingPoint = (reg.getCell(idx1).length() == 4 && reg.getCell(idx2).length() == 4);

    if (isFloatingPoint) {
        int intPart1 = stoi(hexToDec(reg.getCell(idx1).substr(0, 2)));
        int fracPart1 = stoi(hexToDec(reg.getCell(idx1).substr(2, 2)));
        int intPart2 = stoi(hexToDec(reg.getCell(idx2).substr(0, 2)));
        int fracPart2 = stoi(hexToDec(reg.getCell(idx2).substr(2, 2)));

        int resIntPart = intPart1 + intPart2;
        int resFracPart = fracPart1 + fracPart2;

        if (resFracPart >= 100) {
            resIntPart += resFracPart / 100;
            resFracPart = resFracPart % 100;
        }

        string result = decToHex(resIntPart) + decToHex(resFracPart);
        reg.setCell(idx3, result);
        return result;
    } else {
        int value1 = stoi(hexToDec(reg.getCell(idx1)));
        int value2 = stoi(hexToDec(reg.getCell(idx2)));
        int result = value1 + value2;

        if (result >= 256) {
            result -= 256;
        } else if (result < 0) {
            result += 256;
        }

        string resultHex = decToHex(result);
        reg.setCell(idx3, resultHex);
        return resultHex;
    }
}

bool CU::haltFlag = false;

void CU::load(const int REG, int MEM_AD_h_to_d, Register& register_, Memory& memory) {
    register_.setCell(REG, memory.getCell(MEM_AD_h_to_d));
}

void CU::load(const int REG, const string & MEM_h_to_d, Register& register_) {
    register_.setCell(REG, MEM_h_to_d);
}

void CU::print_and_restore(const int REG, Register &register_, Memory &memory) {
    memory.setCell(0, register_.getCell(REG));
    string op = memory.getCell(0);

    int value = stoi(op, nullptr, 16);
    if (value >= 0 && value <= 127) {
        cout << "The value of register " << REG << " in hex: " << register_.getCell(REG)
             << " in ASCII: " << char(value) << endl;
    } else {
        cout << "The value of register " << REG << " in hex: " << register_.getCell(REG)
             << " is not a valid ASCII character." << endl;
    }
}

void CU::store(const int REG, const int MEM, Register& register_, Memory &memory) {
    memory.setCell(MEM, register_.getCell(REG));
}

void CU::move(const int R, const int S, Register& register_) {
    register_.setCell(S, register_.getCell(R));
}

void CU::jump(const int R, const int value, Register& register_, int & ProgramCounter, int & jumpCount) {
    if (register_.getCell(R) == register_.getCell(0)) {
        if (jumpCount < 20) {
            ProgramCounter = value;
            jumpCount++;
        } else {
            cout << "Warning: Jump limit exceeded to prevent infinite loop" << endl;
        }
    }
}

void CU::halt() {
    cout << endl << "The Execute Will Stop" << endl << endl;
    haltFlag = true;
}

int CPU::ProgramCounter = 10;
int CPU::jumpCount = 0;

void CPU::Fetch(Memory& memory) {
    InstructionRegister = memory.getCell(ProgramCounter++);
    InstructionRegister += memory.getCell (ProgramCounter);
    ++ProgramCounter;
    Decode_And_Execute();
}

void CPU::Decode_And_Execute() {
    if (InstructionRegister[0] == '1') {
        const string XY = alu_.hexToDec(InstructionRegister.substr(2));
        const int R = (InstructionRegister[1] - '0');
        CU::load(R, stoi(XY), register_, memory_);
    } else if (InstructionRegister[0] == '2') {
        const string XY = InstructionRegister.substr(2);
        const int R = (InstructionRegister[1] - '0');
        CU::load(R, XY, register_);
    } else if (InstructionRegister[0] == '3') {
        if (InstructionRegister.substr(2) == "00") {
            const int R = (InstructionRegister[1] - '0');
            CU::print_and_restore(R, register_, memory_);
        } else {
            const string XY = alu_.hexToDec(InstructionRegister.substr(2));
            const int R = (InstructionRegister[1] - '0');
            CU::store(R, stoi(XY), register_, memory_);
        }
    } else if (InstructionRegister[0] == '4') {
        const int num1 = (InstructionRegister[2] - '0');
        const int num2 = (InstructionRegister[3] - '0');
        CU::move(num1, num2, register_);
    } else if (InstructionRegister[0] == '5' || InstructionRegister[0] == '6') {
        const int R = (InstructionRegister[1] - '0');
        const int X = (InstructionRegister[2] - '0');
        const int Y = (InstructionRegister[3] - '0');
        alu_.add(X, Y, R, register_);
    } else if (InstructionRegister[0] == 'B') {
        const string XY = alu_.hexToDec(InstructionRegister.substr(2));
        const int R = (InstructionRegister[1] - '0');
        CU::jump(R, stoi(XY), register_, ProgramCounter, jumpCount);
    } else if (InstructionRegister[0] == 'C') {
        CU::halt();
    }
}

int CPU::getProgramcounter() {
    return ProgramCounter;
}

void CPU::resetRegisters() {
    register_.reset();
}

void CPU::resetMemory() {
    memory_.reset();
}

void CPU::setMemory(const Memory& memory) {
    memory_ = memory;
}

Register& CPU::getRegister() {
    return register_;
}

void CPU::resetProgramCounter() {
    ProgramCounter = 0;
}

void CPU::restjumpcount() {
    jumpCount = 0;
}

void Machine::loadProgramFile() {
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);
    ifstream file(filename);

    while (!file.is_open()) {
        cout << "There was an error opening the file: " << filename << endl;
        cout << "Please enter a valid file name: ";
        getline(cin, filename);
        file.clear();
        file.open(filename);
    }

    cpu.resetMemory();
    resetIndex();
    program.clear();
    string instruction;
    while (getline(file, instruction)) {
        program.push_back(instruction);
        loadProgramToMemory(instruction);
    }
    if ((program.size() > 0) && (program[program.size() - 1] != "C000")) {
        program.push_back("C000");
        loadProgramToMemory("C000");
    }

    file.close();
    if (program.empty()) {
        cout << "The file is empty or no instructions were found." << endl;
    }
}

void Machine::resetIndex() {
    i = 10;
}

void Machine::run_whole() {
    cpu.resetRegisters();
    CPU::resetProgramCounter();
    CU::haltFlag = false;
    CPU::restjumpcount();
    while (!CU::haltFlag) {
        cpu.Fetch(memory);
    }
    cout << "Program counter after fetch: " << cpu.getProgramcounter() << endl;
    outputMemory();
    outputRegister();
}

void Machine::run_step_by_step() {
    cpu.resetRegisters();
    CPU::resetProgramCounter();
    CU::haltFlag = false;
    CPU::restjumpcount();
    while (!CU::haltFlag) {
        cpu.Fetch(memory);
        cout << "Program counter after fetch: " << cpu.getProgramcounter() << endl;
        outputMemory();
        outputRegister();
        char ch;
        cout << "Please enter any character to continue: ";
        cin >> ch;
    }
    cout << "All Memory Execute and Decode (step by step) till found \"C000\", BYE..." << endl << endl;
}

void Machine::loadProgramToMemory(const string& Instruction) {
    memory.setCell(i++, Instruction.substr(0, 2));
    memory.setCell(i++, Instruction.substr(2));
    cpu.setMemory(memory); // Set memory for CPU
}

void Machine::outputMemory() {
    cout << "Memory: " << endl;
    for (int j = 0; j < 256; j++) {
        cout << memory.getCell(j) << " ";
    }
    cout << "\n";
}

void Machine::outputRegister() {
    cout << "Register: " << endl;
    Register& reg = cpu.getRegister();
    for (int j = 0; j < 16; j++) {
        cout << reg.getCell(j) << " ";
    }
    cout << "\n";
}

int Machine::i = 10;

void MainUI::start() {
    cout << "Welcome to the Vole Machine!" << endl;
    while (true) {
        if (!detect_choice()) {  // Exit if detect_choice returns false
            cout << "Exiting program." << endl;
            break;
        }
    }
}

bool MainUI::detect_choice() {
    char choice;
    while (true) { // Loop until a valid option is chosen
        choice = inputChoice();
        if (choice == '1') {
            machine.loadProgramFile();
            machine.run_step_by_step();
            return true;
        }
        if (choice == '2') {
            machine.loadProgramFile();
            machine.run_whole();
            return true;
        }
        if (choice == '3') {
            return false; // Exit the program
        }
        cout << "Invalid choice! Please try again." << endl;
    }
}

char MainUI::inputChoice() {
    displayMenu();
    char choice;
    cin >> choice;
    cin.ignore(); // Ignore remaining newline character (if any)
    return choice;
}

void MainUI::displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Run step by step" << endl;
    cout << "2. Run whole" << endl;
    cout << "3. EXIT" << endl;
    cout << "Choose an option: ";
}

