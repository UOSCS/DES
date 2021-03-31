#include "common.h"
#include "key.h"

const int INIT_KEY_SELECTION[] = {
    57, 49, 41, 33, 25, 17,  9,  1,
    58, 50, 42, 34, 26, 18, 10,  2,
    59, 51, 43, 35, 27, 19, 11,  3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15,  7, 62, 54, 46, 38,
    30, 22, 14,  6, 61, 53, 45, 37,
    29, 21, 13,  5, 28, 20, 12,  4
};
const int KEY_COMPRESSION[] = {
    14, 17, 11, 24,  1,  5,  3, 28,
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};
const int ROUND[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void key_generator(bits_64 key)
{
    bits_64 original_key = drop_parity_bits(key);
    bits_64 merged_bits;
    bits_64 left_half = get_left_half(original_key, LENGTH_OF_INIT_KEY_SELECTION);
    bits_64 right_half = get_right_half(original_key, LENGTH_OF_INIT_KEY_SELECTION);
    for(int i = 0; i < NUM_OF_ROUND; i++)
    {
        left_half = left_shift(left_half, ROUND[i]);
        right_half = left_shift(right_half, ROUND[i]);
        merged_bits = merge_left_right(left_half, right_half);
        generated_keys[i] = compress_key(merged_bits);
    }
}

bits_64 drop_parity_bits(bits_64 key)
{
    bits_64 original_key = 0;
    for(int i = 0; i < LENGTH_OF_INIT_KEY_SELECTION; i++)
        original_key |= ((key >> (LENGTH_OF_BIT - INIT_KEY_SELECTION[i])) & 1) << (LENGTH_OF_INIT_KEY_SELECTION - 1 - i);
    return original_key;
}

bits_64 left_shift(bits_64 bits, int shift)
{
    bits_64 tmp;
    bits_64 bit_mask = 1;
    for(int i = 0; i < shift; i++)
        bit_mask <<= 1;
    bit_mask -= 1;
    tmp = (bits >> (LENGTH_OF_INIT_KEY_SELECTION / 2 - shift)) & bit_mask;
    bits <<= shift;
    bits |= tmp;
    bits &= 0xFFFFFFF;
    return bits;
}

bits_64 merge_left_right(bits_64 left_half, bits_64 right_half)
{
    return (left_half << (LENGTH_OF_INIT_KEY_SELECTION / 2)) | right_half;
}

bits_64 compress_key(bits_64 merged_bits)
{
    bits_64 generated_key = 0;
    for(int i = 0; i < LENGTH_OF_KEY_COMPRESSION; i++)
        generated_key |= ((merged_bits >> (LENGTH_OF_INIT_KEY_SELECTION - KEY_COMPRESSION[i])) & 1) << (LENGTH_OF_KEY_COMPRESSION - 1 - i);
    return generated_key;
}