#include <stdio.h>
#include <stdint.h>

extern void _putchar(char character);

void print_hexstring(uint32_t num)
{
    for (uint32_t i = sizeof(num) * 8; i > 0; i -= 4)
    {
        uint8_t nibble = (num >> (i - 4)) & 0xF;
        if (nibble > 9)
        {
            _putchar(nibble + 0x37);
        }
        else
        {
            _putchar(nibble + 0x30);
        }
    }
}

void hexstring(uint32_t num)
{
    print_hexstring(num);
    _putchar('\r');
    _putchar('\n');
}

void hexstrings(uint32_t num)
{
    print_hexstring(num);
    _putchar(' ');
}

void uart_send(uint32_t c) {
    _putchar(c);
}

