#ifndef __HWACCESS_H__
#define __HWACCESS_H__


#include <stdint.h>
#include <string.h>


#define BCM2837B0_AUX_REG                   (0x3f215000)
#define BCM2837B0_AUX_MU_IO_REG             (BCM2837B0_AUX_REG + 0x0040)
#define BCM2837B0_AUX_MU_LSR_REG            (BCM2837B0_AUX_REG + 0x0054)
#define BCM2837B0_AUX_MU_LSR_BIT_RX_RDY     (0x1 << 0)
#define BCM2837B0_AUX_MU_LSR_BIT_TX_EMPTY   (0x1 << 5)
#define BCM2837B0_AUX_MU_LSR_BIT_TX_IDLE    (0x1 << 6)


static inline uint8_t hw_mmio_r8(const uintptr_t addr)
{
    return *((volatile uint8_t*)addr);
}

static inline uint16_t hw_mmio_r16(const uintptr_t addr)
{
    return *((volatile uint16_t*)addr);
}

static inline uint32_t hw_mmio_r32(const uintptr_t addr)
{
    return *((volatile uint32_t*)addr);
}

static inline void hw_mmio_w8(const uintptr_t addr, uint8_t data)
{
    *((volatile uint8_t*)addr) = data;
}

static inline void hw_mmio_w16(const uintptr_t addr, uint16_t data)
{
    *((volatile uint16_t*)addr) = data;
}

static inline void hw_mmio_w32(const uintptr_t addr, uint32_t data)
{
    *((volatile uint32_t*)addr) = data;
}

static inline void hw_uart_putc(const uint8_t ch)
{
    while ((0 == (hw_mmio_r32(BCM2837B0_AUX_MU_LSR_REG) & BCM2837B0_AUX_MU_LSR_BIT_TX_IDLE))
        && (0 == (hw_mmio_r32(BCM2837B0_AUX_MU_LSR_REG) & BCM2837B0_AUX_MU_LSR_BIT_TX_EMPTY)));
    hw_mmio_w32(BCM2837B0_AUX_MU_IO_REG, ch);
}

static inline uint8_t hw_uart_getc(void)
{
    while (0 == (hw_mmio_r32(BCM2837B0_AUX_MU_LSR_REG) & BCM2837B0_AUX_MU_LSR_BIT_RX_RDY));
    return (uint8_t)hw_mmio_r32(BCM2837B0_AUX_MU_IO_REG);
}


void    hw_uart_puts(char* pBuf);
void    hw_uart_write(uint8_t* pBuf, int32_t len);
int32_t hw_uart_read(uint8_t* pBuf, int32_t len);
void    hw_reset();


#endif /* #ifndef __HWACCESS_H__ */
