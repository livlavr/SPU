#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

const int POISON_INDEX = -1;

struct labels
{
    char   name[MAX_CMD_SIZE + 1] = "";
    int index_to_jmp              = POISON_INDEX;
};

struct assembly_cmd_array
{
    int*   commands                   = NULL;
    labels tags[MAX_NUMBER_OF_LABELS] = {};
    size_t size_of_labels_array       = 0;
    size_t size_of_commands_array     = 0;
};

TYPE_OF_ERROR fill_bin_cmds_array(const char* buffer  , assembly_cmd_array* assembly);
TYPE_OF_ERROR output_cmds_to_bin (const char* filename, const assembly_cmd_array* assembly);
void          process_register(CMDS_DISASSEMBLY command, assembly_cmd_array* assembly,
                               int* number_of_cmd, char* cmd);
void          process_label(assembly_cmd_array* assembly, int number_of_cmd, char cmd[]);

#endif
