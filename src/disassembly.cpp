#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "disassembly.h"
#include "commands.h"
#include "size_of_text.h"
#include "stack_public.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main()
{
    disassembly_cmd_array disassembly = {};
    fill_asm_cmds_array("src/spu_commands.bin", &disassembly);
    output_cmds_to_asm ("src/assembly.asm"    , &disassembly);

    return 0;
}

TYPE_OF_ERROR fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly) //TODO check values for valid?
{
    FILE* bin_file = fopen(filename, "rb");

    if (bin_file == NULL)
    {
        printf("File with %s name doesn't exist\n", filename);

        return FILE_OPEN_ERROR;
    }

    size_of_text(filename, &(disassembly->size_of_commands_array));

    size_t number_of_cmd               = 0;
    char   value_of_cmd[MAX_CMD_SIZE]  = "";
    bool   hlt_not_found               = true;

    int bin_commands[disassembly->size_of_commands_array] = {};

    disassembly->commands = (char*)calloc(disassembly->size_of_commands_array * MAX_CMD_SIZE, sizeof(char));

    fread(bin_commands, sizeof(int), disassembly->size_of_commands_array, bin_file);

    fclose(bin_file);

    while(number_of_cmd < MAX_NUMBER_OF_CMDS && hlt_not_found)
    {
        switch(bin_commands[number_of_cmd])
        {
            case DISASSEMBLY_PUSH:
                strcat(disassembly->commands, ASSEMBLY_PUSH);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_PUSHR:
                number_of_cmd++;
                process_register(ASSEMBLY_PUSH, disassembly, &number_of_cmd, bin_commands[number_of_cmd]);
                printf("%s", disassembly->commands);
                break;

            case DISASSEMBLY_POP:
                strcat(disassembly->commands, ASSEMBLY_POP);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_POPR:
                number_of_cmd++;
                process_register(ASSEMBLY_POP, disassembly, &number_of_cmd, bin_commands[number_of_cmd]);
                printf("%s", disassembly->commands);

                break;

            case DISASSEMBLY_ADD:
                strcat(disassembly->commands, ASSEMBLY_ADD);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_SUB:
                strcat(disassembly->commands, ASSEMBLY_SUB);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_DIV:
                strcat(disassembly->commands, ASSEMBLY_DIV);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_OUT:
                strcat(disassembly->commands, ASSEMBLY_OUT);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_HLT:
                strcat(disassembly->commands, ASSEMBLY_HLT);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                hlt_not_found = false;

                break;

            default:
                color_printf(RED_TEXT, BOLD, "%d\n", bin_commands[number_of_cmd]);

                warning(false, VALUE_ERROR);
        }
    }

    return SUCCESS;
}

void int_to_str(int number, char* str)
{
    int number_of_char = 0;
    int sign = number;

    if (number < 0)
        number = -number;

    while (number > 0)
    {
        str[number_of_char++] = number % 10 + '0';
      	number /= 10;
    }

    if (sign < 0)
    {
        str[number_of_char++] = '-';
    }

    str[number_of_char] = '\0';

    reverse_str(str, number_of_char);
}

inline void reverse_str(char* str, int length)
{
    for (int left_char = 0, right_char = length - 1; left_char < right_char; left_char++, right_char--)
    {
        char switcher   = str[left_char];
        str[left_char]  = str[right_char];
        str[right_char] = switcher;
    }
}

void process_register(const char* command, disassembly_cmd_array* disassembly, size_t* number_of_cmd, int cmd)
{
    strcat(disassembly->commands, command);
    strcat(disassembly->commands, " ");
    switch(cmd)
    {
        case DISASSEMBLY_REG_AX :
            strcat(disassembly->commands, ASSEMBLY_REG_AX);
            strcat(disassembly->commands, "\n");
            (*number_of_cmd)++;

            break;
        case DISASSEMBLY_REG_BX :
            strcat(disassembly->commands, ASSEMBLY_REG_BX);
            strcat(disassembly->commands, "\n");
            (*number_of_cmd)++;

            break;
        case DISASSEMBLY_REG_CX :
            strcat(disassembly->commands, ASSEMBLY_REG_CX);
            strcat(disassembly->commands, "\n");
            (*number_of_cmd)++;

            break;
        case DISASSEMBLY_REG_DX :
            strcat(disassembly->commands, ASSEMBLY_REG_DX);
            strcat(disassembly->commands, "\n");
            (*number_of_cmd)++;

            break;
        default :
            color_printf(RED_TEXT, BOLD, "Not a register: %d\n", cmd);
            warning(false, VALUE_ERROR);
    }
}

TYPE_OF_ERROR output_cmds_to_asm(const char* filename, const disassembly_cmd_array* disassembly)
{
    check_expression(disassembly != NULL, POINTER_IS_NULL);

    FILE* asm_file = fopen(filename, "w");

    if (asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\number", filename); //TODO rename enum

        return FILE_OPEN_ERROR;
    }

    fprintf(asm_file, "%s", disassembly->commands);

    return SUCCESS;
}
