#include "Board.h"
#include <iostream>
#include "GameState.h"

int main() {
    Board board;
    setup_starting_position(board);
    print_board(board);

    GameState state;
    setup_starting_gamestate(state);
    print_gamestate(state);
    return 0;


    // Test square_to_coordinate
    // std::cout << "Square 0:  " << square_to_coordinate(0) << '\n';  // a8
    // std::cout << "Square 63: " << square_to_coordinate(63) << '\n'; // h1
    // std::cout << "Square 28: " << square_to_coordinate(28) << '\n'; // e5

    // Test coordinate_to_square
    // std::cout << "e4 -> square " << coordinate_to_square("e4") << '\n'; // 36
    // std::cout << "a8 -> square " << coordinate_to_square("a8") << '\n'; // 0
    // std::cout << "h1 -> square " << coordinate_to_square("h1") << '\n'; // 63

    return 0;
}