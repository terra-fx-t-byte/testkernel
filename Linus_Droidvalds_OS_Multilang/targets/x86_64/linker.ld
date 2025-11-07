ENTRY(start)

SECTIONS
{
    . = 1M;

    .boot :
    {
        KEEP(*(.multiboot_header))
    }

    .text :
    {
        *(.text)
    }

    .bss : { 
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        _end = .;  /* Heap starts here */
    }

    . = . + 0x100000;
    
    /* Reserve space for stack */
    . = . + 0x4000; /* 16KB stack */
    _stack_bottom = .; /* Stack grows downward from here */
    
    /DISCARD/ : { *(.comment*) }
}