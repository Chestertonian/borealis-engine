#include <cstdint>
#include <array>
#include <sstream>
#include <string>
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

// castling rights bit masks
const uint8_t CASTLE_WK = 1;
const uint8_t CASTLE_WQ = 1 << 1;
const uint8_t CASTLE_BK = 1 << 2;
const uint8_t CASTLE_BQ = 1 << 3;

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

std::vector<Move> generate_knight_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    uint64_t attacks = knight_attacks(from_square);
    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (!((own_pieces >> target_square) & 1))
            {
                Move move{from_square, target_square, MoveType::Normal};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

std::vector<Move> generate_king_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    uint64_t attacks = king_attacks(from_square);
    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (!((own_pieces >> target_square) & 1))
            {
                Move move{from_square, target_square, MoveType::Normal};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

std::vector<Move> generate_pawn_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    int starting_rank = (color == Color::WHITE) ? 1 : 6;
    int promotion_rank = (color == Color::WHITE) ? 7 : 0;
    int direction = (color == Color::WHITE) ? 1 : -1;
    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t enemy_pieces = (color == Color::BLACK) ? white_occupied(board) : black_occupied(board);

    int push_square = from_square + (8 * direction);

    if (push_square >= 0 && push_square < 64 &&
        !((all_occupied(board) >> push_square) & 1))
    {
        if ((push_square / 8) == promotion_rank)
        {
            Move promote_knight{from_square, push_square, MoveType::Promotion, PieceType::KNIGHT};
            Move promote_bishop{from_square, push_square, MoveType::Promotion, PieceType::BISHOP};
            Move promote_rook{from_square, push_square, MoveType::Promotion, PieceType::ROOK};
            Move promote_queen{from_square, push_square, MoveType::Promotion, PieceType::QUEEN};
            moves.push_back(promote_knight);
            moves.push_back(promote_bishop);
            moves.push_back(promote_rook);
            moves.push_back(promote_queen);
        }

        else
        {
            Move singlepush{from_square, push_square, MoveType::Normal};
            moves.push_back(singlepush);
            if ((from_square / 8) == starting_rank)
            {
                int double_square = from_square + (16 * direction);
                if (!((all_occupied(board) >> double_square) & 1))
                {
                    Move double_push{from_square, double_square, MoveType::DoublePawnPush};
                    moves.push_back(double_push);
                }
            }
        }
    }

    uint64_t attacks = pawn_attacks(from_square, color);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (target_square == board.en_passant_square)
            {
                Move en_passant{from_square, target_square, MoveType::EnPassant};
                moves.push_back(en_passant);
            }
            if ((enemy_pieces >> target_square) & 1)
            {
                if ((target_square / 8) == promotion_rank)
                {
                    Move capture_promote_knight{from_square, target_square, MoveType::Promotion, PieceType::KNIGHT};
                    Move capture_promote_bishop{from_square, target_square, MoveType::Promotion, PieceType::BISHOP};
                    Move capture_promote_rook{from_square, target_square, MoveType::Promotion, PieceType::ROOK};
                    Move capture_promote_queen{from_square, target_square, MoveType::Promotion, PieceType::QUEEN};
                    moves.push_back(capture_promote_knight);
                    moves.push_back(capture_promote_bishop);
                    moves.push_back(capture_promote_rook);
                    moves.push_back(capture_promote_queen);
                }
                else
                {
                    Move capture{from_square, target_square, MoveType::Normal};
                    moves.push_back(capture);
                }
            }
        }
    }

    return moves;
}

