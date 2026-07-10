#pragma once


enum class PieceType { NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum class Color { WHITE, BLACK };

enum class MoveType {
    Normal,
    DoublePawnPush,
    EnPassant,
    CastleKingside,
    CastleQueenside,
    Promotion
};

struct Move {
    int from;
    int to;
    MoveType type;
    PieceType promotion_piece;
};