#ifndef DISASSEMBLER_H_
#define DISASSEMBLER_H_

enum COMMANDS_ASSEMBLER //TODO big letters enum
{
    assembler_push = 1,
    assembler_pop  = 2,
    assembler_add  = 3,
    assembler_sub  = 4,
    assembler_div  = 5,
    assembler_out  = 6,
    assembler_hlt  = 7
};

int fill_bin_cmds_array(const char* buffer, int* commands);
int output_cmds_to_bin (const char* filename, const int* commands);

#endif
