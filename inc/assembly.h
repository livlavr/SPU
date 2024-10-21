#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

struct assembly_cmd_array
{
    int*   commands               = NULL;
    size_t size_of_commands_array = 0;
};

int fill_bin_cmds_array(const char* buffer  , assembly_cmd_array* assembly);
int output_cmds_to_bin (const char* filename, const assembly_cmd_array* assembly);

#endif
