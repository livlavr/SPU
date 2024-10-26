#ifndef TEXT_PROCESSING_H_
#define TEXT_PROCESSING_H_

TYPE_OF_ERROR size_of_text  (const char* filename, size_t* size_of_buffer);
TYPE_OF_ERROR count_cmds    (char* buffer, size_t size_of_text, size_t* number_of_cmds);
TYPE_OF_ERROR fill_commands (char* buffer, size_t size_of_text, char** asm_commands);
TYPE_OF_ERROR process_filenames(int argc, char** argv, char** input_filename, char** output_filename, const char* source_filename);
TYPE_OF_ERROR process_flag  (size_t number_of_flag, char** argv, char** input_filename, char** output_filename);
TYPE_OF_ERROR set_default_filename(char** filename, const char* source_filename);

#define catch_filenames(argc, argv, input_filename, output_filename)\
    process_filenames(argc, argv, input_filename, output_filename, __FILE__)

#define catch_processor_flags(argc, argv, input_filename)\
    process_filenames(argc, argv, input_filename, input_filename, __FILE__)

#endif
