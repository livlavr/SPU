#ifndef DEBUG_MACROS_H_
#define DEBUG_MACROS_H_

#ifndef NDEBUG
    #include <inttypes.h>

    #define GREEN   "\033[1;32m"
    #define YELLOW  "\033[1;33m"
    #define DEFAULT "\033[0m"
    #define BLUE    "\033[36m"

    #define $DEBUG(type_of_output, variable)                                   \
    {                                                                          \
        printf("< " type_of_output " > - %s | "                                \
               BLUE   "file - %s | "                                           \
               YELLOW "line - %d | "                                           \
               GREEN  "function - %s\n"                                        \
               DEFAULT, variable, #variable, __FILE__, __LINE__, __FUNCTION__);\
    }

#else

    #define $DEBUG(variable, type_of_output) ;

#endif
#endif
