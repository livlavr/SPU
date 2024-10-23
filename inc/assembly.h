#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

struct labels
{
    char   name[MAX_CMD_SIZE] = "";
    size_t index_to_jmp       = 0;
}

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
                               size_t* number_of_cmd, char* cmd);

#endif
