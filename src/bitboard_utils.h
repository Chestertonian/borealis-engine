#pragma once

#include <cstdint>
#include "bitboards.h"
#include <array>


// Converts a (rank, file) pair to a LERF square index (a1 = 0, h8 = 63).
// rank: 0-7, where 0 = rank 1
// file: 0-7, where 0 = file a
int square_index(int rank, int file);

// Prints a 64-bit bitboard as an 8x8 grid, rank 8 on top, file a on the left.
// Mostly debug utility.
void print_bitboard(uint64_t bitboard);

std::string square_to_algebraic(int square);