#ifndef DISASSEMBLY_H_
#define DISASSEMBLY_H_

struct disassembly_cmd_array
{
    char* commands = NULL;
    size_t size_of_commands_array = 0;
};

TYPE_OF_ERROR fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly);
void          int_to_str         (int number, char* str);
inline void   reverse_str        (char* str, int length);
TYPE_OF_ERROR output_cmds_to_asm (const char* filename, const disassembly_cmd_array* disassembly);
void process_register(const char* command, disassembly_cmd_array* disassembly,
                      size_t* number_of_cmd, int cmd);

#endif
