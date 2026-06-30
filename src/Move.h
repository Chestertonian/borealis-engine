#ifndef MOVE_H
#define MOVE_H

#include <string>

enum class PieceType { None, Pawn, Knight, Bishop, Rook, Queen, King };

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

void print_move(const Move& move);

#endif