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

// Used primarily for check/mate.
bool is_square_attacked(const GameState& state, int square, Color by_color);
int  find_king_square(const GameState& state, Color king_color);

// Pawn moves treated differently (en passant, promotion, weird capture).
void add_pawn_move(std::vector<Move>& moves, int from, int to, bool is_promotion);

// Piece-specific generators (pseudo-legal)
std::vector<Move> generate_knight_moves(const GameState& state, int from_square);
std::vector<Move> generate_king_moves(const GameState& state, int from_square);
std::vector<Move> generate_rook_moves(const GameState& state, int from_square);
std::vector<Move> generate_bishop_moves(const GameState& state, int from_square);
std::vector<Move> generate_queen_moves(const GameState& state, int from_square);
std::vector<Move> generate_pawn_moves(const GameState& state, int from_square);

// Castling generators.
std::vector<Move> generate_castling_moves(const GameState& state);

// Top-level generators (all pseudo-moves for the side to move)
std::vector<Move> generate_pseudolegal_moves(const GameState& state);
std::vector<Move> generate_all_moves(const GameState& state);

// perft testing function
long long perft(const GameState& state, int depth);

#endif