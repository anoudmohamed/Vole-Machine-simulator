# include <bits/stdc++.h>
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
        , "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00" };
    int size = 256;
public:
    string getCell(const int address) {
        if (address >= 0 && address < size) {
            return memory[address];
        }
        cout << "Error: invalid address" << endl;
    }
    void setCell(const int address,const string & value) {
        if (address >= 0 && address < size) {
            memory[address] = value;
        }
        else {
            cout << "Error: invalid address" << endl;
        }
    }
    // Reset all memory values to "00"
    Memory& reset() {
        for (int i = 0; i < size; ++i) {
            memory[i] = "00";
        }
        return *this; // Return reference to the current object
    }
};

class Register {
    string memory[16] = {"00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00"
        , "00", "00", "00", "00", "00"};
    int size = 16;
public:
    string getCell(const int address) {
        if (address >= 0 && address < size) {
            return memory[address];
        }
        cout << "Invalid address!";
    }
    void setCell(const int address,const string & value) {
        if (address >= 0 && address < size) {
            memory[address] = value;
        }
        else {
            cout << "Invalid address!";
        }
    }
    // Reset all register values to "00"
    void reset() {
        for (int i = 0; i < size; ++i) {
            memory[i] = "00";
        }
    }

};
class ALU {
public:
    string hexToDec(string hexValue) {
        int decValue = 0;
        int base = 1;

        for (int i = hexValue.size() - 1; i >= 0; i--) {
            if (hexValue[i] >= '0' && hexValue[i] <= '9') {
                decValue += (int(hexValue[i]) - '0') * base;
            } else if (hexValue[i] >= 'A' && hexValue[i] <= 'F') {
                decValue += (int(hexValue[i]) - 'A' + 10) * base;
            }
            base *= 16;
        }

        return to_string(decValue);
    }

