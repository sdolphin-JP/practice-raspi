.section ".text"

.globl __enable_irq
__enable_irq:
    msr daifclr, #2
    ret

.globl __disable_irq
__disable_irq:
    msr daifset, #2
    ret

.global __get_vbar_el2
__get_vbar_el2:
    mrs x20, vbar_el2
    str w0, [x20]
    ret

.global __get_hcr_el2
__get_hcr_el2:
    mrs x20, hcr_el2
    str w0, [x20]
    ret

.global __get_elr_el2
__get_elr_el2:
    mrs x20, elr_el2
    str w0, [x20]
    ret

.global __get_current_el
__get_current_el:
    mrs x20, CurrentEL
    str w0, [x20]
    ret

.global __get_current_sp
__get_current_sp:
    str w0, [sp]
    ret
