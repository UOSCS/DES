#include "common.h"

bits_64 get_left_half(bits_64 generated_key, int length)
{
    return generated_key >> (length / 2);
}

bits_64 get_right_half(bits_64 generated_key, int length)
{
    bits_64 bit_mask = 1;
    for(int i = 0; i < length / 2; i++)
        bit_mask *= 2;
    bit_mask -= 1;
    return generated_key & bit_mask;
}