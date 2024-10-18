#ifndef DISASSEMBLER_H_
#define DISASSEMBLER_H_

// const char* disassembler_push = "PUSH"; //TODO загнать в константы или это лишнее?
// const char* disassembler_pop  = "POP";
// const char* disassembler_add  = "ADD";
// const char* disassembler_sub  = "SUB";
// const char* disassembler_div  = "DIV";
// const char* disassembler_out  = "OUT";
// const char* disassembler_hlt  = "HLT";

int fill_asm_cmds_array    (const char* buffer, const char* commands[]);
int output_cmds_to_asm (const char* filename, const char* commands[]);

#endif
