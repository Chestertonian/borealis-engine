#include "game.h"
#include "bitboard_utils.h"
#include "bitboards.h"

int main()
{
    BoardState state=starting_position();
    print_bitboard(white_pawns_start);
    return 0;
    // play_game(); // return later
}