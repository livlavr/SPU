#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string.h>

#include "custom_asserts.h"
#include "stack_public.h"
#include "debug_macros.h"
#include "text_processing.h"

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

    if(strcmp(source_filename, "src/assembly.cpp") == 0)
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, "src/assembly.asm");
        }
        if(*output_filename == NULL)
        {
            set_default_filename(output_filename, "src/spu_commands.bin");
        }
    }
    else if(strcmp(source_filename, "src/processor.cpp") == 0)
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, "src/spu_commands.bin");
        }
    }
    else
    {
        if(*input_filename == NULL)
        {
            set_default_filename(input_filename, "src/spu_commands.bin");
        }
        if(*output_filename == NULL)
        {
            set_default_filename(output_filename, "src/assembly.asm");
        }
    }


    return SUCCESS;
}

TYPE_OF_ERROR process_flag(size_t number_of_flag, char** argv, char** input_filename, char** output_filename)
{
    if(strcmp(argv[number_of_flag], "--input") == 0)
    {
        size_t size_of_filename = sizeof(argv[number_of_flag + 1]) / sizeof(char);
        *input_filename = (char*)calloc(size_of_filename, sizeof(char));

        warning(*input_filename, CALLOC_ERROR);

        strcpy(*input_filename, argv[number_of_flag + 1]);
    }
    else if(strcmp(argv[number_of_flag], "--output") == 0) //Consts
    {
        size_t size_of_filename = sizeof(argv[number_of_flag + 1]) / sizeof(char);
        *output_filename = (char*)calloc(size_of_filename, sizeof(char));

        warning(*output_filename, CALLOC_ERROR);

        strcpy(*output_filename, argv[number_of_flag + 1]);
    }

    return SUCCESS;
}

TYPE_OF_ERROR set_default_filename(char** filename, const char* source_filename)
{
    size_t size_of_filename = sizeof(source_filename) / sizeof(char);
    *filename = (char*)calloc(size_of_filename, sizeof(char));
    warning(*filename, CALLOC_ERROR);
    strcpy(*filename, source_filename);

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

    char* current_char  = buffer;

    while (current_char < buffer + size_of_text - 1)
    {
        if (*(current_char + 1) != '\n' && *(current_char + 1) != ' ' &&
            *(current_char + 1) != '\t' && *(current_char + 1) != '\0')
        {
            if (*current_char == '\n' || *current_char == ' ' || *current_char == '\t')
            {
                (*number_of_cmds)++;
            }
        }
        current_char++;
    }
    (*number_of_cmds)++;

    return SUCCESS;
}

TYPE_OF_ERROR fill_commands(char* buffer, size_t size_of_text, char** asm_commands)
{
    check_expression(buffer,       POINTER_IS_NULL);
    check_expression(asm_commands, POINTER_IS_NULL);

    // $DEBUG("%s", buffer);
    // $DEBUG("%lu", size_of_text);

    int   number_of_cmd           = 0;
    char* current_char            = buffer;
    asm_commands[number_of_cmd++] = buffer;
    current_char++;

    while(current_char < buffer + size_of_text - 1)
    {
        if(*current_char == '\n' || *current_char == ' ' ||
                *current_char == '\t' || *current_char == '\0')
        {
            if(*(current_char + 1) != '\n' && *(current_char + 1) != ' ' && *(current_char + 1) != '\t')
            {
                asm_commands[number_of_cmd++] = current_char + 1;
            }
        }
        current_char++;
    }

    return SUCCESS;
}
