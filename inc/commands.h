#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_DISASSEMBLY
{
    DISASSEMBLY_PUSH   = 11,
    DISASSEMBLY_POP    = 22,
    DISASSEMBLY_ADD    = 33,
    DISASSEMBLY_SUB    = 44,
    DISASSEMBLY_DIV    = 55,
    DISASSEMBLY_OUT    = 66,
    DISASSEMBLY_HLT    = 77,
    DISASSEMBLY_PUSHR  = 88,
    DISASSEMBLY_POPR   = 99,
    DISASSEMBLY_JA     = 111,
    DISASSEMBLY_JAE    = 222,
    DISASSEMBLY_JB     = 333,
    DISASSEMBLY_JBE    = 444,
    DISASSEMBLY_JE     = 555,
    DISASSEMBLY_JNE    = 666,
    DISASSEMBLY_REG_AX = 1,
    DISASSEMBLY_REG_BX = 2,
    DISASSEMBLY_REG_CX = 3,
    DISASSEMBLY_REG_DX = 4
};

const char* ASSEMBLY_PUSH   = "PUSH";
const char* ASSEMBLY_POP    = "POP" ;
const char* ASSEMBLY_ADD    = "ADD" ;
const char* ASSEMBLY_SUB    = "SUB" ;
const char* ASSEMBLY_DIV    = "DIV" ;
const char* ASSEMBLY_OUT    = "OUT" ;
const char* ASSEMBLY_HLT    = "HLT" ;
const char* ASSEMBLY_REG_AX = "AX"  ;
const char* ASSEMBLY_REG_BX = "BX"  ;
const char* ASSEMBLY_REG_CX = "CX"  ;
const char* ASSEMBLY_REG_DX = "DX"  ;
const char* ASSEMBLY_JA     = "JA:" ;
const char* ASSEMBLY_JAE    = "JAE:";
const char* ASSEMBLY_JB     = "JB:" ;
const char* ASSEMBLY_JBE    = "JBE:";
const char* ASSEMBLY_JE     = "JE:" ;
const char* ASSEMBLY_JNE    = "JNE:";


const size_t MAX_NUMBER_OF_CMDS      = 50;
const size_t MAX_CMD_SIZE            = 15;
const size_t MAX_NUMBER_OF_LABELS    = 10;
const size_t MAX_SIZE_OF_ASM_PROGRAM = MAX_NUMBER_OF_CMDS * MAX_CMD_SIZE * 2;
const char   LABEL_NAME_ENDING       = ':';

#endif
