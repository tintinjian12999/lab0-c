#include "fixed_point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
fixed_point_t fixed_add(fixed_point_t a, fixed_point_t b)
{
    return a + b;
}

fixed_point_t fixed_sub(fixed_point_t a, fixed_point_t b)
{
    return a - b;
}

fixed_point_t fixed_mul(fixed_point_t a, fixed_point_t b)
{
    return (a * b) >> FRACTION_BITS;
}

fixed_point_t fixed_div(fixed_point_t a, fixed_point_t b)
{
    fixed_point_t result = (a << FRACTION_BITS) / b;
    result = int2fix(result);
    result >>= FRACTION_BITS;
    return result;
}

fixed_point_t fixed_sqrt(fixed_point_t a)
{
    fixed_point_t value = a;
    fixed_point_t last = 0;
    while (abs(value - last) > eps) {
        last = value;
        value = (value + fixed_div(a, value)) >> 1;
    }
    return value;
}
int main()
{
    FILE *file;
    file = fopen("compare.txt", "w");
    if (file == NULL) {
        printf("無法打開檔案。\n");
        return 1;
    }
    for (int i = 1; i < 201; i++) {
        fixed_point_t result = 0;
        result = fixed_sqrt(int2fix(i));
        int frac = frac2int(extract_frac(result));
        float result_float = 0;
        float error = (float) fix2int(result) + frac / 1000.0;
        result_float = sqrt(i);
        error = 100 * fabs(error - result_float) / result_float;
        fprintf(file, "%d %d.%d %.3f %f\n", i, fix2int(result), frac,
                result_float, error);
    }
    fclose(file);
}