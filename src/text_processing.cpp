#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string.h>

#include "custom_asserts.h"
#include "stack_public.h"
#include "debug_macros.h"
#include "text_processing.h"
#include "commands.h"

static const char assembly_source      [] = "src/assembly.cpp";
static const char processor_source     [] = "src/processor.cpp";

static const char default_assembly_file[] = "asm/assembly.asm";
static const char default_bin_file     [] = "bin/spu_commands.bin";

TYPE_OF_ERROR process_filenames(int argc, char** argv, char** input_filename,
                             char** output_filename, const char* source_filename)
{
    if(argc == 3)
    {
        process_flag(1, argv, input_filename, output_filename);
    }
    else if(argc == 5)
    {
        process_flag(1, argv, input_filename, output_filename);
        process_flag(3, argv, input_filename, output_filename);
    }

    if(strcmp(source_filename, assembly_source) == 0) //TODO make source consts
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, default_assembly_file);
        }
        if(*output_filename == NULL)
        {
            set_default_filename(output_filename, default_bin_file);
        }
    }
    else if(strcmp(source_filename, processor_source) == 0)
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, default_bin_file);
        }
    }
    else
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, default_bin_file);
        }
        if(*output_filename == NULL)
        {
            set_default_filename(output_filename, default_assembly_file);
        }
    }


    return SUCCESS;
}

TYPE_OF_ERROR process_flag(size_t number_of_flag, char** argv, char** input_filename, char** output_filename)
{
    if(strcmp(argv[number_of_flag], "--input") == 0)
    {
        size_t size_of_filename = strlen(argv[number_of_flag + 1]);
        *input_filename         = (char*)calloc(size_of_filename, sizeof(char));

        warning(*input_filename, CALLOC_ERROR);

        strcpy(*input_filename, argv[number_of_flag + 1]);
    }
    else if(strcmp(argv[number_of_flag], "--output") == 0) //Consts
    {
        size_t size_of_filename = strlen(argv[number_of_flag + 1]);
        *output_filename        = (char*)calloc(size_of_filename, sizeof(char));

        warning(*output_filename, CALLOC_ERROR);

        strcpy(*output_filename, argv[number_of_flag + 1]);
    }

    return SUCCESS;
}

TYPE_OF_ERROR set_default_filename(char** filename, const char* source_filename)
{
    size_t size_of_filename = strlen(source_filename);
    *filename               = (char*)calloc(size_of_filename + 1, sizeof(char));

    warning(*filename, CALLOC_ERROR);

    strcpy(*filename, source_filename);
    strcat(*filename, "\0");

    return SUCCESS;
}

TYPE_OF_ERROR size_of_text(const char* filename, size_t* size_of_buffer)
{
    check_expression(filename      , POINTER_IS_NULL);
    check_expression(size_of_buffer, POINTER_IS_NULL);

    struct stat buf = {};

    int stat_value_check = stat(filename, &buf);

    warning(stat_value_check != -1, STAT_ERROR);

    *size_of_buffer = (size_t)buf.st_size;

    return SUCCESS;
}

TYPE_OF_ERROR count_cmds(char* buffer, size_t size_of_text, size_t* number_of_cmds)
{
    check_expression(buffer, POINTER_IS_NULL);

    char* current_char          = buffer;
    char  command[MAX_CMD_SIZE] = "";

    while(current_char < buffer + size_of_text)
    {
        if(*current_char == '\n' && *(current_char + 1) != '\n')
        {
            (*number_of_cmds)++;
        }
        current_char++;
    }
    (*number_of_cmds)++;

    return SUCCESS;
}

TYPE_OF_ERROR fill_commands(char* buffer, size_t number_of_cmds, char** asm_commands)
{
    check_expression(buffer,       POINTER_IS_NULL);
    check_expression(asm_commands, POINTER_IS_NULL);

    size_t number_of_line        = 0;
    char* current_char           = buffer;
    asm_commands[number_of_line] = current_char;
    number_of_line++;

    while(number_of_line < number_of_cmds - 1)
    {
        if(*current_char == '\n')
        {
            while((*(current_char + 1) == '\n') || (*(current_char + 1) == '\t') || (*(current_char + 1) == ' '))
            {
                current_char++;
            }
            asm_commands[number_of_line] = current_char + 1;
            number_of_line++;
        }
        current_char++;
    }

    return SUCCESS;
}
