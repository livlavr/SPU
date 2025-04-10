#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "error_types.h"
#include "custom_asserts.h"
#include "disassembly.h"
#include "commands.h"
#include "text_processing.h"
#include "stack_public.h"
#include "debug_macros.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main(int argc, char** argv)
{
    disassembly_cmd_array disassembly = {};
    char* input_filename              = NULL;
    char* output_filename             = NULL;
    catch_filenames(argc, argv, &input_filename, &output_filename);
    fill_asm_cmds_array(input_filename,  &disassembly);
    output_cmds_to_asm (output_filename, &disassembly);

    return 0;
}

TYPE_OF_ERROR fill_asm_cmds_array(const char* filename, disassembly_cmd_array* disassembly)
{
    FILE* bin_file = fopen(filename, "rb");

    if(bin_file == NULL)
    {
        printf("File with %s name doesn't exist\n", filename);

        return FILE_OPEN_ERROR;
    }

    size_of_text(filename, &(disassembly->size_of_commands_array)); //TODO pizdec disassembler /sizeof(stack_elem)

    disassembly->size_of_commands_array /= sizeof(stack_elem);

    int  number_of_cmd                = 0;
    int  number_of_label              = 0;
    int  number_of_compilation        = 0;
    char value_of_cmd[MAX_CMD_SIZE]   = "";
    int  bin_commands[disassembly->size_of_commands_array] = {};
    int  size_of_labels_array         = disassembly->size_of_commands_array / 2 + 1;
    int  labels[size_of_labels_array] = {};

    fill_poison(labels, size_of_labels_array, POISON);

    disassembly->commands = (char*)calloc(disassembly->size_of_commands_array * MAX_CMD_SIZE, sizeof(char));

    fread(bin_commands, sizeof(int), disassembly->size_of_commands_array, bin_file);

    fclose(bin_file);

    while(number_of_cmd < disassembly->size_of_commands_array)
    {
        if(find_elem(number_of_cmd, labels, size_of_labels_array))
        {
            int_to_str(number_of_cmd, value_of_cmd);
            strcat(disassembly->commands, value_of_cmd);
            strcat(disassembly->commands, ":");
            strcat(disassembly->commands, "\n");
        }
        if(number_of_cmd == disassembly->size_of_commands_array - 1)
        {
            if(number_of_compilation == 0)
            {
                number_of_compilation++;
                number_of_cmd   = 0;
                number_of_label = 0;
                memset(disassembly->commands, 0, disassembly->size_of_commands_array * MAX_CMD_SIZE);//TODO BAD
            }
        }
        switch(bin_commands[number_of_cmd])
        {
            case DISASSEMBLY_PUSH:
                strcat(disassembly->commands, ASSEMBLY_PUSH);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_POP:
                strcat(disassembly->commands, ASSEMBLY_POP);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_ADD:
                strcat(disassembly->commands, ASSEMBLY_ADD);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_SUB:
                strcat(disassembly->commands, ASSEMBLY_SUB);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_DIV:
                strcat(disassembly->commands, ASSEMBLY_DIV);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_MUL:
                strcat(disassembly->commands, ASSEMBLY_MUL);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_OUT:
                strcat(disassembly->commands, ASSEMBLY_OUT);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_IN:
                strcat(disassembly->commands, ASSEMBLY_IN);
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JA:
                strcat(disassembly->commands, ASSEMBLY_JA);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JAE:
                strcat(disassembly->commands, ASSEMBLY_JAE);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JB:
                strcat(disassembly->commands, ASSEMBLY_JB);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JBE:
                strcat(disassembly->commands, ASSEMBLY_JBE);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JE:
                strcat(disassembly->commands, ASSEMBLY_JE);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_JNE:
                strcat(disassembly->commands, ASSEMBLY_JNE);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                // printf("%s", disassembly->commands);
                number_of_cmd++;

                break;

            case DISASSEMBLY_CALL:
                strcat(disassembly->commands, ASSEMBLY_CALL);
                strcat(disassembly->commands, " ");
                number_of_cmd++;

                labels[number_of_label++] = bin_commands[number_of_cmd];
                int_to_str(bin_commands[number_of_cmd], value_of_cmd);
                strcat(disassembly->commands, value_of_cmd);
                strcat(disassembly->commands, ":");
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

                break;

            case DISASSEMBLY_RETURN:
                strcat(disassembly->commands, ASSEMBLY_RETURN);
                strcat(disassembly->commands, "\n");
                number_of_cmd++;

                break;

            case DISASSEMBLY_HLT:
                strcat(disassembly->commands, ASSEMBLY_HLT);
                strcat(disassembly->commands, "\n");
                printf("%s", disassembly->commands);
                number_of_cmd++;

                break;
            default:
                color_printf(RED_TEXT, BOLD, "%d\n", bin_commands[number_of_cmd]);

                customAssert(false, VALUE_ERROR);
        }
    }

    return SUCCESS;
}

bool find_elem(int number, int* array, int size_of_array)
{
    for(int index = 0; index < size_of_array; index++)
    {
        if(number == array[index])
        {
            return true;

            break;
        }
    }
    return false;
}

TYPE_OF_ERROR fill_poison(int* array, int size, int poison)
{
    warning(array, POINTER_IS_NULL);

    for(int index = 0; index < size; index ++)
    {
        array[index] = poison;
    }

    return SUCCESS;
}

TYPE_OF_ERROR int_to_str(int number, char* str)
{
    warning(str, POINTER_IS_NULL);

    int number_of_char = 0;
    int sign           = number;

    if(number == 0)
    {
        str[number_of_char++]   = '0';
    }
    if(number < 0)
    {
        number = -number;
    }
    while(number > 0)
    {
        str[number_of_char++] = number % 10 + '0';
      	number               /= 10;
    }

    if(sign < 0)
    {
        str[number_of_char++] = '-';
    }

    str[number_of_char] = '\0';

    reverse_str(str, number_of_char);

    return SUCCESS;
}

inline void reverse_str(char* str, int length)
{
    for(int left_char = 0, right_char = length - 1; left_char < right_char; left_char++, right_char--)
    {
        char switcher   = str[left_char];
        str[left_char]  = str[right_char];
        str[right_char] = switcher;
    }
}

TYPE_OF_ERROR process_register(const char* command, disassembly_cmd_array* disassembly, int* number_of_cmd, int cmd)
{
    warning(disassembly,   POINTER_IS_NULL);
    warning(number_of_cmd, POINTER_IS_NULL);

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
            customAssert(false, VALUE_ERROR);
    }

    return SUCCESS;
}

TYPE_OF_ERROR output_cmds_to_asm(const char* filename, const disassembly_cmd_array* disassembly)
{
    warning(disassembly, POINTER_IS_NULL);

    FILE* asm_file = fopen(filename, "w");

    if(asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\number", filename); //TODO rename enum

        return FILE_OPEN_ERROR;
    }

    fprintf(asm_file, "%s", disassembly->commands);

    return SUCCESS;
}
