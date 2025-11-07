#include "kernel_io.h"
#include "panic.h"

void kernel_panic_char_pointer(char* reason){
    reset_cursor();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLUE);
    print_clear();
    print_clear();
    print_newline();
    print_str("A critical error caused a kernel panic: ");
    print_str(reason);
    print_str("\n\n To continue working with kernel - reboot");
    asm volatile("hlt");
}