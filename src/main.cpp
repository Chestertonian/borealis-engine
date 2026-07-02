#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"


int main()
{
    GameState state;

    fen_to_gamestate("8/3p4/8/8/8/8/8/K6k w - - 98 150", state); //testing position

    // setup_starting_gamestate(state);

    Move test_move = Move{coordinate_to_square("a1"), coordinate_to_square("a2"), MoveType::Normal};
    state = apply_move(state, test_move);
    print_move(test_move);
    print_gamestate(state);

    test_move = Move{coordinate_to_square("h1"), coordinate_to_square("g1"), MoveType::Normal};
    state = apply_move(state, test_move);
    print_move(test_move);
    print_gamestate(state);

    GameStatus status = get_game_status(state);
    std::cout << game_status_to_string(status);

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