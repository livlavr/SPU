#include <stdio.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "color_printf.h"
#include "text_processing.h"
#include "processor.h"
#include "debug_macros.h"

int main(int argc, char** argv)
{
    processor proc = {};
    stack_init(proc.st, 15);
    stack_init(proc.functions_return_codes, 5);
//TODO make file read and processor init in different functions
    char* input_filename = NULL;

    catch_processor_flags(argc, argv, &input_filename);

    FILE* bin_file = fopen(input_filename, "rb");

    if(bin_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", input_filename);

        return (int)FILE_OPEN_ERROR;
    }

    size_t size_of_file = 0;
    size_of_text(input_filename, &size_of_file);

    proc.ram       = (stack_elem*)calloc(SIZE_OF_RAM, sizeof(stack_elem));
    proc.registers = (stack_elem*)calloc(MAX_NUMBER_OF_REGISTERS, sizeof(stack_elem));
    proc.commands  = (char*)calloc(size_of_file, sizeof(char));

    fread(proc.commands, sizeof(char), size_of_file, bin_file);

    fclose(bin_file);

    bool       hlt_not_found = true;
    stack_elem value_of_cmd  = 0;
    size_t     ip            = 0;
    stack_elem x = 0, y = 0;

//TODO make hlt not found error in assembly
    while(hlt_not_found)
    {
        $DEBUG("%d - cmd", proc.commands[ip] & BYTE_COMMAND_MASK);
        $DEBUG("%d - push", DISASSEMBLY_PUSH);
        $DEBUG("%d - pop", DISASSEMBLY_POP);
        $DEBUG("%d - add", DISASSEMBLY_ADD);
        $DEBUG("%d - sub", DISASSEMBLY_SUB);
        $DEBUG("%d - div", DISASSEMBLY_DIV);
        $DEBUG("%d - mul", DISASSEMBLY_MUL);
        $DEBUG("%d - in",  DISASSEMBLY_IN);
        $DEBUG("%d - out", DISASSEMBLY_OUT);
        $DEBUG("%d - call", DISASSEMBLY_CALL);
        $DEBUG("%d - return", DISASSEMBLY_RETURN);
        $DEBUG("%d - hlt", DISASSEMBLY_HLT);

        switch(proc.commands[ip++] & BYTE_COMMAND_MASK)
        {
            case DISASSEMBLY_PUSH:
                value_of_cmd = *get_arg(&proc, &ip);
                push(proc.st, value_of_cmd);

                break;

            case DISASSEMBLY_POP:
                pop(proc.st, &x);
                *get_arg(&proc, &ip) = x;

                break;

            case DISASSEMBLY_ADD:
                pop(proc.st, &y); //TODO correct highlighting in pop
                pop(proc.st, &x);
                push(proc.st, x + y);

                // printf("ADD\n");

                break;

            case DISASSEMBLY_SUB:
                pop(proc.st, &y); //TODO correct highlighting
                pop(proc.st, &x);
                push(proc.st, x - y);

                // printf("SUB\n");

                break;

            case DISASSEMBLY_DIV:
                pop(proc.st, &y); //TODO correct highlighting
                pop(proc.st, &x);
                push(proc.st, x / y);

                // printf("DIV\n");

                break;

            case DISASSEMBLY_MUL:
                pop(proc.st, &y);
                pop(proc.st, &x);
                push(proc.st, x * y);

                // printf("MUL\n");

                break;

            case DISASSEMBLY_IN:
                scanf("%d", &x);
                push(proc.st, x);

                break;

            case DISASSEMBLY_OUT: //TODO make print cmd
                pop(proc.st, &x);
                color_printf(GREEN_TEXT, BOLD, "RESULT: %d\n", x);

                break;

            case DISASSEMBLY_JA:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x > y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JAE:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x >= y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JB:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x < y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JBE:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x <= y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JE:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x == y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JNE:
                pop(proc.st, &y);
                pop(proc.st, &x);

                if(x != y)
                {
                    ip = proc.commands[ip];
                }
                else
                {
                    ip += sizeof(int);
                }

                break;

            case DISASSEMBLY_JMP:
                ip = proc.commands[ip];

                break;

            case DISASSEMBLY_CALL:
                push(proc.functions_return_codes, ++ip);
                printf("%d\n", ip);
                scanf(&(proc.commands[ip]), &x);
                printf("%d\n", x);
                ip = x;
                ip += sizeof(int);

                break;

            case DISASSEMBLY_RETURN:
                pop(proc.functions_return_codes, &x);
                ip = x;

                break;

            case DISASSEMBLY_HLT:
                stack_destroy(proc.st);
                stack_destroy(proc.functions_return_codes);

                free(proc.commands);
                free(proc.ram);
                free(proc.registers);

                exit(0);

            default:
                color_printf(RED_TEXT, BOLD, "Command %d doesn't found\n", proc.commands[--ip]);

                warning(false, VALUE_ERROR);
        }
    }
}

stack_elem* get_arg(processor* proc, size_t* ip)
{
    int format                   = (int)(proc->commands[*ip] & BYTE_FORMAT_MASK);
    int is_reg                   = format & IS_REGISTER;
    int is_constant              = format & IS_I_CONSTANT;
    int memory                   = format & IS_MEMORY;
    stack_elem* argument_address = 0;
    stack_elem  ip_of_argument   = 0;
    stack_elem* argument_source  = NULL;

    (*ip)++;

    if(memory)
    {
        argument_source = proc->ram;
    }
    else
    {
        argument_source = proc->registers;
    }

    if(is_reg)
    {
        ip_of_argument += proc->registers[proc->commands[*ip]];
        *ip += sizeof(int);
    }
    if(is_constant)
    {
        ip_of_argument += proc->commands[*ip];
        *ip += sizeof(int);
    }
    argument_source = &(argument_source[ip_of_argument]);

    return argument_source;
}
