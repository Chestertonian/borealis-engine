#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main()
{
    GameState state;

    // fen_to_gamestate("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", state); testing purposes

    setup_starting_gamestate(state);

    // Move test_move = Move{coordinate_to_square("a2"), coordinate_to_square("a1"), MoveType::Promotion, PieceType::Queen};
    // state = apply_move(state, test_move);
    // print_move(test_move);
    // print_gamestate(state);

    // perft_divide(state, 2);

    // for (int depth = 1; depth <= 4; ++depth)
    // {
    //     std::cout << "Perft(" << depth << ") = " << perft(state, depth) << std::endl;
    // }

    //

    // print_gamestate(state);

    // std::vector<Move> all_moves = generate_all_moves(state);
    // for (const Move &m : all_moves)
    // {
    //    print_move(m);
    // };

    // Test square_to_coordinate
    // std::cout << "Square 0:  " << square_to_coordinate(0) << '\n';  // a8

    // Test coordinate_to_square
    // std::cout << "e3 -> square " << coordinate_to_square("e3") << '\n';
    // std::cout << "d6 -> square " << coordinate_to_square("d6") << '\n'; //

    return 0;
}