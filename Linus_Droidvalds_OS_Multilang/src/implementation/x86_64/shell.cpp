#include "shell.h"


const char* SHELL_ENTRYPOINT = "shell";


typedef struct{
    static char rootname[256];
    unsigned int argsstart;
    unsigned int argend;
} ShellCommand;


char* parseinput(char* str){

}