#include "bitboards.h"
#include "bitboard_utils.h"
#include <string>

std::string move_to_san(const Move &move,
                        const BoardState &before,
                        const std::vector<Move> &legal_moves_before,
                        const BoardState &after,
                        const std::vector<Move> &legal_moves_after);

char piece_letter(PieceType type);
