#include <cstdint>
#include <array>
#include "bitboard_utils.h"
#include "bitboards.h"


struct PieceDisplay {
    Color color;
    PieceType type;
    char symbol;
};

const std::array<PieceDisplay, 12> piece_displays = {{
    {Color::WHITE, PieceType::PAWN,   'P'},
    {Color::WHITE, PieceType::KNIGHT, 'N'},
    {Color::WHITE, PieceType::BISHOP, 'B'},
    {Color::WHITE, PieceType::ROOK, 'R'},
    {Color::WHITE, PieceType::QUEEN, 'Q'},
    {Color::WHITE, PieceType::KING, 'K'},
    {Color::BLACK, PieceType::PAWN,   'p'},
    {Color::BLACK, PieceType::KNIGHT, 'n'},
    {Color::BLACK, PieceType::BISHOP, 'b'},
    {Color::BLACK, PieceType::ROOK, 'r'},
    {Color::BLACK, PieceType::QUEEN, 'q'},
    {Color::BLACK, PieceType::KING, 'k'}
    
}};

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

uint64_t white_occupied(const BoardState& board) {
    return board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::KING)];
}

uint64_t black_occupied(const BoardState& board) {
    return board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::KING)];
}

uint64_t all_occupied(const BoardState& board) {
    return board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)]
         | board.bitboards[piece_index(Color::WHITE, PieceType::KING)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)]
         | board.bitboards[piece_index(Color::BLACK, PieceType::KING)];
}

void print_board(const BoardState& board) {
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank+1;
        std::cout << " ";
        for (int file = 0; file <= 7; ++file) {
            int square = square_index(rank, file);
            char symbol = '.';
            for (const auto& pd : piece_displays) {
                if ((board.bitboards[piece_index(pd.color, pd.type)] >> square) & 1) {
                    symbol = pd.symbol;
                    break;
                }
            }
            std::cout << symbol;
        }
        std::cout << "\n";
    }
    std::cout << "  abcdefgh";
}