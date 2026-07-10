#pragma once


enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

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