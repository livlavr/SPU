#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_DISASSEMBLY //TODO big letters enum
{
    DISASSEMBLY_PUSH  = 11,
    DISASSEMBLY_POP   = 22,
    DISASSEMBLY_ADD   = 33,
    DISASSEMBLY_SUB   = 44,
    DISASSEMBLY_DIV   = 55,
    DISASSEMBLY_OUT   = 66,
    DISASSEMBLY_HLT   = 77,
    DISASSEMBLY_PUSHR = 88,
    DISASSEMBLY_POPR  = 99,
    DISASSEMBLY_REG_AX = 1,
    DISASSEMBLY_REG_BX = 2,
    DISASSEMBLY_REG_CX = 3,
    DISASSEMBLY_REG_DX = 4
};

const char* ASSEMBLY_PUSH   = "PUSH";
const char* ASSEMBLY_POP    = "POP";
const char* ASSEMBLY_ADD    = "ADD";
const char* ASSEMBLY_SUB    = "SUB";
const char* ASSEMBLY_DIV    = "DIV";
const char* ASSEMBLY_OUT    = "OUT";
const char* ASSEMBLY_HLT    = "HLT";
const char* ASSEMBLY_REG_AX = "AX";
const char* ASSEMBLY_REG_BX = "BX";
const char* ASSEMBLY_REG_CX = "CX";
const char* ASSEMBLY_REG_DX = "DX";


const size_t MAX_NUMBER_OF_CMDS      = 50;
const size_t MAX_CMD_SIZE            = 15;
const size_t MAX_SIZE_OF_ASM_PROGRAM = MAX_NUMBER_OF_CMDS * MAX_CMD_SIZE * 2;

#endif
