#ifndef PS_FILTER_H_
#define PS_FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 400 Hz

fixed point precision: 16 bits

* 0 Hz - 4 Hz
  gain = 1
  desired ripple = 0.5 dB
  actual ripple = n/a

* 6 Hz - 200 Hz
  gain = 0
  desired attenuation = -30 dB
  actual attenuation = n/a

*/

#define PS_FILTER_TAP_NUM 279

typedef struct {
  int history[PS_FILTER_TAP_NUM];
  unsigned int last_index;
} ps_Filter;

void ps_Filter_init(ps_Filter* f);
void ps_Filter_put(ps_Filter* f, int input);
int ps_Filter_get(ps_Filter* f);

#endif