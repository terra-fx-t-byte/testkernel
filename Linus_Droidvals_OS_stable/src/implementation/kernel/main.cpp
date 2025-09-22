#include "kernel_io.h"

extern "C" void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Booted Successfully");
    print_newline();
    print_str("Executing main kernel function...");
    print_newline();
    char* messagee = get_input(256);
    print_newline();
    print_str(messagee);
    //print_str("OS: Linus Droidvals OS x86_64\n");
    //print_str("Host: User\n");
    //print_str("Display: memory(0xb8000)\n");
    //print_str("Shell: none");
    
}

