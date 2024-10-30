#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "assembly.h"
#include "text_processing.h"
#include "debug_macros.h"

//TODO Static library .a
//TODO Difference between static and dynamic libraries - read about it
//TODO How to make good submodule .h

int main(int argc, char** argv)
{
    assembly_cmd_array assembly = {};
    char* input_filename        = NULL;
    char* output_filename       = NULL;
    catch_filenames(argc, argv, &input_filename, &output_filename);
    // printf("%s\n", input_filename);
    // printf("%s", output_filename);
    fill_bin_cmds_array_bytes(input_filename,  &assembly);
    output_cmds_to_bin (output_filename, &assembly);

    return 0;
}

TYPE_OF_ERROR fill_bin_cmds_array_bytes(const char* filename, assembly_cmd_array* assembly)
{
    check_expression(assembly != NULL, POINTER_IS_NULL);

    FILE* asm_file = fopen(filename, "r");

    if (asm_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename);

        warning(false, FILE_OPEN_ERROR);
    }

    size_t size_of_buffer = 0;
    size_of_text(filename, &(size_of_buffer));

    // $DEBUG("%lu", size_of_buffer);

    char* buffer = (char*)calloc(size_of_buffer, sizeof(char));
    warning(buffer, CALLOC_ERROR);

    fread(buffer, sizeof(char), size_of_buffer, asm_file);
    printf("countCommands:\n");
    count_cmds(buffer, size_of_buffer, &(assembly->size_of_commands_array));

    char cmd[MAX_CMD_SIZE] = "";
    // char arg[MAX_CMD_SIZE] = "";

    char** asm_commands = (char**)calloc(assembly->size_of_commands_array, sizeof(char*));
    warning(asm_commands, CALLOC_ERROR);

    // $DEBUG("%lu", assembly->size_of_commands_array);

    fill_commands(buffer, assembly->size_of_commands_array, asm_commands);

    assembly->commands = (char*)calloc(assembly->size_of_commands_array, sizeof(int));
    warning(assembly->commands, CALLOC_ERROR);

    int    number_of_cmd         = 0;
    int    value_of_cmd          = 0;
    int    is_number             = 0;
    int    number_of_compilation = 0;
    char** begin_of_asm_commands = asm_commands;
    $DEBUG("%c", **begin_of_asm_commands);
    char** size_of_asm           = begin_of_asm_commands + assembly->size_of_commands_array - 1;
    while(asm_commands < size_of_asm)
    {
        scan_command(*asm_commands, &cmd);
        $DEBUG("%c", **begin_of_asm_commands);
        if(!strcmp(ASSEMBLY_PUSH, cmd)) // TODO strcmp == 0
        {
            printf("%s - CMD\n", cmd);
            create_cmd_description(assembly, &asm_commands, &number_of_cmd, DISASSEMBLY_PUSH);
            printf("%c\n", **asm_commands);
        }
        else if(!strcmp(ASSEMBLY_POP, cmd))
        {
            printf("%s - CMD\n", cmd);
            create_cmd_description(assembly, &asm_commands, &number_of_cmd, DISASSEMBLY_POP);
        }
        else if(!strcmp(ASSEMBLY_ADD, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_ADD;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_SUB, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_SUB;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_DIV, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_DIV;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_MUL, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_MUL;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_IN, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_IN;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_OUT, cmd))
        {
            printf("%s - CMD\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_OUT;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_JA, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JA;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(!strcmp(ASSEMBLY_JAE, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JAE;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(!strcmp(ASSEMBLY_JB, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JB;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(!strcmp(ASSEMBLY_JBE, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JBE;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(!strcmp(ASSEMBLY_JE, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JE;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(!strcmp(ASSEMBLY_JNE, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JNE;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);

        }
        else if(!strcmp(ASSEMBLY_JMP, cmd))
        {
            printf("%s - JMP\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_JMP;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(!strcmp(ASSEMBLY_CALL, cmd))
        {
            printf("%s - CALL\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_CALL;
            asm_commands++;

            scan_command(*asm_commands, &cmd);

            if (number_of_compilation) process_label(assembly, number_of_cmd, cmd);

            asm_commands++;
            number_of_cmd += (int)sizeof(int);
        }
        else if(!strcmp(ASSEMBLY_RETURN, cmd))
        {
            printf("%s - RET\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_RETURN;
            asm_commands++;
        }
        else if(!strcmp(ASSEMBLY_HLT, cmd))
        {
            printf("%s - HLT\n", cmd);
            assembly->commands[number_of_cmd++] = DISASSEMBLY_HLT;
            asm_commands++;
        }
        else if(find_elem(cmd, assembly->tags, assembly->size_of_labels_array) && number_of_compilation == 0)
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: Duplicate \"%s\" label.\n", cmd);

            warning(false, VALUE_ERROR);
        }
        else if(cmd[strlen(cmd) - 1] == LABEL_NAME_ENDING)
        {
            if (number_of_compilation == 0)
            {
                printf("%s - LABEL_NAME\n", cmd);

                strncpy(assembly->tags[assembly->size_of_labels_array].name, cmd, MAX_CMD_SIZE); //TODO MAX_CMD_SIZE

                assembly->tags[assembly->size_of_labels_array].index_to_jmp = number_of_cmd;

                (assembly->size_of_labels_array)++;
            }
            asm_commands++;
        }
        else
        {
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't find \"%s\" command.\n", cmd);
            color_printf(RED_TEXT, BOLD, "Command wrong or too long, MAX_CMD_SIZE = %lu\n", MAX_CMD_SIZE);

            warning(false, VALUE_ERROR);
        }
        if((asm_commands == begin_of_asm_commands + assembly->size_of_commands_array - 1) && number_of_compilation == 0)
        {
            printf("End of first compilation\n");
            printf("%c\n", **(asm_commands - 1));
            number_of_compilation++;
            asm_commands  = begin_of_asm_commands;
            number_of_cmd = 0;
            value_of_cmd  = 0;
            is_number     = 0;
            memset(cmd, 0, MAX_CMD_SIZE);
            printf("%c - end\n", **begin_of_asm_commands);
        }
    }
    assembly->size_of_commands_array = number_of_cmd;
    fclose(asm_file);

    return SUCCESS;
}

TYPE_OF_ERROR create_cmd_description(assembly_cmd_array* assembly, char*** asm_commands,
                                     int* number_of_cmd, CMDS_DISASSEMBLY disassembly_cmd)
{
    //ASSEMBLY->COMMANDS point on command
    check_expression(asm_commands, POINTER_IS_NULL);
    check_expression(assembly,     POINTER_IS_NULL);

    char register_value[2] = "";
    int  int_value         = 0;
    char* begin_of_line = **asm_commands;
    $DEBUG("%c", ***asm_commands);
    assembly->commands[(*number_of_cmd)] |= disassembly_cmd;
    **asm_commands = (strchr(**asm_commands, ' ') + 1);
    if((**asm_commands)[0] == '[')
    {
        assembly->commands[(*number_of_cmd)] |= RAM;
        if(sscanf(**asm_commands, "[%s + %d]", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;
            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%s - %d]", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%d + %2s]", &int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "[%d - %2s]",&int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
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
                color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't PUSH / POP this"
                             "lement: %50[^\n]\n", **asm_commands);
                //TODO test this shit
                warning(false, VALUE_ERROR);
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
            color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't POP this"
                         "element: \"%50[^\n]\".\n", register_value);

            warning(false, VALUE_ERROR);
        }
    }
    else if(disassembly_cmd == DISASSEMBLY_PUSH)
    {
        $DEBUG("%c", ***asm_commands);
        if(sscanf(**asm_commands, "%s + %d", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%s - %d", register_value, &int_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d + %s", &int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d - %s",&int_value, register_value) == 2)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER | CONSTANT;
            (*number_of_cmd)++;

            int_value *= -1;
            process_register(assembly, number_of_cmd, register_value);
            memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%d", &int_value) == 1)
        {
            // assembly->commands[(*number_of_cmd)] |= CONSTANT;
            // (*number_of_cmd)++;
            // memcpy(&(assembly->commands[(*number_of_cmd)]), &int_value, sizeof(int));
        }
        else if(sscanf(**asm_commands, "%2s", register_value) == 1)
        {
            assembly->commands[(*number_of_cmd)] |= REGISTER;
            (*number_of_cmd)++;

            process_register(assembly, number_of_cmd, register_value);
        }
        else
        {
                color_printf(RED_TEXT, BOLD, "Syntax error in assembly: can't PUSH this"
                             "element: \"%50[^\n]\".\n", **asm_commands);
                //TODO test this shit
                warning(false, VALUE_ERROR);
        }
    }
    else
    {
        warning(false, PROGRAM_ERROR);
    }

    (*number_of_cmd) += (int)sizeof(int);
    (**asm_commands)   = begin_of_line;
    (*asm_commands)++;

    return SUCCESS;
}

bool find_elem(char* elem, labels* array, int size_of_array)
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
    check_expression(assembly,      POINTER_IS_NULL);
    check_expression(number_of_cmd, POINTER_IS_NULL);
    check_expression(register_value,POINTER_IS_NULL);

    if(!strcmp(register_value, ASSEMBLY_REG_AX))
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_AX;
    }
    else if(!strcmp(register_value, ASSEMBLY_REG_BX))
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_BX;
    }
    else if(!strcmp(register_value, ASSEMBLY_REG_CX))
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_CX;
    }
    else if(!strcmp(register_value, ASSEMBLY_REG_DX))
    {
        assembly->commands[(*number_of_cmd)] |= DISASSEMBLY_REG_DX;
    }
    else
    {
        color_printf(RED_TEXT, BOLD, "Wrong argument: %s\n", register_value);

        warning(false, VALUE_ERROR);
    }
    (*number_of_cmd) += (int)sizeof(int);

    return SUCCESS;
}

TYPE_OF_ERROR process_label(assembly_cmd_array* assembly, int number_of_cmd, char* cmd)
{
    check_expression(assembly,      POINTER_IS_NULL);
    check_expression(cmd,           POINTER_IS_NULL);

    size_t index_of_label = 0;
    if(cmd[strlen(cmd) - 1] == LABEL_NAME_ENDING)
    {
        for(index_of_label = 0; index_of_label < assembly->size_of_labels_array; index_of_label++)
        {
            if (!strcmp(cmd, assembly->tags[index_of_label].name))
            {
                memcpy(&(assembly->commands[number_of_cmd]), &(assembly->tags[index_of_label].index_to_jmp), sizeof(int));
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

    return SUCCESS;
}

TYPE_OF_ERROR output_cmds_to_bin(const char* filename, const assembly_cmd_array* assembly) //TODO create file if doesn't exist
{
    check_expression(assembly != NULL, POINTER_IS_NULL);

    FILE* bin = fopen(filename, "wb");

    if (bin == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename); //TODO rename enum

        return FILE_OPEN_ERROR;
    }

    fwrite(assembly->commands, sizeof(char), assembly->size_of_commands_array, bin);

    return SUCCESS;
}
