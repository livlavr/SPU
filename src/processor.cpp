#include <stdio.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "color_printf.h"
#include "size_of_text.h"

int main()
{
    stack* st = NULL;
    stack_init(st, 10);

    stack_elem registers[NUMBER_OF_REGISTERS] = {};

    const char* filename = "src/spu_commands.bin";
    FILE* bin_file = fopen(filename, "rb");

    if (bin_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", filename);

        return FILE_OPEN_ERROR; //TODO I don't return enum type
    }

    size_t size = 0;
    size_of_text(filename, &size);

    int commands[size] = {};

    fread(commands, sizeof(stack_elem), size, bin_file);

    fclose(bin_file);

    bool hlt_not_found      = true;
    size_t ip               = 0;
    stack_elem value_of_cmd = 0;
    stack_elem x = 0, y = 0;

    while(hlt_not_found)
    {
        switch(commands[ip])
        {
            case DISASSEMBLY_PUSH:
                ip++;
                value_of_cmd = commands[ip++];

                push(st, value_of_cmd);

                // printf("PUSH\n");

                break;

            case DISASSEMBLY_PUSHR:
                ip++;
                value_of_cmd = registers[commands[ip++]];

                push(st, value_of_cmd);

                // printf("PUSHR\n");

                break;

            case DISASSEMBLY_POPR: //DISASSEMBLY POP DOESN'T NEED? think i can make it just print a value
                ip++;
                pop(st, &x);
                registers[commands[ip++]] = x;

                // printf("POPR\n");

                break;

            case DISASSEMBLY_ADD:
                pop(st, &y); //TODO correct highlighting in pop
                pop(st, &x);
                push(st, x + y);

                ip++;

                // printf("ADD\n");

                break;

            case DISASSEMBLY_SUB:
                pop(st, &y); //TODO correct highlighting
                pop(st, &x);
                push(st, x - y);

                ip++;

                // printf("SUB\n");

                break;

            case DISASSEMBLY_DIV:
                pop(st, &y); //TODO correct highlighting
                pop(st, &x);
                push(st, x / y);
                ip++;

                // printf("DIV\n");

                break;

            case DISASSEMBLY_MUL:
                pop(st, &y);
                pop(st, &x);
                push(st, x * y);
                ip++;

                // printf("MUL\n");

                break;

            case DISASSEMBLY_OUT: //TODO make print cmd
                pop(st, &x);
                color_printf(GREEN_TEXT, BOLD, "RESULT: %d\n", x);

                ip++;

                break;

            case DISASSEMBLY_JA:
                pop(st, &y);
                pop(st, &x);

                if(x > y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_JAE:
                pop(st, &y);
                pop(st, &x);

                if(x >= y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_JB:
                pop(st, &y);
                pop(st, &x);

                if(x < y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_JBE:
                pop(st, &y);
                pop(st, &x);

                if(x <= y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_JE:
                pop(st, &y);
                pop(st, &x);

                if(x == y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_JNE:
                pop(st, &y);
                pop(st, &x);

                if(x != y)
                {
                    ip++;
                    ip = commands[ip];
                }
                else
                {
                    ip++;
                    ip++;
                }

                break;

            case DISASSEMBLY_HLT:
                stack_destroy(st);

                exit(0);

            default:
                color_printf(RED_TEXT, BOLD, "Command %d doesn't found\n", commands[ip]);

                warning(false, VALUE_ERROR);
        }
    }
}
