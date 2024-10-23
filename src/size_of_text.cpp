#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "stack_public.h"

TYPE_OF_ERROR size_of_text(const char* filename, size_t* size_of_commands_array)
{
    check_expression(filename               != NULL, POINTER_IS_NULL);
    check_expression(size_of_commands_array != NULL, POINTER_IS_NULL);

    struct stat buf = {};

    int stat_value_check = stat(filename, &buf);

    warning(stat_value_check != -1, STAT_ERROR);

    *size_of_commands_array = (size_t)buf.st_size / sizeof(stack_elem);

    return SUCCESS;
}
