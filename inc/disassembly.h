#ifndef DISASSEMBLY_H_
#define DISASSEMBLY_H_

struct disassembly_cmd_array
{
    char* commands                = NULL;
    size_t size_of_commands_array = 0;
};

TYPE_OF_ERROR fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly);
TYPE_OF_ERROR int_to_str         (int number, char* str);
inline void   reverse_str        (char* str, int length);
TYPE_OF_ERROR output_cmds_to_asm (const char* filename, const disassembly_cmd_array* disassembly);
TYPE_OF_ERROR process_register   (const char* command, disassembly_cmd_array* disassembly, int* number_of_cmd, int cmd);
bool          find_elem          (int number, int* array, int size_of_array);
TYPE_OF_ERROR fill_poison        (int* array, int size, int poison);

const int POISON = -1;

#endif
