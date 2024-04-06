#include "fixed_point.h"
#include <stdio.h>
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
int main()
{
    int a = 2, b = 3;
    fixed_point_t result = 0;
    result = fixed_div(int2fix(a), int2fix(b));
    int frac = frac2int(extract_frac(result));
    printf("%d.%d\n", fix2int(result), frac);
}