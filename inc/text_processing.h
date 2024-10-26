#ifndef TEXT_PROCESSING_H_
#define TEXT_PROCESSING_H_

TYPE_OF_ERROR size_of_text  (const char* filename, size_t* size_of_buffer);
TYPE_OF_ERROR count_cmds    (char* buffer, size_t size_of_text, size_t* number_of_cmds);
TYPE_OF_ERROR fill_commands (char* buffer, size_t size_of_text, char** asm_commands);
TYPE_OF_ERROR catch_filename(int argc, char** argv, char** input_filename, char** output_filename, const char* source_filename);

#define catch_filenames(argc, argv, input_filename, output_filename)\
    catch_filename(argc, argv, input_filename, output_filename, __FILE__)

#define process_flag(number_of_flag)                                                      \
    do                                                                                    \
        {                                                                                 \
            if(strcmp(argv[number_of_flag], input_flag) == 0)                             \
            {                                                                             \
                size_t size_of_filename = sizeof(argv[number_of_flag + 1]) / sizeof(char);\
                *input_filename = (char*)calloc(size_of_filename, sizeof(char));          \
                                                                                          \
                warning(*input_filename, CALLOC_ERROR);                                   \
                                                                                          \
                strcpy(*input_filename, argv[number_of_flag + 1]);                        \
            }                                                                             \
            else if(strcmp(argv[number_of_flag], output_flag) == 0)                       \
            {                                                                             \
                size_t size_of_filename = sizeof(argv[number_of_flag + 1]) / sizeof(char);\
                *output_filename = (char*)calloc(size_of_filename, sizeof(char));         \
                                                                                          \
                warning(*output_filename, CALLOC_ERROR);                                  \
                                                                                          \
                strcpy(*output_filename, argv[number_of_flag + 1]);                       \
            }                                                                             \
            else                                                                          \
            {                                                                             \
                wrong_input_flag = 1;                                                     \
            }                                                                             \
        }                                                                                 \
    while(0)

#define set_default(source_filename)\
    do                                                  \
    {                                                   \
        if(strcmp(source_filename, "src/assembly.cpp"))\
        {\
        set_default_filename(input_filename, asm_source);\
        set_default_filename(output_filename, bin_source);\
        }\
        else\
        {\
        set_default_filename(input_filename, asm_source);\
        set_default_filename(output_filename, bin_source);\
        }\
                                                        \
    }\
    while(0)\

#define set_default_filename(filename, source_filename)\
    do\
    {\
        size_t size_of_filename = sizeof(source_filename) / sizeof(char);\
        *filename = (char*)calloc(size_of_filename, sizeof(char));\
                                                                        \
        warning(*filename, CALLOC_ERROR);\
                                                                        \
        strcpy(*filename, source_filename);\
        $DEBUG("%s", *filename);\
    }\
    while(0)

const char* input_flag  = "--input";
const char* output_flag = "--output";
const char* asm_source  = "src/assembly.asm";
const char* bin_source  = "src/spu_commands.bin";

#endif
