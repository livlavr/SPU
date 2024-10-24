#ifndef SIZE_OF_TEXT_H_
#define SIZE_OF_TEXT_H_

TYPE_OF_ERROR size_of_text(const char* filename, size_t* size_of_buffer);
TYPE_OF_ERROR count_cmds(char* buffer, size_t size_of_text, size_t* number_of_cmds);
TYPE_OF_ERROR fill_commands(char* buffer, size_t size_of_text, char** asm_commands);

#endif
