#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "commands.h"
#include "assembly.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main()
{
    assembly_cmd_array assembly = {};
    fill_bin_cmds_array("src/assembly.asm"    , &assembly);
    output_cmds_to_bin ("src/spu_commands.bin", &assembly);

    return 0;
}

TYPE_OF_ERROR fill_bin_cmds_array(const char* filename, assembly_cmd_array* assembly)
{
    check_expression(assembly != NULL, POINTER_IS_NULL);

    FILE* asm_file = fopen(filename, "r");

    if (asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename);

        return FILE_OPEN_ERROR;
    }

    size_of_text(filename, assembly);
    assembly->commands           = (int*)calloc(MAX_NUMBER_OF_CMDS, sizeof(int));

    warning(assembly->commands != NULL, (int)CALLOC_ERROR);

    size_t number_of_cmd     = 0;
    int    value_of_cmd      = 0;
    int    is_number         = 0;
    char   cmd[MAX_CMD_SIZE] = ""; //TODO if marker more then 15 --> syntax error

    while(number_of_cmd < MAX_NUMBER_OF_CMDS)
    {
        fscanf(asm_file, "%s", &cmd);
        if(!strcmp(ASSEMBLY_PUSH, cmd))
        {
            // printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_PUSH;

            is_number = fscanf(asm_file, "%d", &value_of_cmd);
            if (is_number) //SAME FOR REGISTER IN DISASM
            {
                assembly->commands[number_of_cmd++]   = value_of_cmd;
            }
            else
            {
                fscanf(asm_file, "%s", &cmd);
                process_register(DISASSEMBLY_PUSHR, assembly, &number_of_cmd, cmd);
            }
        }

        else if(!strcmp(ASSEMBLY_POP, cmd))
        {
            // printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_POP;

            is_number = fscanf(asm_file, "%d", &value_of_cmd);
            // printf("%d - NUMBER\n", value_of_cmd);

            if (is_number)
            {
                assembly->commands[number_of_cmd++]   = value_of_cmd;
            }
            else
            {
                fscanf(asm_file, "%s", &cmd);
                process_register(DISASSEMBLY_POPR, assembly, &number_of_cmd, cmd);
            }
        }

        else if(!strcmp(ASSEMBLY_ADD, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_ADD;
        }

        else if(!strcmp(ASSEMBLY_SUB, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_SUB;
        }

        else if(!strcmp(ASSEMBLY_DIV, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_DIV;
        }

        else if(!strcmp(ASSEMBLY_OUT, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_OUT;
        }

        else if(!strcmp(ASSEMBLY_HLT, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_HLT;

            break;
        }

        else
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't find %s command\n", cmd);

            exit(VALUE_ERROR);
        }
    }
    assembly->size_of_commands_array = number_of_cmd;

    fclose(asm_file);

    return SUCCESS;
}

TYPE_OF_ERROR size_of_text(const char* filename, assembly_cmd_array* assembly)
{
    check_expression(filename    != NULL, POINTER_IS_NULL);
    check_expression(assembly    != NULL, POINTER_IS_NULL);

    struct stat buf = {};

    int stat_value_check = stat(filename, &buf);

    warning(stat_value_check != -1, STAT_ERROR);

    assembly->size_of_commands_array = (size_t)buf.st_size / sizeof(stack_t);

    return SUCCESS;
}

void process_register(CMDS_DISASSEMBLY command, assembly_cmd_array* assembly, size_t* number_of_cmd, char cmd[])
{
    (*number_of_cmd)--;
    assembly->commands[(*number_of_cmd)++] = command;

    if (!strcmp(cmd, ASSEMBLY_REG_AX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_AX;
    }
    else if (!strcmp(cmd, ASSEMBLY_REG_BX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_BX;
    }
    else if (!strcmp(cmd, ASSEMBLY_REG_CX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_CX;
    }
    else if (!strcmp(cmd, ASSEMBLY_REG_DX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_DX;
    }
    else
    {
        color_printf(RED_TEXT, BOLD, "You trying to PUSH not a number: %s", cmd);
        warning(false, VALUE_ERROR);
    }
}

TYPE_OF_ERROR output_cmds_to_bin(const char* filename, const assembly_cmd_array* assembly)
{
    check_expression(assembly != NULL, POINTER_IS_NULL);

    FILE* bin = fopen(filename, "wb");

    if (bin == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum

        return FILE_OPEN_ERROR;
    }

    fwrite(assembly->commands, sizeof(int), assembly->size_of_commands_array, bin);

    return SUCCESS;
}
