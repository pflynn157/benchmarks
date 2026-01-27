#include <stddef.h>
#include <stdint.h>

#if defined(__clang__)
#define NO_OPT __attribute__((optnone))
#else
#define NO_OPT __attribute__((optimize("O0")))
#endif

NO_OPT
int putc(int character, void *stream)
{
    //(void)stream;
    //return character;
    //#ifdef ARM
    uint8_t *addr = (uint8_t*)0xE0000000;
    //#elif BMSP430
    //uint8_t *addr = (uint8_t*)0xFFF2;
    //#else
    //uint8_t *addr = (uint8_t*)0x40000000;
    //#endif
    *addr = (char)character;
    return 0;
}

NO_OPT
void _putchar(char character) {
    putc(character, &character);
}

//#pragma GCC push_options
