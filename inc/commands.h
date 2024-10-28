#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_DISASSEMBLY
{
    DISASSEMBLY_HLT    =  1 << 3,
    DISASSEMBLY_PUSH   =  2 << 3,
    DISASSEMBLY_POP    =  3 << 3,
    DISASSEMBLY_ADD    =  4 << 3,
    DISASSEMBLY_SUB    =  5 << 3,
    DISASSEMBLY_DIV    =  6 << 3,
    DISASSEMBLY_OUT    =  7 << 3,
    DISASSEMBLY_MUL    =  8 << 3,
    DISASSEMBLY_IN     =  9 << 3,
    DISASSEMBLY_PUSHR  = 10 << 3,
    DISASSEMBLY_POPR   = 11 << 3,
    DISASSEMBLY_JA     = 12 << 3,
    DISASSEMBLY_JAE    = 13 << 3,
    DISASSEMBLY_JB     = 14 << 3,
    DISASSEMBLY_JBE    = 15 << 3,
    DISASSEMBLY_JE     = 16 << 3,
    DISASSEMBLY_JNE    = 17 << 3,
    DISASSEMBLY_JMP    = 18 << 3,
    DISASSEMBLY_CALL   = 19 << 3,
    DISASSEMBLY_RETURN = 20 << 3,
    DISASSEMBLY_REG_AX = 21 << 3,
    DISASSEMBLY_REG_BX = 22 << 3,
    DISASSEMBLY_REG_CX = 23 << 3,
    DISASSEMBLY_REG_DX = 24 << 3
};

enum TYPE_OF_ARGUMENT
{

}

const char* ASSEMBLY_PUSH   = "PUSH";
const char* ASSEMBLY_POP    = "POP" ;
const char* ASSEMBLY_ADD    = "ADD" ;
const char* ASSEMBLY_SUB    = "SUB" ;
const char* ASSEMBLY_DIV    = "DIV" ;
const char* ASSEMBLY_OUT    = "OUT" ;
const char* ASSEMBLY_IN     = "IN"  ;
const char* ASSEMBLY_MUL    = "MUL" ;
const char* ASSEMBLY_HLT    = "HLT" ;
const char* ASSEMBLY_REG_AX = "AX"  ;
const char* ASSEMBLY_REG_BX = "BX"  ;
const char* ASSEMBLY_REG_CX = "CX"  ;
const char* ASSEMBLY_REG_DX = "DX"  ;
const char* ASSEMBLY_JA     = "JA"  ;
const char* ASSEMBLY_JAE    = "JAE" ;
const char* ASSEMBLY_JB     = "JB"  ;
const char* ASSEMBLY_JBE    = "JBE" ;
const char* ASSEMBLY_JE     = "JE"  ;
const char* ASSEMBLY_JNE    = "JNE" ;
const char* ASSEMBLY_JMP    = "JMP" ;
const char* ASSEMBLY_CALL   = "CALL";
const char* ASSEMBLY_RETURN = "RETURN";


const size_t MAX_NUMBER_OF_CMDS      = 50; //TODO delete all bad consts
const size_t MAX_CMD_SIZE            = 15;
const size_t MAX_NUMBER_OF_LABELS    = 10;
const size_t NUMBER_OF_REGISTERS     = 5;
const size_t MAX_SIZE_OF_ASM_PROGRAM = MAX_NUMBER_OF_CMDS * MAX_CMD_SIZE * 2;
const char   LABEL_NAME_ENDING       = ':';

#endif
