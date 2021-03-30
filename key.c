#include "common.h"
#include "key.h"

void *key_generator(bits_64 key)
{
    bits_64 generated_key = drop_parity_bits(key);

    bits_64 merged_bits;
    bits_64 left_half = get_left_half(generated_key, LENGTH_OF_INIT_KEY_SELECTION);
    bits_64 right_half = get_right_half(generated_key, LENGTH_OF_INIT_KEY_SELECTION);
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
    bits_64 generated_key = 0;
    for(int i = 0; i < LENGTH_OF_INIT_KEY_SELECTION; i++)
        generated_key |= ((key >> (INIT_KEY_SELECTION[i] - 1)) & 1) << i;
    return generated_key;
}

bits_64 left_shift(bits_64 left_half, int shift)
{
    bits_64 tmp;
    bits_64 bit_mask = 1;
    for(int i = 0; i < shift; i++)
        bit_mask *= 2;
    bit_mask -= 1;
    bit_mask <<= (LENGTH_OF_INIT_KEY_SELECTION / 2 - shift);
    tmp = left_half & bit_mask;
    tmp >>= (LENGTH_OF_INIT_KEY_SELECTION / 2 - shift);
    left_half <<= shift;
    left_half |= tmp;
    return left_half;
}

bits_64 merge_left_right(bits_64 left_half, bits_64 right_half)
{
    return (left_half << (LENGTH_OF_INIT_KEY_SELECTION / 2)) | right_half;
}

bits_64 compress_key(bits_64 merged_bits)
{
    bits_64 generated_key = 0;
    for(int i = 0; i < LENGTH_OF_KEY_COMPRESSION; i++)
        generated_key |= ((merged_bits >> (KEY_COMPRESSION[i] - 1)) & 1) << i;
    return generated_key;
}