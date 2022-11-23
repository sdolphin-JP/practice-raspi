.section ".text.boot"

.globl __boot
__boot:

    // Only use core 0
    mrs x20, mpidr_el1
    and x20, x20, #0x3
    cmp x20, #0x0
    bne __hang

    // CurrenEL = 3
    mrs x20, CurrentEL
    and x20, x20, #0xc
    cmp x20, #0xc
    beq __boot_el3

    // CurrenEL = 2
    mrs x20, CurrentEL
    and x20, x20, #0x8
    cmp x20, #0x8
    beq __boot_el2

    // CurrenEL = 1 or 0
    b __boot_el1


__boot_el3:

    // Set sp
    ldr x20, =__stack_end
    mov sp, x20

    // Set sp in el2
    ldr x20, =__stack_end
    msr sp_el1, x20

    // Set vector address in EL3.
    ldr x20, =__vector_table
    msr vbar_el3, x20

    // Enable AArch64 in EL2.
    // EL2 and EL1 cannnot access secure memory.
    // Dsiable secure monitor call.
    mov x20, #0x481
    msr scr_el3, x20

    // Change execution level to EL2h.
    adr x20, __boot_el2
    msr elr_el3, x20
    mov x20, #0x9
    msr spsr_el3, x20
    eret


__boot_el2:

    // Set sp
    ldr x20, =__stack_end
    mov sp, x20

    // Set sp in el1
    ldr x20, =__stack_end
    msr sp_el1, x20

    // Set vector address in EL2.
    ldr x20, =__vector_table
    msr vbar_el2, x20

    // Enable AArch64 in EL1.
    // DC CISW is a 64-bit System instruction.
    mov x20, #(1 << 31)
    orr x20, x20, #(1 << 1)
    msr hcr_el2, x20

    // Change execution level to EL1h.
    adr x20, __boot_el1
    msr elr_el2, x20
    mov x20, #0x5
    msr spsr_el2, x20
    eret


__boot_el1:

    // Set sp
    ldr x20, =__stack_end
    mov sp, x20

    // Set vector address in EL1.
    ldr x20, =__vector_table
    msr vbar_el1, x20

    // Clear bss.
    ldr  x20, =__bss_start
    ldr  w21, =__bss_size
1:  cbz  w21, 2f
    str  xzr, [x20], #8
    sub  w21, w21, #8
    cbnz w21, 1b
2:  nop

    // Start main routine.
    bl main
    b  __hang


__hang:
    wfi
    b __hang
