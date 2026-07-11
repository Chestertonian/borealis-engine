#include "game.h"
#include "bitboard_utils.h"
#include "bitboards.h"
#include <iostream>
#include <vector>

int main()
{

    run_game(); 
    // BoardState state = load_fen("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  ");
    // long long perft_number = perft(state, 5);

    // state = apply_move(state, Move{12, 28, MoveType::DoublePawnPush});
    // state = apply_move(state, Move{52, 36, MoveType::DoublePawnPush});
    // state = apply_move(state, Move{11, 27, MoveType::DoublePawnPush});
    // state = apply_move(state, Move{48, 32});
    // std::cout << perft_number << " possible moves at depth 5. \n";
    // print_board(state);
    // perft_divide(state, 2);
    // std::vector moves = generate_all_moves(state, state.side_to_move);

    // for (const Move &move : moves)
    // {
    //     std::cout << square_to_algebraic(move.from) << " -> " << square_to_algebraic(move.to) << '\n';
    // }

    // print_board(state);

    return 0;
}