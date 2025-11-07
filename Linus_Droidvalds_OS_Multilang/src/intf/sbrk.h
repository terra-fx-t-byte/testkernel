#ifndef _SBRK_H
#define _SBRK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

void memset(void* ptr, int value, size_t num);
void* sbrk(intptr_t increment);
void memcpy(void* dest, const void* src, size_t num);

void* get_heap_start(void);
void* get_heap_end(void);
void* get_current_break(void);

#ifdef __cplusplus
}
#endif

#endif