#ifndef SETUP_H
#define SETUP_H

extern int n_sample_sended;
extern float freq_pkg;
extern float freq_sample;
extern int n_sample;

/* Task para configurar n_sample, freq_sample e freq_pkg*/
void setup(void *p1, void *p2, void *p3);

#endif
