#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>

#define NUM_OF_ROUND 16
#define LENGTH_OF_BIT 64

typedef uint64_t bits_64;

bits_64 generated_keys[NUM_OF_ROUND];

bits_64 get_left_half(bits_64, int);
bits_64 get_right_half(bits_64, int);

#endif