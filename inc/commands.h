#ifndef COMMANDS_H_
#define COMMANDS_H_

enum CMDS_ASSEMBLY //TODO big letters enum
{
    DISASSEMBLY_PUSH = 1,
    DISASSEMBLY_POP  = 2,
    DISASSEMBLY_ADD  = 3,
    DISASSEMBLY_SUB  = 4,
    DISASSEMBLY_DIV  = 5,
    DISASSEMBLY_OUT  = 6,
    DISASSEMBLY_HLT  = 7
};

const char* ASSEMBLY_PUSH = "PUSH";
const char* ASSEMBLY_POP  = "POP";
const char* ASSEMBLY_ADD  = "ADD";
const char* ASSEMBLY_SUB  = "SUB";
const char* ASSEMBLY_DIV  = "DIV";
const char* ASSEMBLY_OUT  = "OUT";
const char* ASSEMBLY_HLT  = "HLT";


#endif
