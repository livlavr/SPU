#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/stat.h>

#include "error_types.h"
#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "assembly.h"
#include "text_processing.h"
#include "debug_macros.h"

int main(int argc, char** argv)
{
    assembly_cmd_array assembly = {};
    char* input_filename        = NULL;
    char* output_filename       = NULL;
    catch_filenames(argc, argv, &input_filename, &output_filename);

    color_printf(YELLOW_COLOR, BOLD, "[ %s ] Start compilation ...\n", input_filename);

    fill_bin_cmds_array_bytes(input_filename,  &assembly);
    output_cmds_to_bin(output_filename, &assembly);

    color_printf(GREEN_COLOR, BOLD, "[ %s ] Compiled successfuly\n", input_filename);

    return 0;
}

TYPE_OF_ERROR fill_bin_cmds_array_bytes(const char* filename, assembly_cmd_array* assembly)
{
    warning(assembly, POINTER_IS_NULL);

    FILE* asm_file = fopen(filename, "r");

    if(asm_file == NULL)
    {
        color_printf(RED_COLOR, BOLD, "File with %s name doesn't exist\n", filename);

        customAssert(false, FILE_OPEN_ERROR);
    }

    size_t size_of_buffer = 0;
    size_of_text(filename, &(size_of_buffer));

    char* buffer = (char*)calloc(size_of_buffer, sizeof(char));
    customAssert(buffer, CALLOC_ERROR);

    fread(buffer, sizeof(char), size_of_buffer, asm_file);
    count_cmds(buffer, size_of_buffer, &(assembly->size_of_commands_array));


    char** asm_commands = (char**)calloc(assembly->size_of_commands_array, sizeof(char*));
    customAssert(asm_commands, CALLOC_ERROR);

    fill_commands(buffer, assembly->size_of_commands_array, asm_commands);

    assembly->commands = (char*)calloc(assembly->size_of_commands_array, sizeof(int));
    customAssert(assembly->commands, CALLOC_ERROR);

    int    number_of_cmd         = 0;
    int    value_of_cmd          = 0;
    int    is_number             = 0;
    int    is_hlt                = 0;
    int    number_of_compilation = 0;
    char   cmd[MAX_CMD_SIZE]     = "";
    char** begin_of_asm_commands = asm_commands;
    char** size_of_asm           = begin_of_asm_commands + assembly->size_of_commands_array - 1;
    int cnt = 0;
    while(asm_commands < size_of_asm)
    {
        skip_spaces(&asm_commands);
        scan_command(*asm_commands, &cmd);
        if(strcmp(ASSEMBLY_PUSH, cmd) == 0)
        {
            create_cmd_description(assembly, &asm_commands, &number_of_cmd, DISASSEMBLY_PUSH);
        }
        else if(strcmp(ASSEMBLY_POP, cmd) == 0)
        {
            create_cmd_description(assembly, &asm_commands, &number_of_cmd, DISASSEMBLY_POP);
        }
        else if(strcmp(ASSEMBLY_ADD, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_ADD;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_SUB, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_SUB;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_DIV, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_DIV;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_MUL, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_MUL;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_SQRT, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_SQRT;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_IN, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_IN;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_OUT, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_OUT;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_JA, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JA;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(strcmp(ASSEMBLY_JAE, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JAE;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(strcmp(ASSEMBLY_JB, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JB;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(strcmp(ASSEMBLY_JBE, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JBE;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(strcmp(ASSEMBLY_JE, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JE;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(strcmp(ASSEMBLY_JNE, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JNE;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(strcmp(ASSEMBLY_JMP, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JMP;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(strcmp(ASSEMBLY_CALL, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_CALL;

            if(number_of_compilation) process_label(assembly, number_of_cmd, &asm_commands);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(strcmp(ASSEMBLY_RETURN, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_RETURN;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_DRAW, cmd) == 0)
        {
            assembly->commands[number_of_cmd++] = DISASSEMBLY_DRAW;
            asm_commands++;
        }
        else if(strcmp(ASSEMBLY_HLT, cmd) == 0)
        {
            is_hlt = 1;
            assembly->commands[number_of_cmd++] = DISASSEMBLY_HLT;
            asm_commands++;
        }
        else if(find_elem(cmd, assembly->tags, assembly->size_of_labels_array) && number_of_compilation == 0)
        {
            color_printf(RED_COLOR, BOLD, "Syntax error in assembly: Duplicate \"%s\" label.\n", cmd);

            customAssert(false, VALUE_ERROR);
        }
        else if(cmd[strlen(cmd) - 1] == LABEL_NAME_ENDING)
        {
            if(number_of_compilation == 0)
            {
                strncpy(assembly->tags[assembly->size_of_labels_array].name, cmd, MAX_CMD_SIZE);
                assembly->tags[assembly->size_of_labels_array].index_to_jmp = number_of_cmd;
                (assembly->size_of_labels_array)++;
            }
            asm_commands++;
        }
        else
        {
            color_printf(RED_COLOR, BOLD, "Syntax error in assembly: can't find \"%s\" command.\n", cmd);
            color_printf(RED_COLOR, BOLD, "Command wrong or too long, MAX_CMD_SIZE = %lu\n", MAX_CMD_SIZE);

            customAssert(false, VALUE_ERROR);
        }
        if((asm_commands == begin_of_asm_commands + assembly->size_of_commands_array - 1) && number_of_compilation == 0)
        {
            number_of_compilation++;
            asm_commands  = begin_of_asm_commands;
            number_of_cmd = 0;
            value_of_cmd  = 0;
            is_number     = 0;
            memset(cmd, 0, MAX_CMD_SIZE);
        }
    }
    if(is_hlt == 0)
    {
        color_printf(RED_COLOR, BOLD, "Syntax error in assembly: there's no \"HLT\" command in program.\n");

        customAssert(false, INPUT_ERROR);
    }
    assembly->size_of_commands_array = number_of_cmd;
    fclose(asm_file);

    return SUCCESS;
}

TYPE_OF_ERROR create_cmd_description(assembly_cmd_array* assembly, char*** asm_commands,
                                     int* number_of_cmd, CMDS_DISASSEMBLY disassembly_cmd)
{
    warning(asm_commands, POINTER_IS_NULL);
    warning(assembly,     POINTER_IS_NULL);

    char register_value[2] = "";
    int  int_value         = 0;
    char* begin_of_cmd = **asm_commands;

    **asm_commands = (strchr(**asm_commands, ' ') + 1);
    skip_spaces(asm_commands);

    assembly->commands[(*number_of_cmd)] |= disassembly_cmd;

    if((**asm_commands)[0] == '[')
    {
        assembly->commands[(*number_of_cmd)] |= RAM;
        if(sscanf(**asm_commands, "[%s + %d]", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%s - %d]", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%d + %2s]", &int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%d - %2s]",&int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%d]", &int_value) == 1)
        {
            assembly->commands[(*number_of_cmd)] |= CONSTANT;
            (*number_of_cmd)++;
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%2s]", register_value) == 1)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
        }
        else
        {
                color_printf(RED_COLOR, BOLD, "Syntax error in assembly: can't PUSH / POP this"
                             "element: %50[^\n]\n", **asm_commands);
                customAssert(false, VALUE_ERROR);
        }
    }
    else if(disassembly_cmd == DISASSEMBLY_POP)
    {
        assembly->commands[(*number_of_cmd)] |= REGISTER;
        (*number_of_cmd)++;
        if(sscanf(**asm_commands, "%2s", register_value) == 1)
        {
            process_register(assembly, number_of_cmd, register_value);
        }
        else
        {
            color_printf(RED_COLOR, BOLD, "Syntax error in assembly: can't POP this"
                         "element: \"%50[^\n]\".\n", register_value);

            customAssert(false, VALUE_ERROR);
        }
    }
    else if(disassembly_cmd == DISASSEMBLY_PUSH)
    {
        if(sscanf(**asm_commands, "%s + %d", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%s - %d", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d + %s", &int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d - %s",&int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            (*number_of_cmd) += (int)sizeof(int);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d", &int_value) == 1)
        {
            assembly->commands[(*number_of_cmd)] |= CONSTANT;
            (*number_of_cmd)++;
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%2s", register_value) == 1)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
        }
        else
        {
                color_printf(RED_COLOR, BOLD, "Syntax error in assembly: can't PUSH this"
                             "element: \"%50[^\n]\".\n", **asm_commands);
                customAssert(false, VALUE_ERROR);
        }
    }
    else
    {
        customAssert(false, PROGRAM_ERROR);
    }
    (*number_of_cmd) += (int)sizeof(int);
    (**asm_commands)  = begin_of_cmd;
    (*asm_commands)++;

    return SUCCESS;
}

inline bool find_elem(char* elem, labels* array, int size_of_array)
{
    for(int index = 0; index < size_of_array; index++)
    {
        if(strcmp(elem, array[index].name) == 0)
        {
            return true;

            break;
        }
    }

    return false;
}

TYPE_OF_ERROR process_register(assembly_cmd_array* assembly, int* number_of_cmd, char* register_value)
{
    warning(assembly,      POINTER_IS_NULL);
    warning(number_of_cmd, POINTER_IS_NULL);
    warning(register_value,POINTER_IS_NULL);

    if(strcmp(register_value, ASSEMBLY_REG_AX) == 0)
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_AX;
    }
    else if(strcmp(register_value, ASSEMBLY_REG_BX) == 0)
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_BX;
    }
    else if(strcmp(register_value, ASSEMBLY_REG_CX) == 0)
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_CX;
    }
    else if(strcmp(register_value, ASSEMBLY_REG_DX) == 0)
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_DX;
    }
    else
    {
        color_printf(RED_COLOR, BOLD, "Wrong argument: %s\n", register_value);

        customAssert(false, VALUE_ERROR);
    }
    return SUCCESS;
}

TYPE_OF_ERROR process_label(assembly_cmd_array* assembly, int number_of_cmd, char*** asm_commands)
{
    warning(assembly,     POINTER_IS_NULL);
    warning(asm_commands, POINTER_IS_NULL);

    size_t index_of_label = 0;
    char** begin_of_cmd   = *asm_commands;
    char cmd[MAX_CMD_SIZE] = "";

    **asm_commands = strchr(**asm_commands, ' ') + 1;
    skip_spaces(asm_commands);
    scan_command(**asm_commands, cmd);
    *asm_commands = begin_of_cmd;
    strcat(cmd, ":");
    for(index_of_label = 0; index_of_label < assembly->size_of_labels_array; index_of_label++)
    {
        if(strcmp(cmd, assembly->tags[index_of_label].name) == 0)
        {
            memcpy(&(assembly->commands[number_of_cmd]), &(assembly->tags[index_of_label].index_to_jmp), sizeof(int));

            break;
        }
    }
    if(index_of_label == assembly->size_of_labels_array)
    {
        color_printf(RED_COLOR, BOLD, "This label doesn't exist: %s\n", cmd);
        customAssert(false, VALUE_ERROR);
    }

    return SUCCESS;
}

TYPE_OF_ERROR output_cmds_to_bin(const char* filename, const assembly_cmd_array* assembly)
{
    warning(assembly, POINTER_IS_NULL);
    FILE* bin = fopen(filename, "wb");

    if(bin == NULL)
    {
        color_printf(RED_COLOR, BOLD, "[ Error ] File with %s name doesn't exist\n", filename);
        color_printf(YELLOW_COLOR, BOLD, "[ Hint! ] You probably didn't create a directory for the output file.\n");

        return FILE_OPEN_ERROR;
    }

    fwrite(assembly->commands, sizeof(char), assembly->size_of_commands_array, bin);

    return SUCCESS;
}

TYPE_OF_ERROR skip_spaces(char*** asm_commands)
{
    warning(asm_commands, POINTER_IS_NULL);

    while(***asm_commands == ' ' || ***asm_commands == '\t') {
        (**asm_commands)++;
    }

    return SUCCESS;
}