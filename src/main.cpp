#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main() {
    GameState state;
    // setup_starting_gamestate(state);
    fen_to_gamestate("7r/8/8/8/4KRBQ/8/8/N7 w - - 0 1", state);
    print_gamestate(state);

    std::vector<Move> knight_moves = generate_knight_moves(state, coordinate_to_square("a1"));
    for (const Move& m : knight_moves) {
        print_move(m);
    }
    
    std::vector<Move> king_moves = generate_king_moves(state, coordinate_to_square("e4"));
    for (const Move& m : king_moves) {
        print_move(m);
    };

    std::vector<Move> rook_moves = generate_rook_moves(state, coordinate_to_square("f4"));
    for (const Move& m : rook_moves) {
        print_move(m);
    };

    std::vector<Move> bishop_moves = generate_bishop_moves(state, coordinate_to_square("g4"));
    for (const Move& m : bishop_moves) {
        print_move(m);
    };

    std::vector<Move> queen_moves = generate_queen_moves(state, coordinate_to_square("h4"));
    for (const Move& m : queen_moves) {
        print_move(m);
    };



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