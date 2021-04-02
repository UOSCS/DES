#include "common.h"
#include "round.h"
#include "key.h"
#include "permutate.h"

int main(void)
{
    // answer: E5A951F59B3160C0
    bits_64 plaintext = 0x0123456789ABCDEF;
    bits_64 key = 0x85E813540F0AB405;
    bits_64 init_permutated_plaintext;
    bits_64 after_16rounds;
    bits_64 ciphertext;

    key_generator(key);
    init_permutated_plaintext = permutation(plaintext, LENGTH_OF_BIT, INIT_PERMUTATION, LENGTH_OF_INIT_PERMUTATION);
    after_16rounds = execute_16rounds(init_permutated_plaintext, generated_keys);
    ciphertext = permutation(after_16rounds, LENGTH_OF_BIT, FINAL_PERMUTATION, LENGTH_OF_FINAL_PERMUTATION);

    printf("Cipher Text: %016lX\n", ciphertext);

    return 0;
}