#include <stdio.h>
#include <cstdlib>
#include <string.h>

#include "custom_asserts.h"
#include "assembly.h"
#include "commands.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main()
{
    assembly_cmd_array assembly = {};
    assembly.commands = (int*)calloc(50, sizeof(int));

    fill_bin_cmds_array("src/assembly.asm"    , &assembly);
    output_cmds_to_bin ("src/spu_commands.bin", &assembly); //TODO const assembly??
    return 0;
}

int fill_bin_cmds_array(const char* filename, assembly_cmd_array* assembly) //TODO check values for valid?
{
    FILE* asm_file = fopen(filename, "r");

    if (asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename);

        return POINTER_IS_NULL; //TODO I don't return enum type
    }

    size_t number_of_cmd = 0;
    int    value_of_cmd  = 0;
    char   cmd[15]       = ""; // TODO Const SIZE or Dynamic //TODO if marker more then 15 --> syntax error

    while(number_of_cmd < 50) // TODO Const SIZE or Dynamic
    {
        fscanf(asm_file, "%s", &cmd);
        // printf("%s\n", cmd);
        if(strcmp(ASSEMBLY_PUSH, cmd) == 0)
        {
            // printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_PUSH;

            fscanf(asm_file, "%d", &value_of_cmd);
            // printf("%d - NUMBER\n", value_of_cmd);
            assembly->commands[number_of_cmd]   = value_of_cmd;
        }

        else if(strcmp(ASSEMBLY_POP, cmd) == 0)
        {
            // printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_POP;
        }

        else if(strcmp(ASSEMBLY_ADD, cmd) == 0)
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_ADD;
        }

        else if(strcmp(ASSEMBLY_SUB, cmd) == 0)
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_SUB;
        }

        else if(strcmp(ASSEMBLY_DIV, cmd) == 0)
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_DIV;
        }

        else if(strcmp(ASSEMBLY_OUT, cmd) == 0)
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_OUT;
        }

        else if(strcmp(ASSEMBLY_HLT, cmd) == 0)
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd] = DISASSEMBLY_HLT;
            number_of_cmd++;

            break;
        }

        else //TODO test this error
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't find %s command", cmd);

            exit(0);
        }
        number_of_cmd++; //TODO delete this and add ++ to [number...cmd]
    }
    assembly->size_of_commands_array = number_of_cmd;

//     for(int i = 0; i < commands[0] + 1; i++)
//     {
//         printf("%d ", commands[i]);
//     }

    fclose(asm_file);

    return 0;
}

int output_cmds_to_bin(const char* filename, const assembly_cmd_array* assembly)
{
    FILE* bin = fopen(filename, "wb");

    if (bin == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum

        return FILE_OPEN_ERROR; //TODO errors enum
    }

    // for(size_t number_of_cmd = 0; number_of_cmd < commands[0] + 1; number_of_cmd++)
    // {
    //     fprintf(bin, "%d ", commands[number_of_cmd]);
    // }

    fwrite(assembly->commands, sizeof(int), assembly->size_of_commands_array, bin);

    return 0;
}
