#include "sbrk.h"

// External symbols defined in linker script
extern char _end;          // End of BSS/data section
extern char _stack_bottom; // Bottom of stack (stack grows down)

static void* current_break = NULL;

void* sbrk(intptr_t increment) {
    if (current_break == NULL) {
        current_break = (void*)&_end;
    }
    
    void* previous_break = current_break;
    void* new_break = (char*)current_break + increment;
    
    if (new_break >= (void*)&_stack_bottom) {
        return (void*)-1;
    }
    
    current_break = new_break;
    return previous_break;
}

// Helper functions
void* get_heap_start(void) {
    return (void*)&_end;
}

void* get_heap_end(void) {
    return (void*)&_stack_bottom;
}

void* get_current_break(void) {
    if (current_break == NULL) {
        return (void*)&_end;
    }
    return current_break;
}

void memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
}

void memcpy(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
}