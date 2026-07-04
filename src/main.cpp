// #include "game.h"
#include "bitboard_utils.h"
#include "bitboards.h"
#include <iostream>

int main()
{
    BoardState state=starting_position();
    for (int board = 0; board < 12; board++) {
        print_bitboard(state.bitboards[board]);
        std::cout << "\n";
    }

    print_board(state);
    return 0;
    // play_game(); // return later
}