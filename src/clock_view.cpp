#include "clock_view.h"
#include "config.h"
#include <math.h>

static const int16_t cx = 120;
static const int16_t cy = 120;
static const int16_t r  = 105;

static uint8_t sec = 0;
static uint8_t min = 42;
static uint8_t hrs = 10;