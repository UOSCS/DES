#ifndef __KEY_H__
#define __KEY_H__

#define LENGTH_OF_INIT_KEY_SELECTION 56
#define LENGTH_OF_KEY_COMPRESSION 48

void key_generator(bits_64);
bits_64 left_shift(bits_64, int);
bits_64 merge_left_right(bits_64, bits_64);

#endif