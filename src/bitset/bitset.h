#ifndef STDC_BITSET_H
#define STDC_BITSET_H


typedef struct vector Bitset;

void bitset_not(Bitset *self);

void bitset_and(Bitset *self, Bitset *other);

void bitset_or(Bitset *self, Bitset *other);

void bitset_xor(Bitset *self, Bitset *other);


void bitset_lshift(Bitset *self, uint64_t shift);

void bitset_rshift(Bitset *self, uint64_t shift);


#endif /* STDC_BITSET_H */