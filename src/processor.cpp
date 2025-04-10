#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#include "error_types.h"
#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "color_printf.h"
#include "text_processing.h"
#include "processor.h"
#include "debug_macros.h"

int main(int argc, char** argv)
{
    char* input_filename = NULL;
    catch_processor_flags(argc, argv, &input_filename);

    char* input_buffer = read_file(argc, argv);

    processor* proc = processor_ctor(input_buffer);

    handle_program(proc);

    processor_dtor(proc);
}

stack_elem* get_arg(processor* proc, int* ip, CMDS_DISASSEMBLY command, int**  shift)
{
    int format                   = (int)(proc->commands[(*ip) - 1] & BYTE_FORMAT_MASK);
    int is_reg                   = format & IS_REGISTER;
    int is_constant              = format & IS_I_CONSTANT;
    int memory                   = format & IS_MEMORY;
    stack_elem* argument_address = NULL;
    stack_elem  ip_of_argument   = 0;
    stack_elem* argument_source  = NULL;

    proc->registers[0] = 0;
    if(command == DISASSEMBLY_POP)
    {
        if(memory)
        {
            argument_source = proc->ram;
            if(is_reg)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                ip_of_argument += proc->registers[**shift];
                *ip += sizeof(int);
            }
            if(is_constant)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                ip_of_argument += **shift;
                *ip += sizeof(int);
            }
        }
        else
        {
            argument_source = proc->registers;
            memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
            ip_of_argument += **shift;
            *ip += sizeof(int);
        }

        argument_address = &(argument_source[ip_of_argument]);

        return argument_address;
    }
    else
    {
        if(memory)
        {
            argument_source = proc->ram;
            if(is_reg)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                ip_of_argument += proc->registers[**shift];
                *ip += sizeof(int);
            }
            if(is_constant)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                ip_of_argument += **shift;
                *ip += sizeof(int);
            }
            argument_address = &(argument_source[ip_of_argument]);

            return argument_address;
        }
        else
        {
            if(is_reg)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                proc->registers[0] += proc->registers[**shift];
                *ip += sizeof(int);
            }
            if(is_constant)
            {
                memcpy(*shift, &(proc->commands[*ip]), sizeof(int));
                proc->registers[0] += **shift;
                *ip += sizeof(int);
            }

            return &(proc->registers[0]);
        }
    }
}

processor* processor_ctor(char* input_buffer)
{
    customAssert(input_buffer, POINTER_IS_NULL);

    processor* proc = (processor*)calloc(1, sizeof(processor));
    stack_init(proc->st, 15);
    stack_init(proc->functions_return_codes, 5);

    proc->ram       = (stack_elem*)calloc(SIZE_OF_RAM, sizeof(stack_elem));
    proc->registers = (stack_elem*)calloc(MAX_NUMBER_OF_REGISTERS, sizeof(stack_elem));
    proc->commands  = input_buffer;

    return proc;
}

TYPE_OF_ERROR processor_dtor(processor* proc)
{
    customAssert(proc, POINTER_IS_NULL);

    stack_destroy(proc->st);
    stack_destroy(proc->functions_return_codes);

    FREE(proc->commands);
    FREE(proc->ram);
    FREE(proc->registers);
    FREE(proc);

    return SUCCESS;
}

char* read_file(int argc, char** argv)
{
    customAssert(argv, POINTER_IS_NULL);

    char* input_filename = NULL;
    catch_processor_flags(argc, argv, &input_filename);

    FILE* bin_file = fopen(input_filename, "rb");
    customAssert(bin_file, FILE_OPEN_ERROR && "Input file doesn't exist");

    size_t size_of_file = 0;
    size_of_text(input_filename, &size_of_file);

    char* input_buffer = (char*)calloc(size_of_file, sizeof(char));
    fread(input_buffer, sizeof(char), size_of_file, bin_file);

    fclose(bin_file);

    return input_buffer;
}

