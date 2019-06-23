#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
    #define Log(format, ...) do{      \
    printf(format, __VA_ARGS__);    \
                                            \
    } while(0)
#else
    #define Log(...) ;
#endif // ! DEBUG