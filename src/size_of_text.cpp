#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "stack_public.h"
#include "debug_macros.h"

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
    $DEBUG("%c", asm_commands[number_of_cmd - 1][0]);
    current_char++;

    while(current_char < buffer + size_of_text - 1)
    {
        if(*current_char == '\n' || *current_char == ' ' ||
                *current_char == '\t' || *current_char == '\0')
        {
            if(*(current_char + 1) != '\n' && *(current_char + 1) != ' ' && *(current_char + 1) != '\t')
            {
                asm_commands[number_of_cmd++] = current_char + 1;

                $DEBUG("%c", asm_commands[number_of_cmd - 1][0]);
            }
        }
        current_char++;
    }

    return SUCCESS;
}
