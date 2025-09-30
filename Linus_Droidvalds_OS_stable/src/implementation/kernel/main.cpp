#include "kernel_io.h"
#include "barestring.h"

extern "C" void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Booted Successfully, ");
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("ver: 0.4.2\n");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);

    char* stringgg = "Do you see the fun in gcc?";

    char* slice = substr(stringgg, 22, 25);

    print_str(slice);


    while(true){
        char* e = get_input(256);
        print_newline();
        print_str(e);
    }
}

