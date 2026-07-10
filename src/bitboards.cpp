#include <cstdint>
#include <array>
#include "bitboard_utils.h"
#include "bitboards.h"
#include "MoveStruct.h"

struct PieceDisplay
{
    Color color;
    PieceType type;
    char symbol;
};

const int knight_offsets[8][2] = {
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

const int king_offsets[8][2] = {
    {1, -1}, {1, 0}, {1, 1}, {0, 1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

const int rook_directions[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

const int bishop_directions[4][2] = {
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

const int queen_directions[8][2] = {
    {1, 1}, {1, 0}, {1, -1}, {0, -1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};

const std::array<PieceDisplay, 12> piece_displays = {{{Color::WHITE, PieceType::PAWN, 'P'},
                                                      {Color::WHITE, PieceType::KNIGHT, 'N'},
                                                      {Color::WHITE, PieceType::BISHOP, 'B'},
                                                      {Color::WHITE, PieceType::ROOK, 'R'},
                                                      {Color::WHITE, PieceType::QUEEN, 'Q'},
                                                      {Color::WHITE, PieceType::KING, 'K'},
                                                      {Color::BLACK, PieceType::PAWN, 'p'},
                                                      {Color::BLACK, PieceType::KNIGHT, 'n'},
                                                      {Color::BLACK, PieceType::BISHOP, 'b'},
                                                      {Color::BLACK, PieceType::ROOK, 'r'},
                                                      {Color::BLACK, PieceType::QUEEN, 'q'},
                                                      {Color::BLACK, PieceType::KING, 'k'}

}};

BoardState starting_position()
{
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
    uint64_t white_pawns = (0xFFULL << (8 * 1));
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
    uint64_t black_pawns = (0xFFULL << (8 * 6));
    board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)] = black_pawns;

    board.side_to_move = Color::WHITE;
    board.en_passant_square = -1;
    board.castling_rights = 0b1111;
    board.halfmove_clock = 0;
    board.fullmove_number = 1;

    return board;
}

int piece_index(Color color, PieceType type)
{
    return static_cast<int>(color) * 6 + static_cast<int>(type);
}

uint64_t white_occupied(const BoardState &board)
{
    return board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)] | board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)] | board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)] | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)] | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)] | board.bitboards[piece_index(Color::WHITE, PieceType::KING)];
}

uint64_t black_occupied(const BoardState &board)
{
    return board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)] | board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)] | board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)] | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)] | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)] | board.bitboards[piece_index(Color::BLACK, PieceType::KING)];
}

uint64_t all_occupied(const BoardState &board)
{
    return board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)] | board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)] | board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)] | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)] | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)] | board.bitboards[piece_index(Color::WHITE, PieceType::KING)] | board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)] | board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)] | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)] | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)] | board.bitboards[piece_index(Color::BLACK, PieceType::KING)];
}

void print_board(const BoardState &board)
{
    for (int rank = 7; rank >= 0; --rank)
    {
        std::cout << rank + 1;
        std::cout << " ";
        for (int file = 0; file <= 7; ++file)
        {
            int square = square_index(rank, file);
            char symbol = '.';
            for (const auto &pd : piece_displays)
            {
                if ((board.bitboards[piece_index(pd.color, pd.type)] >> square) & 1)
                {
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

uint64_t knight_attacks(int square)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    for (int i = 0; i < 8; ++i)
    {
        int new_rank = rank + knight_offsets[i][0];
        int new_file = file + knight_offsets[i][1];

        if (new_rank >= 0 && new_rank <= 7 && new_file >= 0 && new_file <= 7)
        {
            attacks |= (1ULL << square_index(new_rank, new_file));
        }
    }

    return attacks;
}

uint64_t king_attacks(int square)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    for (int i = 0; i < 8; ++i)
    {
        int new_rank = rank + king_offsets[i][0];
        int new_file = file + king_offsets[i][1];

        if (new_rank >= 0 && new_rank <= 7 && new_file >= 0 && new_file <= 7)
        {
            attacks |= (1ULL << square_index(new_rank, new_file));
        }
    }

    return attacks;
}

uint64_t pawn_attacks(int square, Color color)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    if (color == Color::BLACK)
    {
        const int pawn_offsets[2][2] = {
            {-1, -1}, {-1, 1}};

        for (int i = 0; i < 2; ++i)
        {
            int new_rank = rank + pawn_offsets[i][0];
            int new_file = file + pawn_offsets[i][1];

            if (new_rank >= 0 && new_rank <= 7 && new_file >= 0 && new_file <= 7)
            {
                attacks |= (1ULL << square_index(new_rank, new_file));
            }
        }
    }

    else
    {
        const int pawn_offsets[2][2] = {
            {1, -1}, {1, 1}};

        for (int i = 0; i < 2; ++i)
        {
            int new_rank = rank + pawn_offsets[i][0];
            int new_file = file + pawn_offsets[i][1];

            if (new_rank >= 0 && new_rank <= 7 && new_file >= 0 && new_file <= 7)
            {
                attacks |= (1ULL << square_index(new_rank, new_file));
            }
        }
    }

    return attacks;
}

uint64_t rook_attacks(int square, uint64_t all_occupied, uint64_t own_occupied)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    for (int d = 0; d < 4; ++d)
    {
        int r = rank;
        int f = file;

        while (true)
        {
            r += rook_directions[d][0];
            f += rook_directions[d][1];

            if (r < 0 || r > 7 || f < 0 || f > 7)
                break;

            int target = square_index(r, f);

            if ((own_occupied >> target) & 1)
                break;

            attacks |= (1ULL << target);

            if ((all_occupied >> target) & 1)
                break;
        }
    }

    return attacks;
}

uint64_t bishop_attacks(int square, uint64_t all_occupied, uint64_t own_occupied)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    for (int d = 0; d < 4; ++d)
    {
        int r = rank;
        int f = file;

        while (true)
        {
            r += bishop_directions[d][0];
            f += bishop_directions[d][1];

            if (r < 0 || r > 7 || f < 0 || f > 7)
                break;

            int target = square_index(r, f);

            if ((own_occupied >> target) & 1)
                break;

            attacks |= (1ULL << target);

            if ((all_occupied >> target) & 1)
                break;
        }
    }

    return attacks;
}

