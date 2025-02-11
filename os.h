#ifndef OS_INDENTIFY
#define OS_INDENTIFY

#ifndef OS_NAME
    #ifdef _WIN32
    #define OS_NAME "Windows 32-bit"
    #elif _WIN64
    #define OS_NAME "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    #define OS_NAME "Mac OSX";
    #elif __linux__
    #define OS_NAME "Linux";
    #elif __FreeBSD__
    #define OS_NAME "FreeBSD";
    #elif __unix || __unix__
    #define OS_NAME "Unix";
    #else
    #define OS_NAME "Other";
    #endif
#endif

#endif