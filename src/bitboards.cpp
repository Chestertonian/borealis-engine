#include <cstdint>
#include <array>
#include "bitboard_utils.h"
#include "bitboards.h"

BoardState starting_position() {
    BoardState board;
    uint64_t white_rooks = (1ULL << square_index(0, 0)) | (1ULL << square_index(0, 7));
    board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)] = white_rooks;
    uint64_t white_knights = (1ULL << square_index(0, 1)) | (1ULL << square_index(0, 6));
    board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)] = white_knights;
    uint64_t white_bishops = (1ULL << square_index(0, 2)) | (1ULL << square_index(0, 5));
    board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)] = white_bishops;
    uint64_t white_queen = (1ULL << square_index(0, 3));
    board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)] = white_queen;
    uint64_t white_king = (1ULL << square_index(0, 4));
    board.bitboards[piece_index(Color::WHITE, PieceType::KING)] = white_king;
    uint64_t white_pawns = (0xFFULL << (8*1));
    board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)] = white_pawns;

    uint64_t black_rooks = (1ULL << square_index(7, 0)) | (1ULL << square_index(7, 7));
    board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)] = black_rooks;
    uint64_t black_knights = (1ULL << square_index(7, 1)) | (1ULL << square_index(7, 6));
    board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)] = black_knights;
    uint64_t black_bishops = (1ULL << square_index(7, 2)) | (1ULL << square_index(7, 5));
    board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)] = black_bishops;
    uint64_t black_queen = (1ULL << square_index(7, 3));
    board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)] = black_queen;
    uint64_t black_king = (1ULL << square_index(7, 4));
    board.bitboards[piece_index(Color::BLACK, PieceType::KING)] = black_king;
    uint64_t black_pawns = (0xFFULL << (8*6));
    board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)] = black_pawns;

    board.side_to_move=Color::WHITE;
    board.en_passant_square=-1;
    board.castling_rights=0b1111;
    board.halfmove_clock=0;
    board.fullmove_number=1;

    return board;
}

int piece_index(Color color, PieceType type) {
    return static_cast<int>(color) * 6 + static_cast<int>(type);
}