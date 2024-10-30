#ifndef TIME_SORTS_H
#define TIME_SORTS_H

#include "subscriber_funcs.h"

void generate_dataset(subscriber_t subscribers[], int dataset_size);
void measure_sorting_times_bubble(subscriber_t subscribers[], key_t keys[], int num_subscribers);
void measure_sorting_times_quick(subscriber_t subscribers[], key_t keys[], int num_subscribers);

#endif//TIME_SORTS_H
