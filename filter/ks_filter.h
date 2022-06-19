#ifndef KS_FILTER_H_
#define KS_FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 400 Hz

fixed point precision: 16 bits

* 0 Hz - 10 Hz
  gain = 0
  desired attenuation = -30 dB
  actual attenuation = n/a

* 15 Hz - 24 Hz
  gain = 1
  desired ripple = 0.1 dB
  actual ripple = n/a

* 30 Hz - 200 Hz
  gain = 0
  desired attenuation = -30 dB
  actual attenuation = n/a

*/

#define KS_FILTER_TAP_NUM 153

typedef struct {
  int history[KS_FILTER_TAP_NUM];
  unsigned int last_index;
} ks_Filter;

void ks_Filter_init(ks_Filter* f);
void ks_Filter_put(ks_Filter* f, int input);
int ks_Filter_get(ks_Filter* f);

#endif