#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "commands.h"
#include "assembly.h"
#include "size_of_text.h"

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

    size_of_text(filename, &(assembly->size_of_commands_array));
    assembly->commands           = (int*)calloc(MAX_NUMBER_OF_CMDS, sizeof(int));

    warning(assembly->commands != NULL, (int)CALLOC_ERROR);

    int    number_of_cmd         = 0;
    int    value_of_cmd          = 0;
    int    is_number             = 0;
    int    number_of_compilation = 0;
    char   cmd[MAX_CMD_SIZE + 1] = ""; //+1 for \0 symbol

    while(number_of_cmd < MAX_NUMBER_OF_CMDS)
    {
        fscanf(asm_file, "%15s", &cmd); //TODO define to remove magic number 15
        if(!strcmp(ASSEMBLY_PUSH, cmd))
        {
            // printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_PUSH;

            is_number = fscanf(asm_file, "%d", &value_of_cmd);
            if (is_number)
            {
                assembly->commands[number_of_cmd++]   = value_of_cmd;
            }
            else
            {
                fscanf(asm_file, "%15s", &cmd);
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
                fscanf(asm_file, "%15s", &cmd);
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
        else if(!strcmp(ASSEMBLY_JA, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JA;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;
        }
        else if(!strcmp(ASSEMBLY_JAE, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JAE;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;

        }
        else if(!strcmp(ASSEMBLY_JB, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JB;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;

        }
        else if(!strcmp(ASSEMBLY_JBE, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JBE;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;

        }
        else if(!strcmp(ASSEMBLY_JE, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JE;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;

        }
        else if(!strcmp(ASSEMBLY_JNE, cmd))
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JNE;

            fscanf(asm_file, "%15s", &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            number_of_cmd++;

        }
        else if(!strcmp(ASSEMBLY_HLT, cmd))
        {
            // printf("%s\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_HLT;

            if (number_of_compilation) break;

            number_of_compilation++;
            number_of_cmd          = 0;
            value_of_cmd           = 0;
            is_number              = 0;
            memset(cmd, 0, MAX_CMD_SIZE + 1);

            rewind(asm_file);
        }
        else if(cmd[strlen(cmd) - 1] == LABEL_NAME_ENDING)
        {
            if (number_of_compilation == 0)
            {
                strncpy(assembly->tags[assembly->size_of_labels_array].name, cmd, MAX_CMD_SIZE + 1); //TODO delete +1
                assembly->tags[assembly->size_of_labels_array].index_to_jmp = number_of_cmd;
                printf("%s ",   assembly->tags[assembly->size_of_labels_array].name);
                printf("%d\n", assembly->tags[assembly->size_of_labels_array].index_to_jmp);
                (assembly->size_of_labels_array)++;
            }
        }
        else //TODO add line of error
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't find %s command. ", cmd);
            color_printf(RED_TEXT, BOLD, "Command wrong or too long, MAX_CMD_SIZE = %lu\n", MAX_CMD_SIZE);

            warning(false, VALUE_ERROR);
        }
    }
    if(assembly->commands[number_of_cmd - 1] != DISASSEMBLY_HLT)
    {
        color_printf(RED_TEXT, BOLD, "Syntax error in assembly: too many commands. ");
        color_printf(RED_TEXT, BOLD, "Maximum number of commands: MAX_NUMBER_OF_CMDS = %lu\n", MAX_NUMBER_OF_CMDS);

        warning(false, VALUE_ERROR);
    }
    assembly->size_of_commands_array = number_of_cmd;

    for(int i = 0; i < assembly->size_of_commands_array; i++)
    {
        printf("%d - cmd number %d\n", assembly->commands[i], i);
    }

    fclose(asm_file);

    return SUCCESS;
}

void process_register(CMDS_DISASSEMBLY command, assembly_cmd_array* assembly, int* number_of_cmd, char cmd[])
{
    (*number_of_cmd)--;
    assembly->commands[(*number_of_cmd)++] = command;

    if(!strcmp(cmd, ASSEMBLY_REG_AX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_AX;
    }
    else if(!strcmp(cmd, ASSEMBLY_REG_BX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_BX;
    }
    else if(!strcmp(cmd, ASSEMBLY_REG_CX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_CX;
    }
    else if(!strcmp(cmd, ASSEMBLY_REG_DX))
    {
        assembly->commands[(*number_of_cmd)++] = DISASSEMBLY_REG_DX;
    }
    else
    {
        color_printf(RED_TEXT, BOLD, "You trying to PUSH not a number: %s\n", cmd);
        warning(false, VALUE_ERROR);
    }
}

void process_label(assembly_cmd_array* assembly, int number_of_cmd, char cmd[])
{
    size_t index_of_label = 0;
    if(cmd[strlen(cmd) - 1] == LABEL_NAME_ENDING)
    {
        for(index_of_label = 0; index_of_label < assembly->size_of_labels_array; index_of_label++)
        {
            if (!strcmp(cmd, assembly->tags[index_of_label].name))
            {
                assembly->commands[number_of_cmd] = assembly->tags[index_of_label].index_to_jmp;

                printf("%d - index in cmd\n", assembly->commands[number_of_cmd]);

                break;
            }
        }
        if(index_of_label == assembly->size_of_labels_array)
        {
            color_printf(RED_TEXT, BOLD, "This label doesn't exist: %s\n", cmd);
            warning(false, VALUE_ERROR);
        }
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
