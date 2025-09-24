#include "kernel_io.h"
#include "barestring.h"

extern "C" void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Booted Successfully, ");
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("ver: 0.4.2\n");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    int index = strfind("foo bar", 'r');
    char* out = inttostr(index);
    print_str(out);
    print_str("\n^^^ index of appearance of r in 'foo bar'");
    char* messagee = get_input(256);
    print_newline();
    print_str(messagee);
}

