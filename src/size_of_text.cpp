#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "stack_public.h"

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

TYPE_OF_ERROR count_lines(char* buffer, size_t size_of_text, size_t* number_of_lines)
{
    check_expression(buffer, POINTER_IS_NULL);

    char* current_char  = buffer;

    while (current_char < buffer + size_of_text)
    {
        if (*current_char == '\n')
        {
            (*number_of_lines)++;
        }
        current_char++;
    }
    (*number_of_lines)++;

    return SUCCESS;
}
