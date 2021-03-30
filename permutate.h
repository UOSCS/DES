#ifndef __PERMUTATE_H__
#define __PERMUTATE_H__

#define LENGTH_OF_INIT_PERMUTATION 64
#define LENGTH_OF_FINAL_PERMUTATION 64
#define LENGTH_OF_EXPANSION_PERMUTATION 48
#define LENGTH_OF_STRAIGHT_PERMUTATION 32
#define NUM_OF_S_BOX 8

bits_64 initial_permutation(bits_64);
bits_64 final_permutation(bits_64);
bits_64 expansion_permutation(bits_64);
bits_64 straight_permutation(bits_64);
bits_64 s_box(bits_64);
bits_64 swap(bits_64, bits_64);

#endif