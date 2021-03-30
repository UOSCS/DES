#include "common.h"
#include "permutate.h"

bits_64 initial_permutation(bits_64 plaintext)
{
    bits_64 init_permutated_plaintext = 0;
    for(int i = 0; i < LENGTH_OF_INIT_PERMUTATION; i++)
        init_permutated_plaintext |= ((plaintext >> (INIT_PERMUTATION[i] - 1)) & 1) << i;
    return init_permutated_plaintext;
}

bits_64 final_permutation(bits_64 after_16rounds)
{
    bits_64 ciphertext = 0;
    for(int i = 0; i < LENGTH_OF_FINAL_PERMUTATION; i++)
        ciphertext |= ((after_16rounds >> (FINAL_PERMUTATION[i] - 1)) & 1) << i;
    return ciphertext;
}

bits_64 expansion_permutation(bits_64 right_half)
{
    bits_64 expanded_right_half = 0;
    for(int i = 0; i < LENGTH_OF_EXPANSION_PERMUTATION; i++)
        expanded_right_half |= ((right_half >> (EXPANSION_PERMUTATION[i] - 1)) & 1) << i;
    return expanded_right_half;
}

bits_64 straight_permutation(bits_64 after_S_box)
{
    bits_64 after_straight_permutation = 0;
    for(int i = 0; i < LENGTH_OF_STRAIGHT_PERMUTATION; i++)
        after_straight_permutation |= ((after_S_box >> (STRAIGHT_PERMUTATION[i] - 1)) & 1) << i;
    return after_straight_permutation;
}

bits_64 s_box(bits_64 right_XOR_key)
{
    bits_64 result = 0;
    for(int i = 0, row, col; i < NUM_OF_S_BOX; i++)
    {
        bits_64 take_6_bits = right_XOR_key & 0x3F;
        row = (take_6_bits & 1) + ((take_6_bits & 0x20) >> 5);
        col = (take_6_bits >> 1) & 0xF;
        result |= S_BOX[i][row * 16 + col];
        result <<= 4;
        right_XOR_key >>= 6;
    }
    return result;
}

bits_64 swap(bits_64 left_half, bits_64 right_half)
{
    right_half <<= LENGTH_OF_BIT / 2;
    left_half >>= LENGTH_OF_BIT / 2;
    return right_half | left_half;
}