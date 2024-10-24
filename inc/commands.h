#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_DISASSEMBLY
{
    DISASSEMBLY_HLT    = 10,
    DISASSEMBLY_PUSH   = 20,
    DISASSEMBLY_POP    = 30,
    DISASSEMBLY_ADD    = 40,
    DISASSEMBLY_SUB    = 50,
    DISASSEMBLY_DIV    = 60,
    DISASSEMBLY_OUT    = 70,
    DISASSEMBLY_MUL    = 80,
    DISASSEMBLY_PUSHR  = 100,
    DISASSEMBLY_POPR   = 200,
    DISASSEMBLY_JA     = 1000,
    DISASSEMBLY_JAE    = 2000,
    DISASSEMBLY_JB     = 3000,
    DISASSEMBLY_JBE    = 4000,
    DISASSEMBLY_JE     = 5000,
    DISASSEMBLY_JNE    = 6000,
    DISASSEMBLY_JMP    = 7000,
    DISASSEMBLY_CALL   = 8000,
    DISASSEMBLY_RETURN = 9000,
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


const size_t MAX_NUMBER_OF_CMDS      = 50;
const size_t MAX_CMD_SIZE            = 15;
const size_t MAX_NUMBER_OF_LABELS    = 10;
const size_t NUMBER_OF_REGISTERS     = 5;
const size_t MAX_SIZE_OF_ASM_PROGRAM = MAX_NUMBER_OF_CMDS * MAX_CMD_SIZE * 2;
const char   LABEL_NAME_ENDING       = ':';

#endif