    string decToHex(int num) {
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

    string add(int idx1, int idx2, int idx3, Register &reg) {
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
};
class CU {
public:
    // Initialize the halt flag
    static bool haltFlag;
     static void load(const int REG, int MEM_AD_h_to_d,Register& register_ ,Memory& memory){
        register_.setCell(REG, memory.getCell(MEM_AD_h_to_d));
    }
    static void load(const int REG, const string & MEM_h_to_d,Register& register_ ){
        register_.setCell(REG, MEM_h_to_d);
    }
    static void print_and_restore(const int REG, Register &register_, Memory &memory) {
         memory.setCell(0, register_.getCell(REG));
         string op = memory.getCell(0);

         // Convert hex to decimal
         int value = stoi(op, nullptr, 16); // Convert hex string to decimal integer

         // Check if value is within printable ASCII range
         if (value >= 0 && value <= 127) { // Only consider standard ASCII range
             cout << "The value of register " << REG << " in hex: " << register_.getCell(REG)
                  << " in ASCII: " << char(value) << endl;
         } else {
             cout << "The value of register " << REG << " in hex: " << register_.getCell(REG)
                  << " is not a valid ASCII character." << endl;
         }
     }
    static void store(const int REG,const int MEM,Register& register_, Memory &memory ){
        memory.setCell(MEM, register_.getCell(REG));
    }
    static void move(const int R, const int S,Register& register_ ){
        register_.setCell(S, register_.getCell(R));
    }
    static void jump(const int R, const int value, Register& register_, int & ProgramCounter, int & jumpCount) {
         if (register_.getCell(R) == register_.getCell(0)) {
             if (jumpCount < 20) {  // Limit jump executions to prevent infinite loop
                 ProgramCounter = value;
                 jumpCount++;
             } else {
                 cout << "Warning: Jump limit exceeded to prevent infinite loop" << endl;
             }
         }
     }

    static void halt(){
        cout << endl <<"The Execute Will Stop" << endl << endl;
         haltFlag = true;
    }

};// Initialize the halt flag
bool CU::haltFlag = false;

// CPU Class
class CPU {
    static int ProgramCounter;
    static int jumpCount;
    CU cu;
    ALU alu_;
    Register register_;
    Memory memory_;


public:
    string InstructionRegister;
    void Fetch(Memory& memory) {
        InstructionRegister = memory.getCell(ProgramCounter++);
        InstructionRegister += memory.getCell(ProgramCounter);
        ++ProgramCounter;
        Decode_And_Execute();
    }

    void Decode_And_Execute() {
        if (InstructionRegister[0] == '1') {
            const string XY = alu_.hexToDec(InstructionRegister.substr(2));
            const int R = (InstructionRegister[1] - '0');
            CU::load(R, stoi(XY), register_, memory_);
        }
        else if (InstructionRegister[0] == '2') {
            const string XY = InstructionRegister.substr(2);
            const int R = (InstructionRegister[1] - '0');
            CU::load(R, XY, register_);
        }
        else if (InstructionRegister[0] == '3') {
            if (InstructionRegister.substr(2) == "00") {
                const int R = (InstructionRegister[1] - '0');
                CU::print_and_restore(R, register_, memory_);
            }
            else {
                const string XY = alu_.hexToDec(InstructionRegister.substr(2));
                const int R = (InstructionRegister[1] - '0');
                CU::store(R, stoi(XY), register_, memory_);
            }
        }
        else if (InstructionRegister[0] == '4') {
            const int num1 = (InstructionRegister[2] - '0');
            const int num2 = (InstructionRegister[3] - '0');
            CU::move(num1, num2, register_);
        }
        else if (InstructionRegister[0] == '5' || InstructionRegister[0] == '6') {
            const int R = (InstructionRegister[1] - '0');
            const int X = (InstructionRegister[2] - '0');
            const int Y = (InstructionRegister[3] - '0');

            alu_.add(X, Y, R, register_);
        }
        else if (InstructionRegister[0] == 'B') {
            const string XY = alu_.hexToDec(InstructionRegister.substr(2));
            const int R = (InstructionRegister[1] - '0');
            CU::jump(R, stoi(XY), register_, ProgramCounter, jumpCount);
        }

        else if (InstructionRegister[0] == 'C') {
            CU::halt();
        }
    }
    int getProgramcounter() {
        return ProgramCounter;
    }

    void resetRegisters() {
        register_.reset();
    }
    void resetMemory() {
        memory_.reset(); // Call reset on the memory object
    }

    void setMemory(const Memory& memory) {
        memory_ = memory;
    }
    Register& getRegister() {
        return register_;
    }
    static void resetProgramCounter() {
        ProgramCounter = 0;
    }
    static void restjumpcount() {
        jumpCount = 0;
    }
};

int CPU::ProgramCounter = 10;
int CPU::jumpCount = 10;

// Machine Class
class Machine {
    CPU cpu;
    Memory memory;
    Register register_;
    vector<string> program;
    static int i;

public:
    void loadProgramFile() {
        string filename;
        cout << "Enter the filename: ";
        getline(cin, filename);
        ifstream file(filename);

        while (!file.is_open()) {
            cout << "There was an error opening the file: " << filename << endl;
            cout << "Please enter a valid file name: ";
            getline(cin, filename);

            // Attempt to open the file with the new filename
            file.clear();          // Clear any error flags from previous attempts
            file.open(filename);   // Re-open with the new filename
        }

        cpu.resetMemory(); // Reset memory
        resetIndex();      // Reset index to 10
        program.clear();
        string instruction;
        while (getline(file, instruction)) {
            program.push_back(instruction);
            loadProgramToMemory(instruction); // Load each instruction into memory immediately
        }
        if((program.size() > 0) && (program[program.size()- 1] != "C000")) {
            program.push_back("C000");
            loadProgramToMemory("C000");
        }

        file.close();
        if (program.empty()) {
            cout << "The file is empty or no instructions were found." << endl;
        }
    }

    void resetIndex() {
        i = 10; // Reset the instruction index
    }

    void run_whole() {
        cpu.resetRegisters();            // Reset all register values
        CPU::resetProgramCounter();  // Reset the program counter
        CU::haltFlag = false;
        CPU::restjumpcount(); // Reset jump count here
        while (!CU::haltFlag) {
            cpu.Fetch(memory);
        }
        cout << "Program counter after fitch : " << cpu.getProgramcounter() << endl;
        outputMemory();
        outputRegister();

    }
    void run_step_by_step() {
        cpu.resetRegisters();            // Reset all register values
        CPU::resetProgramCounter();  // Reset the program counter
        CU::haltFlag = false;
        CPU::restjumpcount(); // Reset jump count here
        while(!CU::haltFlag){
            cpu.Fetch(memory);
            cout << "Program counter after fitch : " << cpu.getProgramcounter() << endl;
            outputMemory();
            outputRegister();
            char ch;
            cout << "please enter any character to continue : ";
            cin >> ch;
        }
        cout << endl << "All Memory Execute and Decode (step be step) till found \"C000\", BYE..." << endl << endl;
    }

    void loadProgramToMemory(const string& Instruction) {
        memory.setCell(i++, Instruction.substr(0,2));
        memory.setCell(i++, Instruction.substr(2));
        cpu.setMemory(memory); // Set memory for CPU
    }
    void outputMemory(){
        cout << "Memory : "<< endl;
        for (int j = 0; j < 256; j++){
            cout << memory.getCell(j) << " ";
        }
        cout << "\n";
    }
    void outputRegister() {
        cout << "Register : "<< endl;
        // Accesses CPU's register to output actual register values
        Register& reg = cpu.getRegister();
        for (int j = 0; j < 16; j++) {
            cout << reg.getCell(j) << " ";
        }
        cout << "\n";
    }


};

int Machine::i = 10;

// MainUI Class
class MainUI {
    Machine machine;

public:
    void start() {
        cout << "Welcome to the Vole Machine!" << endl;
        while (true) {
            if (!getFile()) {  // Exit if getFile returns false
                cout << "Exiting program." << endl;
                break;
            }
        }
    }

    bool getFile() {
        char choice;
        while (true) { // Loop until a valid option is chosen
            choice = inputChoice();
            if (choice == '1') {
                machine.loadProgramFile();
                machine.run_step_by_step();
                return true;
            }if (choice == '2') {
                machine.loadProgramFile();
                machine.run_whole();
                return true;
            }if (choice == '3') {
                return false; // Exit the program
            }cout << "Invalid choice! Please try again." << endl;
        }
    }

    static char inputChoice() {
        displayMenu();
        char choice;
        cin >> choice;
        cin.ignore(); // Ignore remaining newline character (if any)
        return choice;
    }

    static void displayMenu() {
        cout << "\nMenu:" << endl;
        cout << "1. Run step by step" << endl;
        cout << "2. Run whole" << endl;
        cout << "3. EXIT" << endl;
        cout << "Choose an option: ";
    }

};

int main() {
    MainUI ui;
    ui.start();
    return 0;
}
