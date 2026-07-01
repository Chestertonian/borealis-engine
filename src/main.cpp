#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main()
{
    GameState state;
    setup_starting_gamestate(state);
    // fen_to_gamestate("7r/p7/P7/8/3KpRBQ/3P1P2/8/N7 b - - 0 1", state);
    // fen_to_gamestate("3k4/1N6/8/8/8/8/8/8 w - - 0 1", state);
    print_gamestate(state);

    // std::vector<Move> all_moves = generate_all_moves(state);
    // for (const Move &m : all_moves)
    // {
    //     print_move(m);
    // };

    Move test_move = Move{coordinate_to_square("e2"), coordinate_to_square("e4")};
    state = apply_move(state, test_move);
    print_move(test_move);
    print_gamestate(state);

    // Test square_to_coordinate
    // std::cout << "Square 0:  " << square_to_coordinate(0) << '\n';  // a8
    // std::cout << "Square 63: " << square_to_coordinate(63) << '\n'; // h1
    // std::cout << "Square 28: " << square_to_coordinate(28) << '\n'; // e5

    // Test coordinate_to_square
    // std::cout << "e4 -> square " << coordinate_to_square("e4") << '\n'; //
    // std::cout << "e2 -> square " << coordinate_to_square("e2") << '\n'; //
    // std::cout << "h1 -> square " << coordinate_to_square("h1") << '\n'; // 63

    return 0;
}