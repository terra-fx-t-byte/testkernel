#include "kernel_io.h"

void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("what about gcc?");
    print_newline();
    print_str("do i see the fun in gcc?");
    print_newline();
    for (int i = 0; i < 155; i++) {
        char c = getchar();
        print_char(c);
    }
    
}

