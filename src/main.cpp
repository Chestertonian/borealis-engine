#include "game.h"
#include "bitboard_utils.h"


int main()
{
    uint64_t white_pawns_start = 0x000000000000FF00ULL;
    print_bitboard(white_pawns_start);
    return 0;
    // play_game(); // return later
}