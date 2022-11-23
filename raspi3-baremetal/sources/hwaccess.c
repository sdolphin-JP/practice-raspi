#include "hwaccess.h"

void hw_uart_puts(char* pBuf)
{
    if (NULL == pBuf)
    {
        pBuf = "(null)";
    }

    while (0 != *pBuf)
    {
        hw_uart_putc(*pBuf);
        pBuf++;
    }
}

void hw_uart_write(uint8_t* pBuf, int32_t len)
{
    while (0 < len)
    {
        hw_uart_putc(*pBuf);
        pBuf++;
        len--;
    }
}

int32_t hw_uart_read(uint8_t* pBuf, int32_t len)
{
    int32_t count = 0;

    while (0 < len)
    {
        *pBuf = hw_uart_getc();
        pBuf++;
        len--;
        count++;
        break;
    }

    return count;
}

void hw_reset()
{
    hw_uart_puts("resetting ... \r\n");
    hw_mmio_w32(0x3f10001C, 0x5a000000 | ((hw_mmio_r32(0x3f10001C) & ~0x00000030) | 0x00000020));
    hw_mmio_w32(0x3f100024, 0x5a000000 | 0x20);
    while (1);
}
