# Vole Machine

A virtual machine implementation that simulates a simplified computer architecture with registers, memory, and instruction execution.

## Overview

The Vole Machine is an educational project that simulates the core components of a computer system, including a CPU, memory, and registers. It implements a simple instruction set architecture (ISA) that allows for program execution, memory manipulation, and basic arithmetic operations.

## Features

- **Memory System**: 256 memory cells, each storing 2-byte hexadecimal values
- **Register Set**: 16 registers for temporary data storage
- **Arithmetic Logic Unit (ALU)**: Supports addition operations on both integer and floating-point values
- **Control Unit (CU)**: Manages instruction execution and program flow control
- **Program Execution**: Run programs step-by-step or in a single execution
- **Instruction Set**:
  - Load operations (Memory to Register)
  - Store operations (Register to Memory)
  - Move operations (Register to Register)
  - Addition operations
  - Jump operations (Conditional branching)
  - Halt operation

## Instruction Set

| Code | Description |
|------|-------------|
| 1RXY | Load value from memory address XY into register R |
| 2RXY | Load immediate value XY into register R |
| 3R00 | Print value from register R and restore it to memory |
| 3RXY | Store value from register R to memory address XY |
| 4RXY | Move value from register X to register Y |
| 5RXY | Add values in registers X and Y, storing result in register R |
| 6RXY | Add values (floating point) in registers X and Y, storing result in register R |
| BRXY | Jump to memory address XY if value in register R equals value in register 0 |
| C000 | Halt program execution |

## Program File Format

Programs are loaded from text files where each line represents a 4-character instruction in hexadecimal format (e.g., `2100`, `5012`, etc.).

## Getting Started

Follow the interactive menu to:
1. Run a program step-by-step (with output after each instruction)
2. Run a program completely (with output only at the end)
3. Exit the program

### Loading a Program

When prompted, enter the filename of your program. The file should contain one instruction per line in 4-character hexadecimal format.

## Architecture Details

### Memory

The memory system consists of 256 cells, each capable of storing a 2-byte hexadecimal value. Memory addresses start at 0, with program storage beginning at address 10.

### Registers

The machine features 16 registers (0-15), each storing a 2-byte hexadecimal value. Register 0 has special significance in jump operations.

### ALU

The ALU supports addition operations for both regular hexadecimal values and floating-point values (represented as 4-character hex strings).

### Control Unit

The CU handles the execution of instructions and manages program flow, including conditional jumps and the halt operation.

### CPU

The CPU coordinates the fetch-decode-execute cycle, managing the program counter and facilitating instruction execution.


## Project Structure

- `main.cpp`: Entry point that initializes the UI
- `VoleMachine.h`: Header file defining all classes and interfaces
- `VoleMachine.cpp`: Implementation of all machine components


