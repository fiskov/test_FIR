#include "ksps_signal.h"
#include "ks_filter.h"
#include "ps_filter.h"


#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

#define M_PI	3.14159265358979323846



static ks_Filter fks = {};
static ps_Filter fps = {};
static int ks_values[256] = {}, ks_values_pos = 0;


int get_ks(int value)
{
    ks_Filter_put(&fks, value);
    return ks_Filter_get(&fks);
}

int get_ks_ampl(int value, int period)
{
    ks_values[ ks_values_pos++ ] = value;
    if (ks_values_pos >= period) ks_values_pos = 0;
    int *p_value = ks_values;
    /*
    int max_value = -4096, min_value = 4096;
    while (period--)
    {
        max_value = MAX(*p_value, max_value);
        min_value = MIN(*p_value, min_value);
        p_value++;
    }

    return max_value-min_value;
    */
   long long sum = 0, square_sum = 0;
   int count = period;
    while (period--)
    {
        sum += (*p_value);
        square_sum += (*p_value) * (*p_value);
        p_value++;
    }
    int mean = sum / count;
    return sqrt((square_sum - (long)mean*sum)/count);
}


int get_ps(int value)
{
    ps_Filter_put(&fps, value);
    return ps_Filter_get(&fps);
}



static double signal_sin(double t, double freq_sin, double ampl)
{
    return ampl * sin(2 * M_PI * freq_sin * t);
}
static double signal_square(double t, double freq_square, double ampl)
{
    double decimal_value = t * freq_square;
    return  ampl / 2 * ((decimal_value - (int)decimal_value) < 0.5 ? -1 : 1);
}
double get_signal_value(double t, signal_param_t * sp)
{
    return sp->ps_offset
            +signal_square(t, sp->ps_freq, sp->ps_ampl)
            +signal_square(t, sp->ks_freq, sp->ks_ampl)
            +signal_sin(t, sp->noise_low_freq, sp->noise_low_ampl)
            +signal_sin(t, sp->noise_high_freq, sp->noise_high_ampl)
            ;
}





static float random_in_range(float min_value, float max_value)
{
    return (1.0*rand()/RAND_MAX)*(max_value-min_value)+min_value;
}

void update_signal_noise(signal_param_t * sp)
{
    sp->noise_low_freq = random_in_range(5, 10);
    sp->noise_high_freq = random_in_range(27, 75);

    sp->noise_low_ampl = random_in_range(100, 1000);
    sp->noise_high_ampl = random_in_range(100, 1000);
}

void generate_signal_bfr(uint16_t bfr[], size_t length, signal_param_t *sp)
{
    for (size_t pos=0; pos<length; pos++)
        bfr[pos] = get_signal_value(pos / 1000.0, sp);
}
