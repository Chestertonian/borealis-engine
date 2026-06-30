#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include <string>

enum class Color { White, Black };

struct GameState {
    Board board;
    Color side_to_move;

    bool white_kingside_castle;
    bool white_queenside_castle;
    bool black_kingside_castle;
    bool black_queenside_castle;

    int en_passant_square;   // -1 if none
    int halfmove_clock;
    int fullmove_number;
};

void setup_starting_gamestate(GameState& state);
void fen_to_gamestate(const std::string& fen, GameState& state);
void print_gamestate(const GameState& state);

#endif