#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

struct assembly_cmd_array
{
    int*   commands               = NULL;
    size_t size_of_commands_array = 0;
};

TYPE_OF_ERROR fill_bin_cmds_array(const char* buffer  , assembly_cmd_array* assembly);
TYPE_OF_ERROR output_cmds_to_bin (const char* filename, const assembly_cmd_array* assembly);
TYPE_OF_ERROR size_of_text       (const char* filename, assembly_cmd_array* assembly);
void process_register(CMDS_DISASSEMBLY command, assembly_cmd_array* assembly,
                               size_t* number_of_cmd, char* cmd);
#endif
