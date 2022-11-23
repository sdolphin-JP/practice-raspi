.section ".vectors"

.globl __vector_table
__vector_table:

    .set VBAR, __vector_table

    /* Synchronous / Current EL with SP0 */
    .org VBAR
        eret

    /* IRQ/vIRQ / Current EL with SP0 */
    .org (VBAR + 0x80)
        eret

    /* FIQ/vFRQ / Current EL with SP0 */
    .org (VBAR + 0x100)
        eret

    /* SError/vSError / Current EL with SP0 */
    .org (VBAR + 0x180)
        eret


    /* Synchronous / Current EL with SPx */
    .org (VBAR + 0x200)
        eret

    /* IRQ/vIRQ / Current EL with SPx */
    .org (VBAR + 0x280)
        eret

    /* FIQ/vFRQ / Current EL with SPx */
    .org (VBAR + 0x300)
        eret

    /* SError/vSError / Current EL with SPx */
    .org (VBAR + 0x380)
        eret


    /* Synchronous / Lower EL using AArch64 */
    .org (VBAR + 0x400)
        eret

    /* IRQ/vIRQ / Lower EL using AArch64 */
    .org (VBAR + 0x480)
        eret

    /* FIQ/vFRQ / Lower EL using AArch64 */
    .org (VBAR + 0x500)
        eret

    /* SError/vSError / Lower EL using AArch64 */
    .org (VBAR + 0x580)
        eret


    /* Synchronous / Lower EL using AArch32 */
    .org (VBAR + 0x600)
        eret

    /* IRQ/vIRQ / Lower EL using AArch32 */
    .org (VBAR + 0x680)
        eret

    /* FIQ/vFRQ / Lower EL using AArch32 */
    .org (VBAR + 0x700)
        eret

    /* SError/vSError / Lower EL using AArch32 */
    .org (VBAR + 0x780)
        eret
