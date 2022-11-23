#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syscalls.h"
#include "hwaccess.h"

void main(void)
{
    printf("Raspi3b Baremtal Practice \r\n");
    printf("Build: %s %s \r\n", __DATE__, __TIME__);
    printf("\r\n");

    while (1);
}