TYPE_OF_ERROR handle_program(processor* proc)
{
    customAssert(proc, POINTER_IS_NULL);

    stack_elem  x = 0, y = 0;
    int         ip             = 0;
    stack_elem  value_of_cmd   = 0;
    bool        hlt_not_found  = true;
    int*        shift          = (int*)calloc(1, sizeof(int));
    stack_elem* constant_value = (stack_elem*)calloc(1, sizeof(stack_elem));
    while(hlt_not_found)
    {
        switch(proc->commands[ip++] & BYTE_COMMAND_MASK)
        {
            case DISASSEMBLY_PUSH:
                value_of_cmd = *get_arg(proc, &ip, DISASSEMBLY_PUSH, &shift);
                push(proc->st, value_of_cmd);

                break;

            case DISASSEMBLY_POP:
                pop(proc->st, &x);
                *get_arg(proc, &ip, DISASSEMBLY_POP, &shift) = x;

                break;

            // TODO define DISASSEMBLY_ARITHM(ADD, +)
            case DISASSEMBLY_ADD:
                pop(proc->st, &y);
                pop(proc->st, &x);
                push(proc->st, x + y);

                break;

            case DISASSEMBLY_SUB:
                pop(proc->st, &y);
                pop(proc->st, &x);
                push(proc->st, x - y);

                break;

            case DISASSEMBLY_DIV:
                pop(proc->st, &y);
                pop(proc->st, &x);
                push(proc->st, x / y);

                break;

            case DISASSEMBLY_MUL:
                pop(proc->st, &y);
                pop(proc->st, &x);
                push(proc->st, x * y);

                break;

            case DISASSEMBLY_SQRT:
                pop(proc->st, &x);
                push(proc->st, (int)sqrt(x));

                break;

            case DISASSEMBLY_IN:
                scanf("%d", &x);
                push(proc->st, x);

                break;

            case DISASSEMBLY_OUT:
                pop(proc->st, &x);
                color_printf(GREEN_COLOR, BOLD, "RESULT: %d\n", x);

                break;

            case DISASSEMBLY_JA:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x > y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JAE:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x >= y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JB:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x < y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JBE:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x <= y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;
            // TODO define DISASSEMBLY_JUMP(JE, ==)
            case DISASSEMBLY_JE:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x == y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JNE:
                pop(proc->st, &y);
                pop(proc->st, &x);

                if(x != y)
                {
                    memcpy(shift, &(proc->commands[ip]), sizeof(int));

                    ip = *shift;
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JMP:
                memcpy(shift, &(proc->commands[ip]), sizeof(int));

                ip = *shift;

                break;

            case DISASSEMBLY_CALL:
                memcpy(shift, &(proc->commands[ip]), sizeof(int));
                ip += sizeof(int);
                push(proc->functions_return_codes, ip);
                ip = *shift;

                break;

            case DISASSEMBLY_RETURN:
                pop(proc->functions_return_codes, &x);
                ip = x;

                break;

            case DISASSEMBLY_DRAW:
                draw(proc);

                break;

            case DISASSEMBLY_HLT:
                hlt_not_found = false;

                break;
            default:
                color_printf(RED_COLOR, BOLD, "Command %d doesn't found\n", proc->commands[--ip]);

                customAssert(false, VALUE_ERROR);
        }
    }

    FREE(shift);
    FREE(constant_value);

    return SUCCESS;
}

TYPE_OF_ERROR draw(processor* proc)
{
    customAssert(proc, POINTER_IS_NULL);

    int ram_side_size = (int)sqrt(SIZE_OF_RAM);
    for(int y = 29; y >= 0; y--)
    {
        for(int x = 0; x < ram_side_size; x++)
        {
            if(proc->ram[x + y * ram_side_size] == 0)
            {
                putchar('.');
                putchar(' ');
            }
            else
            {
                putchar(proc->ram[x + y * (ram_side_size)]);
                putchar(' ');
            }
        }
        putchar('\n');
    }
    putchar('\n');

    return SUCCESS;
}
