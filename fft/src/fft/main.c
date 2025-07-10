#include "printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#define printf_float(_num) _num

#include "fourier.h"

const uint32_t MAXSIZE = 256;       // small 4096, 8192 inverse, 512 for memory-limited systems
const uint32_t MAXWAVES = 4;        // large has 8
const uint32_t MAX_NUMS_PER_LINE = 8;

static float realin[256];
static float imagin[256];
static float realout[256];
static float imagout[256];
static float Coeff[4];
static float Amp[4];

static uint32_t _myrand_seed = 1234;

void my_srand(uint32_t new_seed)
{
    _myrand_seed = new_seed;
}

uint32_t my_rand(void)
{
    _myrand_seed = (uint32_t)(1103515245 * _myrand_seed + 12345);
    return _myrand_seed;
}


void printf_float_array(const char* name, float *array, uint32_t size)
{
    printf("%s:\r\n", name);
    for (uint32_t i = 0, p = 0; i < size; i++)
    {
        printf("%+011.4f     ", printf_float(array[i]));
        if (p == MAX_NUMS_PER_LINE - 1)
        {
            printf("\r\n");
            p = 0;
        }
        else
        {
            p++;
        }
    }
    printf("\r\n");
}

int main(void)
{
    uint32_t i, j;
    float    *RealIn;
    float    *ImagIn;
    float    *RealOut;
    float    *ImagOut;
    float    *coeff;
    float    *amp;

    my_srand(1);

    // Statically allocate
    RealIn  = realin;
    ImagIn  = imagin;
    RealOut = realout;
    ImagOut = imagout;
    coeff   = Coeff;
    amp     = Amp;

    /* Makes MAXWAVES waves of random amplitude and period */
    for (i = 0; i < MAXWAVES; i++)
    {
        coeff[i] = my_rand() % 1000;
        amp[i]   = my_rand() % 1000;
    }
    for (i = 0; i < MAXSIZE; i++)
    {
        RealIn[i] = 0;
        for (j = 0; j < MAXWAVES; j++)
        {
            /* randomly select sin or cos */
            if (my_rand() % 2)
            {
                RealIn[i] += coeff[j] * cos(amp[j] * i);
            }
            else
            {
                RealIn[i] += coeff[j] * sin(amp[j] * i);
            }
            ImagIn[i] = 0;
        }
    }

    printf_float_array("RealIn", RealIn, MAXSIZE);
    printf_float_array("ImagIn", ImagIn, MAXSIZE);

    printf("Regular FFT\r\n");
    printf("-----------\r\n");
    fft_float(MAXSIZE, FALSE, RealIn, ImagIn, RealOut, ImagOut);
    printf_float_array("RealOut", RealOut, MAXSIZE);
    printf_float_array("ImagOut", ImagOut, MAXSIZE);

    printf("Inverse FFT\r\n");
    printf("-----------\r\n");
    fft_float(MAXSIZE, TRUE, RealIn, ImagIn, RealOut, ImagOut);
    printf_float_array("RealOut", RealOut, MAXSIZE);
    printf_float_array("ImagOut", ImagOut, MAXSIZE);

    return 0;
}
