#include "Board.h"
#include <iostream>
#include "GameState.h"
#include "Move.h"
#include "MoveGen.h"

int main()
{
    GameState state;

    // fen_to_gamestate("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ", state); (KIWIPETE position)
    setup_starting_gamestate(state);
    
    Move test_move = Move{coordinate_to_square("e2"), coordinate_to_square("e4"), MoveType::DoublePawnPush};
    state = apply_move(state, test_move);
    print_move(test_move);
    print_gamestate(state);
    perft_divide(state, 6);

    // for (int depth = 1; depth <= 4; ++depth) {
    //   std::cout << "Perft(" << depth << ") = " << perft(state, depth) << std::endl;
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
    // std::cout << "d5 -> square " << coordinate_to_square("d5") << '\n'; 
    // std::cout << "d6 -> square " << coordinate_to_square("d6") << '\n'; //


    return 0;
}