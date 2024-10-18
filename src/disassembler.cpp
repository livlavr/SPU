#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "custom_asserts.h" // TODO -I custom-asserts
#include "disassembler.h"
#include "assembler.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO Push build = PIZDA TEBE VANEK
//TODO Firstly text (w) --> after bin (wb)
//TODO How to make good submodule .h

int main()
{
    const char* commands[50] = {}; //TODO Dynamic memory
    fill_asm_cmds_array("src/spu_commands.bin", commands);
    // for(int i = 0; i < commands[0] + 1; i++)
    // {
    //     printf("%d ", commands[i]);
    // }
    // output_cmds_to_bin("src/assembler.asm", commands); //const??

    return 0;
}

int fill_asm_cmds_array(const char* filename, const char* commands[]) //TODO check values for valid?
{
    FILE* assembler = fopen(filename, "r");

    if (assembler == NULL)
    {
        printf("File with %s name doesn't exist\n", filename);

        return POINTER_IS_NULL;
    }

    size_t number_of_cmd    = 1;
    int    value_of_cmd     = 0;
    char   char_value_of_cmd[10] = "";
    int    cmd          = 0; // TODO Const SIZE or Dynamic (line: 19)

    while(number_of_cmd < 50)  // TODO Const SIZE or Dynamic (line: 19)
    {
        fscanf(assembler, "%d", &cmd);
        switch(cmd)
        {
            case assembler_push:
                commands[number_of_cmd++] = "PUSH";

                fscanf(assembler, "%d", &value_of_cmd);
                itoa(value_of_cmd,char_value_of_cmd,10);
                commands[number_of_cmd]   = char_value_of_cmd;
                number_of_cmd++;

            case assembler_pop:
                commands[number_of_cmd] = "POP";
                number_of_cmd++;

            case assembler_add:
                commands[number_of_cmd] = "ADD";
                number_of_cmd++;

            case assembler_sub:
                commands[number_of_cmd] = "SUB";
                number_of_cmd++;

            case assembler_div:
                commands[number_of_cmd] = "DIV";
                number_of_cmd++;

            case assembler_out:
                commands[number_of_cmd] = "OUT";
                number_of_cmd++;

            case assembler_hlt:
                commands[number_of_cmd] = "HLT";
                number_of_cmd++;

                break;

            default:
                warning(true, 0xDEADC0DE);

                break;
        }
        number_of_commands = number_of_cmd;

//
//     for(int i = 0; i < commands[0] + 1; i++)
//     {
//         printf("%d ", commands[i]);
//     }

    fclose(assembler);

    return 0;
}

int output_cmds_to_asm(const char* filename, const int commands[])
{
    FILE* bin = fopen(filename, "w"); //TODO change w --> wb

    if (bin == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum
    }

    // for(size_t number_of_cmd = 0; number_of_cmd < number_of_commands + 1; number_of_cmd++)
    // {
    //     fprintf(bin, "%d ", commands[number_of_cmd]);
    // }

    fwrite();

    return 0;
}
