#include "fixed_point.h"
#include <math.h>
#include <stddef.h>
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
    fixed_point_t result = (a << SHIFT) / b;
    result = int2fix(result);
    result >>= SHIFT;
    return result;
}

fixed_point_t fixed_sqrt(fixed_point_t a)
{
    fixed_point_t value = a / 2;
    fixed_point_t last = 0;
    while (abs(value - last) > eps) {
        last = value;
        value = (value + fixed_div(a, value)) >> 1;
    }
    return value;
}

fixed_point_t fixed_log(fixed_point_t a)
{
    fixed_point_t b = int2fix(1) >> 1;
    fixed_point_t y = 0;
    while (a < int2fix(1)) {
        a <<= 1;
        y -= int2fix(1);
    }
    while (a >= int2fix(2)) {
        a >>= 1;
        y += int2fix(1);
    }
    fixed_point_t z = a;
    for (size_t i = 0; i < FRACTION_BITS; i++) {
        z = fixed_mul(z, z);
        if (z >= int2fix(2)) {
            z >>= 1;
            y += b;
        }
        b >>= 1;
    }
    return (y * INV_LOG2_E) >> 31;
}
