typedef long fixed_point_t;
#define FRACTION_BITS 16
#define int2fix(a) ((fixed_point_t)((a) << FRACTION_BITS))
#define fix2int(a) ((int) ((a >> FRACTION_BITS)))
#define extract_frac(a) ((int) (a & (int2fix(1) - 1)))
#define frac2int(a) ((int) ((a * 1000) >> FRACTION_BITS))
#define eps int2fix(1) >> 10
fixed_point_t fixed_add(fixed_point_t a, fixed_point_t b);
fixed_point_t fixed_sub(fixed_point_t a, fixed_point_t b);
fixed_point_t fixed_mul(fixed_point_t a, fixed_point_t b);
fixed_point_t fixed_div(fixed_point_t a, fixed_point_t b);
fixed_point_t fixed_sqrt(fixed_point_t a);
fixed_point_t fixed_log(fixed_point_t a);