#ifndef ERROR_TYPES_H_
#define ERROR_TYPES_H_

enum TYPE_OF_ERROR {
    POINTER_IS_NULL = 1,
    DOUBLE_IS_NAN   = 2,
    FILE_OPEN_ERROR = 3,
    FILE_READ_ERROR = 4,
    STAT_ERROR      = 5,
    CALLOC_ERROR    = 6,
    SUCCESS         = 7,
};

#endif