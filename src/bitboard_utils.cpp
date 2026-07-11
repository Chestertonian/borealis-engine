#include <iostream>
#include <cstdint>
#include <string>
#include "bitboards.h"


int square_index(int rank, int file)
{
    return rank * 8 + file;
}

void print_bitboard(uint64_t bitboard)
{
    for (int rank = 7; rank >= 0; rank--)
    { // rank 8 first, rank 1 last
        for (int file = 0; file <= 7; ++file)
        { // file a to file h
            int square = square_index(rank, file);
            int bit = (bitboard >> square) & 1;
            std::cout << bit;
            
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string square_to_algebraic(int square) {
    int rank = square / 8;
    int file = square % 8;
    char file_char = 'a' + file;
    char rank_char = '1' + rank;
    return std::string(1, file_char) + std::string(1, rank_char);
}