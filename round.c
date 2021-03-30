#include "common.h"
#include "round.h"
#include "permutate.h"

bits_64 execute_16rounds(bits_64 init_permutated_plaintext, bits_64 *generated_keys)
{
    bits_64 after_16rounds;
    bits_64 left_half = get_left_half(init_permutated_plaintext, LENGTH_OF_BIT);
    bits_64 right_half = get_right_half(init_permutated_plaintext, LENGTH_OF_BIT);
    for(int i = 0; i < NUM_OF_ROUND; i++)
    {
        bits_64 expanded_right_half = expansion_permutation(right_half);
        bits_64 right_XOR_key = expanded_right_half ^ generated_keys[i];
        bits_64 after_S_box = s_box(right_XOR_key);
        printf("%lx\n", after_S_box);
        bits_64 after_straight_permutation = straight_permutation(after_S_box);
        bits_64 left_XOR_func_r = left_half ^ after_straight_permutation;
        left_half = right_half;
        right_half = left_XOR_func_r;
    }
    after_16rounds = swap(left_half, right_half);
    return after_16rounds;
}