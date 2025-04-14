#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

const int POISON_INDEX = -1;

struct labels
{
    char   name[MAX_CMD_SIZE + 1] = "";
    int    index_to_jmp           = POISON_INDEX;
};

struct assembly_cmd_array
{
    char*  commands                   = NULL;
    labels tags[MAX_NUMBER_OF_LABELS] = {};
    size_t size_of_labels_array       = 0;
    size_t size_of_commands_array     = 0;
};

TYPE_OF_ERROR fill_bin_cmds_array_bytes(const char* filename, assembly_cmd_array* assembly);
TYPE_OF_ERROR output_cmds_to_bin       (const char* filename, const assembly_cmd_array* assembly);
TYPE_OF_ERROR process_register         (assembly_cmd_array* assembly, int* number_of_cmd, char* register_value);
TYPE_OF_ERROR process_label            (assembly_cmd_array* assembly, int number_of_cmd, char*** asm_commands);
inline bool   find_elem                (char* elem, labels* array, int size_of_array);
TYPE_OF_ERROR skip_spaces              (char*** asm_commands);
TYPE_OF_ERROR create_cmd_description   (assembly_cmd_array* assembly, char*** asm_commands,
                                        int* number_of_cmd, CMDS_DISASSEMBLY disassembly_cmd);
#define scan_command(buffer, cmd) sscanf(buffer, "%14s", cmd) //TODO calloc %n and sscanf :)

#endif
