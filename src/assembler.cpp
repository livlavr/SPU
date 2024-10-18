#include <stdio.h>
#include <cstdlib>
#include <string.h>

#include "custom_asserts.h" // TODO -I custom-asserts
#include "assembler.h"
#include "disassembler.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO Push build = PIZDA TEBE VANEK
//TODO Firstly text -> after bin
//TODO How to make good submodule .h

int main()
{
    int* commands = (int*)calloc(50, sizeof(int)); //TODO Dynamic memory
    fill_bin_cmds_array("src/assembler.asm", commands);
    // for(int i = 0; i < commands[0] + 1; i++)
    // {
    //     printf("%d ", commands[i]);
    // }
    output_cmds_to_bin("src/spu_commands.bin", commands); //const??
    return 0;
}

int fill_bin_cmds_array(const char* filename, int* commands) //TODO check values for valid?
{
    FILE* assembler = fopen(filename, "r");

    if (assembler == NULL)
    {
        printf("File with %s name doesn't exist\n", filename);

        return POINTER_IS_NULL;
    }

    size_t number_of_cmd = 1;
    int    value_of_cmd  = 0;
    char   cmd[10]       = ""; // TODO Const SIZE or Dynamic (line: 19)

    while(number_of_cmd < 50) // TODO Const SIZE or Dynamic (line: 19)
    {
        fscanf(assembler, "%s", &cmd);
        // printf("%s\n", cmd);
        if(strcmp("PUSH", cmd) == 0)
        {
            // printf("%s - CMD\n", cmd);
            commands[number_of_cmd++] = assembler_push;

            fscanf(assembler, "%d", &value_of_cmd);
            // printf("%d - NUMBER\n", value_of_cmd);
            commands[number_of_cmd]   = value_of_cmd;
        }

        else if(strcmp("POP", cmd) == 0)
        {
            // printf("%s - CMD\n", cmd);
            commands[number_of_cmd] = assembler_pop;
        }

        else if(strcmp("ADD", cmd) == 0)
        {
            // printf("%s\n", cmd);
            commands[number_of_cmd] = assembler_add;
        }

        else if(strcmp("SUB", cmd) == 0)
        {
            // printf("%s\n", cmd);
            commands[number_of_cmd] = assembler_sub;
        }

        else if(strcmp("DIV", cmd) == 0)
        {
            // printf("%s\n", cmd);
            commands[number_of_cmd] = assembler_div;
        }

        else if(strcmp("OUT", cmd) == 0)
        {
            // printf("%s\n", cmd);
            commands[number_of_cmd] = assembler_out;
        }

        else if(strcmp("HLT", cmd) == 0)
        {
            // printf("%s\n", cmd);
            commands[number_of_cmd] = assembler_hlt;

            break;
        }

        else
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembler: can't find %s command", cmd);
        }
        number_of_cmd++;
    }
    commands[0] = number_of_cmd;
//
//     for(int i = 0; i < commands[0] + 1; i++)
//     {
//         printf("%d ", commands[i]);
//     }

    fclose(assembler);

    return 0;
}

int output_cmds_to_bin(const char* filename, const int* commands)
{
    FILE* bin = fopen(filename, "wb"); //TODO change w --> wb

    if (bin == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum
    }

    // for(size_t number_of_cmd = 0; number_of_cmd < commands[0] + 1; number_of_cmd++)
    // {
    //     fprintf(bin, "%d ", commands[number_of_cmd]);
    // }

    fwrite(commands, sizeof(int), commands[0] + 1, bin);

    return 0;
}
