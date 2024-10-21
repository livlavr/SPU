#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "custom_asserts.h"
#include "disassembly.h"
#include "commands.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main()
{

    disassembly_cmd_array disassembly = {};
    fill_asm_cmds_array("src/spu_commands.bin", &disassembly);
//     output_cmds_to_asm ("src/assembly.asm"    , &disassembly); //TODO const assembly??

    return 0;
}

int fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly) //TODO check values for valid?
{
    FILE* bin_file = fopen(filename, "rb");

    if (bin_file == NULL)
    {
        printf("File with %s name doesn't exist\n", filename);

        return 1;//TODO dont return enum value
    }

    char value_of_cmd[10] = "";
    int  cmd              = 0;
    int  number_of_cmd    = 0;

    int bin_commands[100] = {};
    fread(bin_commands, sizeof(int), 19, bin_file);


    while(number_of_cmd < 50)
    {
        // printf("%d", bin_commands[number_of_cmd]);
        switch(bin_commands[number_of_cmd])
        {
            case DISASSEMBLY_PUSH:
                strcat(disassembly->commands, ASSEMBLY_PUSH);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                value_of_cmd = itoa(bin_commands[number_of_cmd++]);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, "\n");

                printf("%s\n", disassembly->commands);

                number_of_cmd++;

            case DISASSEMBLY_POP:
                strcat(disassembly->commands, ASSEMBLY_POP);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

            case DISASSEMBLY_ADD:
                strcat(disassembly->commands, ASSEMBLY_ADD);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

            case DISASSEMBLY_SUB:
                strcat(disassembly->commands, ASSEMBLY_SUB);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

            case DISASSEMBLY_DIV:
                strcat(disassembly->commands, ASSEMBLY_DIV);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

            case DISASSEMBLY_OUT:
                strcat(disassembly->commands, ASSEMBLY_OUT);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

            case DISASSEMBLY_HLT:
                strcat(disassembly->commands, ASSEMBLY_HLT);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

                break;

            default:
                warning(false, 0xDEADC0DE);
        }
    }
    // disassembly->size_of_commands_array = number_of_cmd;

    fclose(bin_file);

    return 0;
}

int output_cmds_to_asm(const char* filename, const disassembly_cmd_array* disassembly)
{
    FILE* asm_file = fopen(filename, "wb");

    if (asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum

        return FILE_OPEN_ERROR;
    }

    // for(size_t number_of_cmd = 0; number_of_cmd < number_of_assembly->commands + 1; number_of_cmd++)
    // {
    //     fprintf(bin, "%d ", assembly->commands[number_of_cmd]);
    // }

    fwrite(disassembly->commands, sizeof(char), sizeof(disassembly->commands), asm_file);

    return 0;
}
