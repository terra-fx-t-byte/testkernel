#include "apm.h"

void apm_shutdown() {
    __asm__ volatile (
        // Connect to APM API
        "mov $0x5301, %%ax\n"
        "xor %%bx, %%bx\n"      // BX = 0
        "int $0x15\n"
        
        // Try to set APM version to 1.2
        "mov $0x530E, %%ax\n"
        "xor %%bx, %%bx\n"      // BX = 0  
        "mov $0x0102, %%cx\n"   // CX = 0x0102 (version 1.2)
        "int $0x15\n"
        
        // Turn off the system
        "mov $0x5307, %%ax\n"
        "mov $0x0001, %%bx\n"   // BX = 1 (all devices)
        "mov $0x0003, %%cx\n"   // CX = 3 (power off)
        "int $0x15\n"
        
        // Return (in case of failure)
        "ret\n"
        :
        : 
        : "ax", "bx", "cx", "memory"
    );

    __asm__ volatile ("hlt");

}