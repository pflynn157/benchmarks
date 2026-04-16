#include "printf.h"
#include <stdio.h>

#include "common.h"
#include "c6h6_model.h" // emlearn generated model
#include "data.h"

int benchmark_main(void)
{
    volatile float noprint_output;
    float out;
    int i, j;
    for (i = TESTCASES - 1; i >= 0; i--)
    {
        out = c6h6_model_predict(testFeatures[i], 7);
        for (j = 0; j < 6; j++)
        {
            printf("%hu, ", testFeatures[i][j]);
        }
        printf("%hu: ", testFeatures[i][6]);
        printf("%f\r\n", printf_float(out));
        //uint32_t bits_out;
        //memcpy(&bits_out, &out, sizeof(uint32_t));
        //printf("%lx\r\n", bits_out);
    }

    noprint_output = out;
    (void)noprint_output;

    return 0;
}