uint64_t queen_attacks(int square, uint64_t all_occupied, uint64_t own_occupied)
{
    uint64_t attacks = 0;
    int rank = square / 8;
    int file = square % 8;

    for (int d = 0; d < 4; ++d)
    {
        int r = rank;
        int f = file;

        while (true)
        {
            r += queen_directions[d][0];
            f += queen_directions[d][1];

            if (r < 0 || r > 7 || f < 0 || f > 7)
                break;

            int target = square_index(r, f);

            if ((own_occupied >> target) & 1)
                break;

            attacks |= (1ULL << target);

            if ((all_occupied >> target) & 1)
                break;
        }
    }

    return attacks;
}

std::vector<Move> generate_knight_moves(const BoardState& board, int from_square, Color color) {
    std::vector<Move> moves;

    uint64_t attacks = knight_attacks(from_square);
    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);

    for (int target_square = 0; target_square < 64; ++target_square) {
        if ((attacks >> target_square) & 1) {
            if (!((own_pieces >> target_square) & 1)) {
                Move move{from_square, target_square};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

void test_knight_attacks()
{
    std::cout << "Knight on a1:\n";
    print_bitboard(knight_attacks(square_index(0, 0))); // expect 2 bits

    std::cout << "Knight on d4:\n";
    print_bitboard(knight_attacks(square_index(3, 3))); // expect 8 bits
}

void test_king_attacks()
{
    std::cout << "King on a1:\n";
    print_bitboard(king_attacks(square_index(0, 0))); // expect 3 bits

    std::cout << "King on d4:\n";
    print_bitboard(king_attacks(square_index(3, 3))); // expect 8 bits
}

void test_pawn_attacks()
{
    std::cout << "Pawn on a2:\n";
    print_bitboard(pawn_attacks(square_index(1, 0), Color::WHITE)); // expect 1 bit

    std::cout << "Pawn on d4:\n";
    print_bitboard(pawn_attacks(square_index(3, 3), Color::BLACK)); // expect 2 bits
}

void test_rook_attacks()
{
    std::cout << "Rook on d4, no blockers:\n";
    print_bitboard(rook_attacks(square_index(3, 3), 0ULL, 0ULL));

    uint64_t blocker_d6 = 1ULL << square_index(5, 3);
    uint64_t blocker_d2 = 1ULL << square_index(1, 3);
    uint64_t own = blocker_d6;
    uint64_t all = blocker_d6 | blocker_d2;

    std::cout << "Rook on d4, friendly blocker d6, enemy blocker d2:\n";
    print_bitboard(rook_attacks(square_index(3, 3), all, own));

    std::cout << "Rook on a1, no blockers:\n";
    print_bitboard(rook_attacks(square_index(0, 0), 0ULL, 0ULL));
}

void test_bishop_attacks()
{
    std::cout << "Bishop on d4, no blockers:\n";
    print_bitboard(bishop_attacks(square_index(3, 3), 0ULL, 0ULL));

    uint64_t blocker_e5 = 1ULL << square_index(4, 4);
    uint64_t blocker_b6 = 1ULL << square_index(5, 1);
    uint64_t own = blocker_e5;
    uint64_t all = blocker_e5 | blocker_b6;

    std::cout << "Bishop on d4, friendly blocker e5, enemy blocker b6:\n";
    print_bitboard(bishop_attacks(square_index(3, 3), all, own));

    std::cout << "Bishop on a1, no blockers:\n";
    print_bitboard(bishop_attacks(square_index(0, 0), 0ULL, 0ULL));
}

void test_queen_attacks()
{
    std::cout << "Queen on d4, no blockers:\n";
    print_bitboard(queen_attacks(square_index(3, 3), 0ULL, 0ULL));

    uint64_t blocker_d5 = 1ULL << square_index(4, 3);
    uint64_t blocker_b6 = 1ULL << square_index(5, 1);
    uint64_t own = blocker_d5;
    uint64_t all = blocker_d5 | blocker_b6;

    std::cout << "Queen on d4, friendly blocker d5, enemy blocker b6:\n";
    print_bitboard(queen_attacks(square_index(3, 3), all, own));

    std::cout << "Queen on a1, no blockers:\n";
    print_bitboard(queen_attacks(square_index(0, 0), 0ULL, 0ULL));
}