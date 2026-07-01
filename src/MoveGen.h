#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>
#include "Move.h"
#include "GameState.h"

// Helpers
bool is_white_piece(char piece);
bool is_black_piece(char piece);
bool is_friendly(char piece, Color side);
bool is_enemy(char piece, Color side);
bool is_empty(char piece);

// Piece-specific generators (pseudo-legal)
std::vector<Move> generate_knight_moves(const GameState& state, int from_square);
std::vector<Move> generate_king_moves(const GameState& state, int from_square);
std::vector<Move> generate_rook_moves(const GameState& state, int from_square);
std::vector<Move> generate_bishop_moves(const GameState& state, int from_square);
std::vector<Move> generate_queen_moves(const GameState& state, int from_square);


// Top-level generator (all pseudo-legal moves for the side to move)
std::vector<Move> generate_all_moves(const GameState& state);

#endif