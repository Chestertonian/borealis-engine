// #include "game.h"
#include "bitboard_utils.h"
#include "bitboards.h"
#include <iostream>
#include <vector>

int main()
{
    BoardState state = starting_position();
    // for (int board = 0; board < 12; board++) {
    // print_bitboard(state.bitboards[board]);
    //     std::cout << "Bitboard #" << board << " loaded.\n";
    // std::cout << "\n";
    // }

    print_board(state);
    std::cout << "\n";
    std::vector moves = generate_all_moves(state, Color::WHITE);
    for (const Move &move : moves)
    {
        std::cout << square_to_algebraic(move.from) << " -> " << square_to_algebraic(move.to) << '\n';
    }
    state = apply_move(state, Move{1, 18, MoveType::Normal});
    print_board(state);

    return 0;
    // play_game(); // return later
}