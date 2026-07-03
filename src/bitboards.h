#pragma once

#include <cstdint>
#include <array>
#include "bitboard_utils.h"

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum class Color { WHITE, BLACK };

// Index into a 12-element bitboard array: 0-5 = white pieces, 6-11 = black,
// ordered PAWN..KING within each color. Same idea as an enum-to-array-index
// pattern you've already used for PieceType elsewhere.
int piece_index(Color color, PieceType type);

struct BoardState {
    std::array<uint64_t, 12> bitboards{}; // one bit per square, per piece type/color

    Color side_to_move;
    uint8_t castling_rights;   // 4 bits used: WK, WQ, BK, BQ
    int en_passant_square;     // -1 if none
    int halfmove_clock;
    int fullmove_number;
};

// Returns a BoardState set up for the standard chess starting position.
BoardState starting_position();

// Converts to the bitboard to which it belongs.
int piece_index(Color color, PieceType type);