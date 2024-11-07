
#include "ALU.h"
string ALU::hexToDec(string hexValue) {
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

void ALU::add(int idx1, int idx2, int idx3, Register& reg) {

    bool isFloatingPoint = (reg.getCell(idx1).length() == 4 && reg.getCell(idx2).length() == 4);

    if (isFloatingPoint) {

        int intPart1 = hexToDec(reg.getCell(idx1).substr(0, 2)).size() > 0 ? stoi(hexToDec(reg.getCell(idx1).substr(0, 2))) : 0;
        int fracPart1 = hexToDec(reg.getCell(idx1).substr(2, 2)).size() > 0 ? stoi(hexToDec(reg.getCell(idx1).substr(2, 2))) : 0;
        int intPart2 = hexToDec(reg.getCell(idx2).substr(0, 2)).size() > 0 ? stoi(hexToDec(reg.getCell(idx2).substr(0, 2))) : 0;
        int fracPart2 = hexToDec(reg.getCell(idx2).substr(2, 2)).size() > 0 ? stoi(hexToDec(reg.getCell(idx2).substr(2, 2))) : 0;

        int resIntPart = intPart1 + intPart2;
        int resFracPart = fracPart1 + fracPart2;


        if (resFracPart >= 100) {
            resIntPart += resFracPart / 100;
            resFracPart = resFracPart % 100;
        }


        reg.setCell(idx3, decToHex(resIntPart) + decToHex(resFracPart));
        cout << "Floating point addition: " << resIntPart << "." << (resFracPart < 10 ? "0" : "") << resFracPart
             << " stored in register " << idx3 << endl;
    } else {

        int result = stoi(hexToDec(reg.getCell(idx1))) + stoi(hexToDec(reg.getCell(idx2)));


        if (result >= 256) {
            result -= 256;
        }

        reg.setCell(idx3, decToHex(result));
        cout << "Two's complement addition: " << result << " stored in register " << idx3 << endl;
    }
}