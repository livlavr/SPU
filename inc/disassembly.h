#ifndef DISASSEMBLY_H_
#define DISASSEMBLY_H_

struct disassembly_cmd_array
{
    char  commands[1000]              = ""; //TODO bullshit
    size_t size_of_commands_array = 0;
};

int fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly);
int output_cmds_to_asm (const char* filename, const disassembly_cmd_array* disassembly);

#endif
