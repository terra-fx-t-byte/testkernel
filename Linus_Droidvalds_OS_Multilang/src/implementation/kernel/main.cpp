#include "kernel_io.h"
#include "barestring.h"
#include "panic.h"
#include "apm.h"
#include "sbrk.h"

extern "C" void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Booted Successfully, ");
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("ver: 0.6 ");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str(" - Initial sysbreak start: ");
    print_str(inttostr((int)get_current_break()));
    print_str("\n * Initial Heap start: ");
    print_str(inttostr((int)get_heap_start()));
    print_str("\n * Initial Heap end: ");
    print_str(inttostr((int)get_heap_end()));
    int* nums = (int*)sbrk(149 * sizeof(int));
    if (nums == (void*)-1) {
        kernel_panic_char_pointer("sbrk err");
    }
    for (int i = 0; i<149; i++) {
        nums[i] = i * 1;
        print_char(' ');
        print_str(inttostr(nums[i]));
    }
    print_str("\n Initial sysbreak end: ");
    print_str(inttostr((int)get_current_break()));
}

