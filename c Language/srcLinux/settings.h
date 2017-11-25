#include "stddef.h"

#ifndef SETTINGS_H
#define SETTINGS_H


struct settings {
  int mask;
  int numa_enabled;
  size_t tt_size;
  size_t num_threads;
  int large_pages;
  int clear;
};

extern struct settings settings, delayed_settings;

void process_delayed_settings(void);

#endif

