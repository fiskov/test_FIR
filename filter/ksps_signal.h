#ifndef KSPS_SIGNAL_H
#define KSPS_SIGNAL_H

#include <stdint.h>
#include <stdlib.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct signal_param_t
{
    double ks_ampl, ks_freq;
    double ps_offset, ps_ampl, ps_freq;
    double noise_high_freq, noise_low_freq;
    double noise_high_ampl, noise_low_ampl;
} signal_param_t;


int get_ks(int);
int get_ps(int);

int get_ks_ampl(int value, int period);

void update_signal_noise(signal_param_t * sp);
void generate_signal_bfr(uint16_t bfr[], size_t length, signal_param_t * sp);

#endif // KSPS_SIGNAL_H
