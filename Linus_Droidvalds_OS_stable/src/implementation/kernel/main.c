#include "print.h"

void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("what about gcc?");
    print_newline();
    print_str("do i see the fun in gcc?");
}