std::vector<Move> generate_rook_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);
    uint64_t attacks = rook_attacks(from_square, occupied, own_pieces);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (!((own_pieces >> target_square) & 1))
            {
                Move move{from_square, target_square, MoveType::Normal};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

std::vector<Move> generate_bishop_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);
    uint64_t attacks = bishop_attacks(from_square, occupied, own_pieces);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (!((own_pieces >> target_square) & 1))
            {
                Move move{from_square, target_square, MoveType::Normal};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

std::vector<Move> generate_queen_moves(const BoardState &board, int from_square, Color color)
{
    std::vector<Move> moves;

    uint64_t own_pieces = (color == Color::WHITE) ? white_occupied(board) : black_occupied(board);
    uint64_t occupied = all_occupied(board);
    uint64_t attacks = queen_attacks(from_square, occupied, own_pieces);

    for (int target_square = 0; target_square < 64; ++target_square)
    {
        if ((attacks >> target_square) & 1)
        {
            if (!((own_pieces >> target_square) & 1))
            {
                Move move{from_square, target_square, MoveType::Normal};
                moves.push_back(move);
            }
        }
    }

    return moves;
}

std::vector<Move> generate_castle_moves(const BoardState &board, Color color)
{
    std::vector<Move> moves;

    if (board.castling_rights & CASTLE_WK)
    {
        bool path_empty = !((all_occupied(board) >> square_index(0, 5)) & 1)     // f1
                          && !((all_occupied(board) >> square_index(0, 6)) & 1); // g1

        bool not_through_check = !is_square_attacked(board, square_index(0, 4), Color::BLACK)     // e1
                                 && !is_square_attacked(board, square_index(0, 5), Color::BLACK)  // f1
                                 && !is_square_attacked(board, square_index(0, 6), Color::BLACK); // g1

        if (path_empty && not_through_check)
        {
            Move castle{square_index(0, 4), square_index(0, 6), MoveType::CastleKingside, PieceType::NONE};
            moves.push_back(castle);
        }
    }

    if (board.castling_rights & CASTLE_WQ)
    {
        bool path_empty = !((all_occupied(board) >> square_index(0, 3)) & 1)     // d1
                          && !((all_occupied(board) >> square_index(0, 2)) & 1)  // c1
                          && !((all_occupied(board) >> square_index(0, 1)) & 1); // b1

        bool not_through_check = !is_square_attacked(board, square_index(0, 4), Color::BLACK)     // e1
                                 && !is_square_attacked(board, square_index(0, 3), Color::BLACK)  // d1
                                 && !is_square_attacked(board, square_index(0, 2), Color::BLACK); // c1

        if (path_empty && not_through_check)
        {
            Move castle{square_index(0, 4), square_index(0, 2), MoveType::CastleQueenside, PieceType::NONE};
            moves.push_back(castle);
        }
    }

    if (board.castling_rights & CASTLE_BK)
    {
        bool path_empty = !((all_occupied(board) >> square_index(7, 5)) & 1)     // f8
                          && !((all_occupied(board) >> square_index(7, 6)) & 1); // g8

        bool not_through_check = !is_square_attacked(board, square_index(7, 4), Color::WHITE)     // e8
                                 && !is_square_attacked(board, square_index(7, 5), Color::WHITE)  // f8
                                 && !is_square_attacked(board, square_index(7, 6), Color::WHITE); // g8

        if (path_empty && not_through_check)
        {
            Move castle{square_index(7, 4), square_index(7, 6), MoveType::CastleKingside, PieceType::NONE};
            moves.push_back(castle);
        }
    }

    if (board.castling_rights & CASTLE_BQ)
    {
        bool path_empty = !((all_occupied(board) >> square_index(7, 3)) & 1)     // d8
                          && !((all_occupied(board) >> square_index(7, 2)) & 1)  // c8
                          && !((all_occupied(board) >> square_index(7, 1)) & 1); // b8

        bool not_through_check = !is_square_attacked(board, square_index(7, 4), Color::WHITE)     // e8
                                 && !is_square_attacked(board, square_index(7, 3), Color::WHITE)  // d8
                                 && !is_square_attacked(board, square_index(7, 2), Color::WHITE); // c8

        if (path_empty && not_through_check)
        {
            Move castle{square_index(7, 4), square_index(7, 2), MoveType::CastleQueenside, PieceType::NONE};
            moves.push_back(castle);
        }
    }

    return moves;
}

std::vector<Move> generate_all_moves(const BoardState &board, Color color)
{
    std::vector<Move> moves;

    // KNIGHT
    uint64_t knights = board.bitboards[piece_index(color, PieceType::KNIGHT)];
    for (int square = 0; square < 64; ++square)
    {
        if ((knights >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_knight_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // KING
    uint64_t kings = board.bitboards[piece_index(color, PieceType::KING)];
    for (int square = 0; square < 64; ++square)
    {
        if ((kings >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_king_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // ROOK
    uint64_t rooks = board.bitboards[piece_index(color, PieceType::ROOK)];
    for (int square = 0; square < 64; ++square)
    {
        if ((rooks >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_rook_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // BISHOP
    uint64_t bishops = board.bitboards[piece_index(color, PieceType::BISHOP)];
    for (int square = 0; square < 64; ++square)
    {
        if ((bishops >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_bishop_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // QUEEN
    uint64_t queens = board.bitboards[piece_index(color, PieceType::QUEEN)];
    for (int square = 0; square < 64; ++square)
    {
        if ((queens >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_queen_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // PAWN
    uint64_t pawns = board.bitboards[piece_index(color, PieceType::PAWN)];
    for (int square = 0; square < 64; ++square)
    {
        if ((pawns >> square) & 1)
        {
            std::vector<Move> piece_moves = generate_pawn_moves(board, square, color);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
    }

    // CASTLING
    std::vector<Move> castle_moves = generate_castle_moves(board, color);
    moves.insert(moves.end(), castle_moves.begin(), castle_moves.end());

    return moves;
}

bool is_square_attacked(const BoardState &board, int square, Color attacking_color)

{

    // KNIGHT
    uint64_t enemy_knights = board.bitboards[piece_index(attacking_color, PieceType::KNIGHT)];
    if (knight_attacks(square) & enemy_knights)
        return true;

    // KING
    uint64_t enemy_king = board.bitboards[piece_index(attacking_color, PieceType::KING)];
    if (king_attacks(square) & enemy_king)
        return true;

    uint64_t occ = all_occupied(board);
    uint64_t attacker_occupied = (attacking_color == Color::WHITE)
                                     ? white_occupied(board)
                                     : black_occupied(board);

    // ROOK/QUEEN
    uint64_t enemy_rooks_queens = board.bitboards[piece_index(attacking_color, PieceType::ROOK)] | board.bitboards[piece_index(attacking_color, PieceType::QUEEN)];
    if (rook_attacks(square, occ, 0ULL) & enemy_rooks_queens)
        return true;

    // BISHOP/QUEEN
    uint64_t enemy_bishops_queens = board.bitboards[piece_index(attacking_color, PieceType::BISHOP)] | board.bitboards[piece_index(attacking_color, PieceType::QUEEN)];
    if (bishop_attacks(square, occ, 0ULL) & enemy_bishops_queens)
        return true;

    // PAWN
    Color opposite = (attacking_color == Color::WHITE) ? Color::BLACK : Color::WHITE;
    uint64_t enemy_pawns = board.bitboards[piece_index(attacking_color, PieceType::PAWN)];
    if (pawn_attacks(square, opposite) & enemy_pawns)
        return true;

    return false;
}

int algebraic_to_square(const std::string &algebraic)
{
    int file = algebraic[0] - 'a';
    int rank = algebraic[1] - '1';
    return square_index(rank, file);
}

PieceType char_to_piece_type(char c)
{
    switch (std::tolower(c))
    {
    case 'p':
        return PieceType::PAWN;
    case 'n':
        return PieceType::KNIGHT;
    case 'b':
        return PieceType::BISHOP;
    case 'r':
        return PieceType::ROOK;
    case 'q':
        return PieceType::QUEEN;
    case 'k':
        return PieceType::KING;
    default:
        return PieceType::NONE;
    }
}

BoardState load_fen(const std::string &fen)
{

    BoardState board;
    board.bitboards.fill(0ULL);

    std::istringstream iss(fen);
    std::string placement, side_to_move_str, castling_str, en_passant_str;
    int halfmove, fullmove;
    iss >> placement >> side_to_move_str >> castling_str >> en_passant_str >> halfmove >> fullmove;

    // Field 1: piece placement
    int rank = 7, file = 0;
    for (char c : placement)
    {
        if (c == '/')
        {
            rank -= 1;
            file = 0;
        }
        else if (std::isdigit(c))
        {
            file += (c - '0');
        }
        else
        {
            Color color = std::isupper(c) ? Color::WHITE : Color::BLACK;
            PieceType type = char_to_piece_type(c);
            int square = square_index(rank, file);
            board.bitboards[piece_index(color, type)] |= (1ULL << square);
            file += 1;
        }
    }

    // Field 2: side to move
    board.side_to_move = (side_to_move_str == "w") ? Color::WHITE : Color::BLACK;

    // Field 3: castling rights
    board.castling_rights = 0;
    if (castling_str != "-")
    {
        for (char c : castling_str)
        {
            if (c == 'K')
                board.castling_rights |= CASTLE_WK;
            if (c == 'Q')
                board.castling_rights |= CASTLE_WQ;
            if (c == 'k')
                board.castling_rights |= CASTLE_BK;
            if (c == 'q')
                board.castling_rights |= CASTLE_BQ;
        }
    }

    // Field 4: en passant square
    board.en_passant_square = (en_passant_str == "-") ? -1 : algebraic_to_square(en_passant_str);

    // Fields 5-6: clocks
    board.halfmove_clock = halfmove;
    board.fullmove_number = fullmove;

    return board;
}

PieceType piece_at(const BoardState &board, int square, Color color)
{
    for (int t = 0; t < 6; ++t)
    {
        PieceType type = static_cast<PieceType>(t);
        if ((board.bitboards[piece_index(color, type)] >> square) & 1)
        {
            return type;
        }
    }
    return PieceType::NONE;
}

BoardState apply_move(const BoardState &board, const Move &move)
{
    BoardState new_board = board;

    Color moving_color = board.side_to_move;
    Color enemy_color = (moving_color == Color::WHITE) ? Color::BLACK : Color::WHITE;

    PieceType moving_piece = piece_at(board, move.from, moving_color);
    PieceType captured_piece = piece_at(board, move.to, enemy_color);

    if (move.type == MoveType::Normal)
    {

        // clear from-square, set to-square for the moving piece
        new_board.bitboards[piece_index(moving_color, moving_piece)] &= ~(1ULL << move.from);
        new_board.bitboards[piece_index(moving_color, moving_piece)] |= (1ULL << move.to);

        if (captured_piece != PieceType::NONE)
        {
            new_board.bitboards[piece_index(enemy_color, captured_piece)] &= ~(1ULL << move.to);
        }
        new_board.en_passant_square = -1;
    }

    if (move.type == MoveType::DoublePawnPush)
    {
        int direction = (moving_color == Color::WHITE) ? 1 : -1;
        int intermediate_square = move.from + (8 * direction);

        // clear from-square, set to-square for the moving piece
        new_board.bitboards[piece_index(moving_color, moving_piece)] &= ~(1ULL << move.from);
        new_board.bitboards[piece_index(moving_color, moving_piece)] |= (1ULL << move.to);

        if (captured_piece != PieceType::NONE)
        {
            new_board.bitboards[piece_index(enemy_color, captured_piece)] &= ~(1ULL << move.to);
        }
        new_board.en_passant_square = intermediate_square;
    }

    if (move.type == MoveType::Promotion)
    {
        // clear the pawn from its origin square
        new_board.bitboards[piece_index(moving_color, PieceType::PAWN)] &= ~(1ULL << move.from);

        // set the PROMOTED piece at the destination — not the pawn
        new_board.bitboards[piece_index(moving_color, move.promotion_piece)] |= (1ULL << move.to);

        // handle a possible capture on the destination square, same as Normal
        PieceType captured_piece = piece_at(board, move.to, enemy_color);
        if (captured_piece != PieceType::NONE)
        {
            new_board.bitboards[piece_index(enemy_color, captured_piece)] &= ~(1ULL << move.to);
        }
        new_board.en_passant_square = -1;
    }

    if (move.type == MoveType::CastleKingside)
    {
        // king: e -> g (file 4 -> file 6, same rank)
        new_board.bitboards[piece_index(moving_color, PieceType::KING)] &= ~(1ULL << move.from);
        new_board.bitboards[piece_index(moving_color, PieceType::KING)] |= (1ULL << move.to);

        // rook: h -> f (file 7 -> file 5, same rank)
        int rook_rank = (moving_color == Color::WHITE) ? 0 : 7;
        int rook_from = square_index(rook_rank, 7);
        int rook_to = square_index(rook_rank, 5);
        new_board.bitboards[piece_index(moving_color, PieceType::ROOK)] &= ~(1ULL << rook_from);
        new_board.bitboards[piece_index(moving_color, PieceType::ROOK)] |= (1ULL << rook_to);
        new_board.en_passant_square = -1;
        if (moving_color == Color::WHITE)
            new_board.castling_rights &= ~(CASTLE_WK | CASTLE_WQ);
        else
            new_board.castling_rights &= ~(CASTLE_BK | CASTLE_BQ);
    }

    if (move.type == MoveType::CastleQueenside)
    {
        // king: e -> c (file 4 -> file 2, same rank)
        new_board.bitboards[piece_index(moving_color, PieceType::KING)] &= ~(1ULL << move.from);
        new_board.bitboards[piece_index(moving_color, PieceType::KING)] |= (1ULL << move.to);

        // rook: a -> d (file 0 -> file 3, same rank)
        int rook_rank = (moving_color == Color::WHITE) ? 0 : 7;
        int rook_from = square_index(rook_rank, 0);
        int rook_to = square_index(rook_rank, 3);
        new_board.bitboards[piece_index(moving_color, PieceType::ROOK)] &= ~(1ULL << rook_from);
        new_board.bitboards[piece_index(moving_color, PieceType::ROOK)] |= (1ULL << rook_to);

        new_board.en_passant_square = -1;
        if (moving_color == Color::WHITE)
            new_board.castling_rights &= ~(CASTLE_WK | CASTLE_WQ);
        else
            new_board.castling_rights &= ~(CASTLE_BK | CASTLE_BQ);
    }

    if (move.type == MoveType::EnPassant)
    {
        PieceType moving_piece = PieceType::PAWN; // always a pawn, same reasoning as promotion

        // move the capturing pawn normally
        new_board.bitboards[piece_index(moving_color, PieceType::PAWN)] &= ~(1ULL << move.from);
        new_board.bitboards[piece_index(moving_color, PieceType::PAWN)] |= (1ULL << move.to);

        // the captured pawn is one rank behind `to`, NOT on `to` itself
        int direction = (moving_color == Color::WHITE) ? 1 : -1;
        int captured_square = move.to - (8 * direction);

        new_board.bitboards[piece_index(enemy_color, PieceType::PAWN)] &= ~(1ULL << captured_square);
    }

    // metadata updates — apply regardless of move type, come back to these
    if (moving_color == Color::BLACK)
    {
        new_board.fullmove_number = board.fullmove_number + 1;
    }
    new_board.side_to_move = enemy_color;

    // 50 move rule enforcement.
    if (moving_piece == PieceType::PAWN || captured_piece != PieceType::NONE)
    {
        new_board.halfmove_clock = 0;
    }
    else
    {
        new_board.halfmove_clock = board.halfmove_clock + 1;
    }

    return new_board;
}
