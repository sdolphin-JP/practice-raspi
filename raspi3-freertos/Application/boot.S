.section ".text.boot"

.globl __boot
__boot:

    // set sp
    ldr x20, =__stack_end
    mov sp, x20

    //
    // x0-31 and w0-w30 share the area.
    //  x0 - x30: 64bit general register
    //  w0 - w30: 32bit general register
    //
    // xzr: Always zero register.
    // wzr: Always zero register.
    //

    // clear bss.
    ldr  x20, =__bss_start
    ldr  w21, =__bss_size
1:  cbz  w21, 2f
    str  xzr, [x1], #8
    sub  w21, w21, #8
    cbnz w21, 1b
2:  nop

    // start main routine.
    bl main
    b  __hang


__hang:
    wfi
    b __hang
