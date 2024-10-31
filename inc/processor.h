#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "commands.h"
#include "stack_public.h"

struct processor{
    stack*      st                     = NULL;
    stack*      functions_return_codes = NULL;
    char*       commands               = NULL;
    stack_elem* ram                    = NULL;
    stack_elem* registers              = NULL;
};

stack_elem* get_arg(processor* proc, int* ip, CMDS_DISASSEMBLY command,
                    int**  shift);
TYPE_OF_ERROR draw(processor* proc);

#endif
