#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "commands.h"
#include "stack_public.h"

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL

struct processor{
    stack*      st                     = NULL;
    stack*      functions_return_codes = NULL;
    char*       commands               = NULL;
    stack_elem* ram                    = NULL;
    stack_elem* registers              = NULL;
};

char*         read_file     (int argc, char** argv);
stack_elem*   get_arg       (processor* proc, int* ip, CMDS_DISASSEMBLY command, int**  shift);
processor*    processor_ctor(char* input_buffer);
TYPE_OF_ERROR processor_dtor(processor* proc);
TYPE_OF_ERROR handle_program(processor* proc);
TYPE_OF_ERROR draw          (processor* proc);

#endif
