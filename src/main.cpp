#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main()
{
    GameState state;
    setup_starting_gamestate(state);
    // fen_to_gamestate("a fen string", state);
    // Move test_move = Move{coordinate_to_square("e2"), coordinate_to_square("e4")};
    // state = apply_move(state, test_move);

    print_gamestate(state);

    GameStatus status = get_game_status(state);
    std::cout << game_status_to_string(status);
    std::vector<Move> all_moves = generate_all_moves(state);
    for (const Move &m : all_moves)
    {
        print_move(m);
    };

    // Test square_to_coordinate
    // std::cout << "Square 0:  " << square_to_coordinate(0) << '\n';  // a8

    // Test coordinate_to_square
    // std::cout << "e4 -> square " << coordinate_to_square("e4") << '\n'; //

    return 0;
}