ENTRY(__boot)
SECTIONS
{
    . = 0x80000;
    __start = .;

    /*
     * The program is deployed to "text section".
     */
    __text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        . = ALIGN(2048);
        KEEP(*(.vectors))
        . = ALIGN(2048);
        *(.text)
        *(.text.*)
    }
    . = ALIGN(4096);
    __text_end = .;

    /*
     * The initialized variable is deployed to "data section".
     */
    __data_start = .;
    .data :
    {
        *(.data)
        *(.data*)
    }
    . = ALIGN(4096);
    __data_end = .;

    /*
     * The uninitialized variable is deployed to "bss section".
     * Need initialize to zero when startup.
     */
    __bss_start = .;
    .bss :
    {
        *(.bss)
        *(.bss*)
        *(COMMON)
    }
    . = ALIGN(4096);
    __bss_end = .;

    /*
     * The heap is deployed to "heap section".
     */
    __heap_start = .;
    .heap :
    {
        /* 512 MB */
        . += 0x20000000;
    }
    . = ALIGN(4096);
    __heap_end = .;

    /*
     * The stack is deployed to "stack section".
     */
    __stack_start = .;
    .stack :
    {
        /* 64 MB */
        . += 0x04000000;
    }
    . = ALIGN(4096);
    __stack_end = .;

    __end = .;
}
__text_size  = (__text_end  - __text_start);
__data_size  = (__data_end  - __data_start);
__bss_size   = (__bss_end   - __bss_start);
__heap_size  = (__heap_end  - __heap_start);
__stack_size = (__stack_end - __stack_start);
