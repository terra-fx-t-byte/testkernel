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

#ifdef __cplusplus
}
#endif