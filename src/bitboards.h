#pragma once

#include <cstdint>
#include <array>
#include "bitboard_utils.h"
#include <iostream>
#include <vector>
#include "MoveStruct.h"

// Index into a 12-element bitboard array: 0-5 = white pieces, 6-11 = black,
// ordered PAWN..KING within each color.
int piece_index(Color color, PieceType type);

struct BoardState
{
    std::array<uint64_t, 12> bitboards{}; // one bit per square, per piece type/color

    Color side_to_move;
    uint8_t castling_rights; // 4 bits used: WK, WQ, BK, BQ
    int en_passant_square;   // -1 if none
    int halfmove_clock;
    int fullmove_number;
};

// Returns a BoardState set up for the starting position
BoardState starting_position();

// FEN loading
int algebraic_to_square(const std::string &algebraic);
BoardState load_fen(const std::string &fen);

// Converts to the bitboard to which it belongs.
int piece_index(Color color, PieceType type);

// Checks if a square is attacked.
bool is_square_attacked(const BoardState &board, int square, Color attacking_color);

// Generate bitboards to show piece occupancy (useful for move generation!)
uint64_t white_occupied(const BoardState &board);
uint64_t black_occupied(const BoardState &board);
uint64_t all_occupied(const BoardState &board);

void print_board(const BoardState &board);

PieceType piece_at(const BoardState &board, int square, Color color);

int find_king_square(const BoardState &board, Color color);

// Generate knight attacks.
uint64_t knight_attacks(int square);

// Generate king attacks.
uint64_t king_attacks(int square);

// Generate pawn attacks (NOT pushes!).
uint64_t pawn_attacks(int square, Color color);

// Generate rook attacks (slider!).
uint64_t rook_attacks(int square, uint64_t all_occupied, uint64_t own_occupied);

// Generate bishop attacks (another slider!).
uint64_t bishop_attacks(int square, uint64_t all_occupied, uint64_t own_occupied);

// Generate queen attacks.
uint64_t queen_attacks(int square, uint64_t all_occupied, uint64_t own_occupied);

// All of these compile the sets of moves generated.
std::vector<Move> generate_knight_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_bishop_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_pawn_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_king_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_rook_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_queen_moves(const BoardState &board, int from_square, Color color);
std::vector<Move> generate_castle_moves(const BoardState &board, Color color);

std::vector<Move> generate_all_moves(const BoardState &board, Color color);

std::vector<Move> generate_legal_moves(const BoardState &board, Color color);

BoardState apply_move(const BoardState &board, const Move &move);

long long perft(const BoardState &state, int depth);
void perft_divide(const BoardState &state, int depth);
void print_move(const Move &move);
int count_bits(uint64_t bitboard);

