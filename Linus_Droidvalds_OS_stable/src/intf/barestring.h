#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stddef.h>


char* inttostr(int value);
int strfind(char* str, char firstappearance);
void strreplace(char* str, int index, char repl);
size_t strsize(char* str);
int strcmp(char* strA, char* strB);
char* substr(char* str, int startindex, int endindex);

#ifdef __cplusplus
}
#endif