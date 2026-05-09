# Team_1_CA26
This project is a C-based simulation of a fictional processor using a Von Neumann architecture.  The goal of this project is to simulate the behavior of the processor from reading an assembly program, parsing and encoding its instructions, loading them into memory, and running them through the processor pipeline cycle by cycle.
## Team Members

| Name | ID | Tutorial |
|---|---|---|
| Martin Shihata | 1600-2227 | 2 |
| Ahmed Hazem | 1900-2039 | 2 |
| Youssef Habashy | 1900-2208 | 2 |
|  Sherif Fawzy | 1900-2196 | 2 |
| Youssef Abdelbary | 1900-2212 | 2 |

## Project Overview

The goal of this project is to simulate the execution of assembly instructions on a fictional processor.

The simulator performs the following steps:

1. Reads an assembly program from `programs/input.txt`.
2. Parses the instructions.
3. Encodes the parsed instructions into 32-bit instruction words.
4. Creates and initializes the CPU.
5. Loads the encoded instructions into main memory.
6. Runs the processor pipeline cycle by cycle.
7. Prints the pipeline state after every clock cycle.
8. Writes the full execution log, final register state, and final memory state to `output/output.txt`.

## Processor Architecture

The simulated processor uses a Von Neumann architecture.

This means that instructions and data are stored in the same physical memory.

### Main Memory

Main memory contains 2048 words.

Each word is 32 bits.

Memory layout:

| Address Range | Purpose |
|---|---|
| 0 to 1023 | Instruction segment |
| 1024 to 2047 | Data segment |

### Registers

The processor has:

| Register Type | Count | Description |
|---|---|---|
| General-purpose registers | 31 | R1 to R31 |
| Zero register | 1 | R0, always contains 0 |
| Program counter | 1 | PC, stores the address of the current instruction |

R0 is hardwired to zero and cannot be modified by any instruction.

The PC is stored as part of the CPU state because it has special behavior during instruction fetch, jumps, and branches.

## Instruction Set Architecture

The processor supports 12 instructions.

Each instruction is 32 bits.

There are 3 instruction formats:

| Format | Fields |
|---|---|
| R-Format | OPCODE, R1, R2, R3, SHAMT |
| I-Format | OPCODE, R1, R2, IMMEDIATE |
| J-Format | OPCODE, ADDRESS |

The instruction module is responsible for encoding and decoding instructions according to the ISA.

## Base Project Folder Structure

```text
Team_1_CA26/
  IO/
    input.txt
    output.txt

  src/
    main.c
    parser.c
    instruction.c
    memory.c
    registers.c
    cpu.c
    logger.c

    pipeline/
      pipeline.c
      pipeline_slot.c
      instruction_packet.c

  include/
    constants.h
    parser.h
    instruction.h
    memory.h
    registers.h
    cpu.h
    logger.h

    pipeline/
      pipeline.h
      pipeline_slot.h
      instruction_packet.h

  README.md
```


## Execution Flow

The high-level program flow is:

```text
1. main starts the program.
2. main calls the parser.
3. parser reads programs/input.txt.
4. parser returns parsed instructions.
5. main creates the CPU.
6. CPU initializes memory, registers, PC, clock, and pipeline.
7. CPU loads encoded instructions into memory.
8. CPU starts the simulation loop.
9. Each cycle:
     - CPU creates a cycle log.
     - CPU calls pipeline_run_cycle.
     - Pipeline runs the active pipeline stages.
     - Pipeline updates pipeline slots.
     - Logger prints the cycle log to the console.
     - Logger stores the cycle log.
     - CPU increments the clock.
10. After simulation ends:
     - Logger writes all logs to output/output.txt.
     - Logger writes final registers.
     - Logger writes final memory.
```
