#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_DISASSEMBLY
{
    DISASSEMBLY_HLT    =  1 << 3, // 8
    DISASSEMBLY_PUSH   =  2 << 3, // 16
    DISASSEMBLY_POP    =  3 << 3, // 24
    DISASSEMBLY_ADD    =  4 << 3, // 32
    DISASSEMBLY_SUB    =  5 << 3, // 40
    DISASSEMBLY_DIV    =  6 << 3, // 48
    DISASSEMBLY_OUT    =  7 << 3, // 56
    DISASSEMBLY_MUL    =  8 << 3, // 64
    DISASSEMBLY_IN     =  9 << 3, // 72
    DISASSEMBLY_JA     = 10 << 3, // 80
    DISASSEMBLY_JAE    = 11 << 3, // 88
    DISASSEMBLY_JB     = 12 << 3, // 96
    DISASSEMBLY_JBE    = 13 << 3, // 104
    DISASSEMBLY_JE     = 14 << 3, // 112
    DISASSEMBLY_JNE    = 15 << 3, // 120
    DISASSEMBLY_JMP    = 16 << 3, // 128
    DISASSEMBLY_CALL   = 17 << 3, // 136
    DISASSEMBLY_RETURN = 18 << 3, // 144
    DISASSEMBLY_DRAW   = 19 << 3, // 152
    DISASSEMBLY_SQRT   = 20 << 3, // 160
    DISASSEMBLY_REG_AX = 1,
    DISASSEMBLY_REG_BX = 2,
    DISASSEMBLY_REG_CX = 3,
    DISASSEMBLY_REG_DX = 4
};

enum TYPE_OF_ARGUMENT // 00000MIR
{
    RAM                   = 1 << 2,
    CONSTANT              = 1 << 1,
    REGISTER              = 1 << 0
};

static const char* ASSEMBLY_PUSH   = "PUSH";
static const char* ASSEMBLY_POP    = "POP" ;
static const char* ASSEMBLY_ADD    = "ADD" ;
static const char* ASSEMBLY_SUB    = "SUB" ;
static const char* ASSEMBLY_DIV    = "DIV" ;
static const char* ASSEMBLY_OUT    = "OUT" ;
static const char* ASSEMBLY_IN     = "IN"  ;
static const char* ASSEMBLY_MUL    = "MUL" ;
static const char* ASSEMBLY_HLT    = "HLT" ;
static const char* ASSEMBLY_REG_AX = "AX"  ;
static const char* ASSEMBLY_REG_BX = "BX"  ;
static const char* ASSEMBLY_REG_CX = "CX"  ;
static const char* ASSEMBLY_REG_DX = "DX"  ;
static const char* ASSEMBLY_JA     = "JA"  ;
static const char* ASSEMBLY_JAE    = "JAE" ;
static const char* ASSEMBLY_JB     = "JB"  ;
static const char* ASSEMBLY_JBE    = "JBE" ;
static const char* ASSEMBLY_JE     = "JE"  ;
static const char* ASSEMBLY_JNE    = "JNE" ;
static const char* ASSEMBLY_JMP    = "JMP" ;
static const char* ASSEMBLY_CALL   = "CALL";
static const char* ASSEMBLY_RETURN = "RETURN";
static const char* ASSEMBLY_DRAW = "DRAW";
static const char* ASSEMBLY_SQRT = "SQRT";



const size_t MAX_NUMBER_OF_CMDS      = 50; //TODO delete all bad consts
const size_t MAX_CMD_SIZE            = 15;
const size_t MAX_NUMBER_OF_LABELS    = 10;
const size_t MAX_NUMBER_OF_REGISTERS = 5;
const size_t SIZE_OF_RAM             = 900;
const int    BYTE_COMMAND_MASK       = 248;
const int    BYTE_FORMAT_MASK        = 7;
const int    IS_REGISTER             = 1;
const int    IS_I_CONSTANT           = 2;
const int    IS_MEMORY               = 4;
const size_t MAX_SIZE_OF_ASM_PROGRAM = MAX_NUMBER_OF_CMDS * MAX_CMD_SIZE * 2;
const char   LABEL_NAME_ENDING       = ':';

#endif
