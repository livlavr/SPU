#include <stdio.h>
#include <cstdlib>

#include "custom_asserts.h"
#include "commands.h"
#include "stack_public.h"
#include "color_printf.h"

int main()
{
    stack* st = NULL;
    stack_init(st, 10);
    int commands[50] = {};

    FILE* bin_file = fopen("src/spu_commands.bin", "rb");

    if (bin_file == NULL)
    {
        color_printf(RED_TEXT, BOLD, "File with %s name doesn't exist\n", bin_file);

        return FILE_OPEN_ERROR; //TODO I don't return enum type
    }

    fread(commands, sizeof(stack_elem), 50, bin_file);

    fclose(bin_file);

    bool hlt_not_found = true;
    size_t ip = 0;
    stack_elem value_of_cmd     = 0;
    stack_elem x = 0, y = 0;

    while(ip < 50 && hlt_not_found)
    {
        switch(commands[ip])
        {
            case DISASSEMBLY_PUSH:
                ip++;
                value_of_cmd = commands[ip++];

                push(st, value_of_cmd);

                printf("PUSH\n");

                break;

            case DISASSEMBLY_POP:

                ip++;

                break;

            case DISASSEMBLY_ADD:
                pop(st, &y); //TODO correct highlighting in pop
                pop(st, &x);
                push(st, x + y);

                ip++;

                printf("ADD\n");

                break;

            case DISASSEMBLY_SUB:
                pop(st, &y); //TODO correct highlighting
                pop(st, &x);
                push(st, x - y);

                ip++;

                printf("SUB\n");

                break;

            case DISASSEMBLY_DIV:
                pop(st, &y); //TODO correct highlighting
                pop(st, &x);
                push(st, x / y);
                ip++;

                printf("DIV\n");

                break;

            case DISASSEMBLY_OUT:
                pop(st, &x);
                color_printf(GREEN_TEXT, BOLD, "RESULT: %d\n", x);

                ip++;

                break;

            case DISASSEMBLY_HLT:
                stack_destroy(st);

                exit(0);

                break;

            default:
                color_printf(RED_TEXT, BOLD, "Command - %d\n", commands[ip]);
                warning(false, "Command doesn't found\n");
        }
    }
}
