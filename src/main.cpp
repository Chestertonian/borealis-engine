#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main()
{
    GameState state;
    // setup_starting_gamestate(state);
    fen_to_gamestate("r3k3/8/8/8/8/8/8/4K2R w Kq - 0 100", state);

    print_gamestate(state);

    std::vector<Move> all_moves = generate_all_moves(state);
    for (const Move &m : all_moves)
    {
        print_move(m);
    };

    // test_move = Move{coordinate_to_square("e5"), coordinate_to_square("d6"), MoveType::EnPassant};
    // state = apply_move(state, test_move);
    // print_move(test_move);
    // print_gamestate(state);


    // Test square_to_coordinate
    // std::cout << "Square 0:  " << square_to_coordinate(0) << '\n';  // a8

    // Test coordinate_to_square
    // std::cout << "d5 -> square " << coordinate_to_square("d5") << '\n'; 
    // std::cout << "d6 -> square " << coordinate_to_square("d6") << '\n'; //


    return 0;
}