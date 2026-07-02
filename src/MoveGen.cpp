#include "MoveGen.h"
#include <cctype>
#include "GameState.h"

std::vector<Move> generate_king_moves(const GameState &state, int from_square)
{
    // from_square = where the king is now.

    // moves of the king
    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    // define row/column
    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;
    for (int i = 0; i < 8; ++i)
    {
        int new_row = row + offsets[i][0];
        int new_col = column + offsets[i][1];
        // boundary check
        if (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7)
        {
            continue;
        }

        int to_square = new_row * 8 + new_col;
        char target = state.board[to_square];

        // is own piece?
        if (is_friendly(target, state.side_to_move))
        {
            continue;
        }

        // construct new move
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});
    }

    return moves;
}

std::vector<Move> generate_queen_moves(const GameState &state, int from_square)
{
    // 8 directions
    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 8; ++i)
    {
        int current_row = row;
        int current_col = column;

        while (true)
        {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7)
            {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move))
            {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.')
            {
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

std::vector<Move> generate_rook_moves(const GameState &state, int from_square)
{
    // 4 directions: up, down, left, right
    int offsets[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 4; ++i)
    {
        int current_row = row;
        int current_col = column;

        while (true)
        {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7)
            {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move))
            {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.')
            {
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

std::vector<Move> generate_bishop_moves(const GameState &state, int from_square)
{
    // 4 directions
    int offsets[4][2] = {
        {-1, 1}, {1, -1}, {1, 1}, {-1, -1}};

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 4; ++i)
    {
        int current_row = row;
        int current_col = column;

        while (true)
        {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7)
            {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move))
            {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.')
            {
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

std::vector<Move> generate_knight_moves(const GameState &state, int from_square)
{
    // from_square = where the knight is now.

    // moves of the knight
    int offsets[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    // define row/column
    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;
    for (int i = 0; i < 8; ++i)
    {
        int new_row = row + offsets[i][0];
        int new_col = column + offsets[i][1];
        // boundary check
        if (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7)
        {
            continue;
        }

        int to_square = new_row * 8 + new_col;
        char target = state.board[to_square];

        // is own piece?
        if (is_friendly(target, state.side_to_move))
        {
            continue;
        }

        // construct move
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});
    }

    return moves;
}

std::vector<Move> generate_pawn_moves(const GameState &state, int from_square)
{
    // from_square = where the pawn is now.

    // define row/column
    int row = from_square / 8;
    int column = from_square % 8;

    int direction;
    int starting_row;
    int final_row;
    int en_passant_row;

    if (state.side_to_move == Color::White)
    {
        direction = -1;
        starting_row = 6;
        final_row = 1;
        en_passant_row = 3;
    }
    else
    {
        direction = 1;
        starting_row = 1;
        final_row = 6;
        en_passant_row = 4;
    }

    std::vector<Move> moves;
    for (int i = 0; i < 1; ++i)
    {
        int new_row = row + direction;
        // boundary check
        if (new_row < 0 || new_row > 7)
        {
            continue;
        }

        int to_square = new_row * 8 + column;
        char target = state.board[to_square];

        // is own piece?
        if (is_friendly(target, state.side_to_move))
        {
            continue;
        }

        if (is_enemy(target, state.side_to_move))
        {
            continue;
        }

        // construct new move
        if (row == final_row)
        {
            add_pawn_move(moves, from_square, to_square, true);
        }

        if (row != final_row)
        {
            add_pawn_move(moves, from_square, to_square, false);
        }
    }

    // initial two-space push

    for (int i = 0; i < 1; ++i)
    {
        if (row == starting_row)
        {
            int new_row = row + (direction * 2);

            if (new_row < 0 || new_row > 7)
            {
                continue;
            }

            int to_square = new_row * 8 + column;
            int middle_square = (row + direction) * 8 + column;
            char target = state.board[to_square];

            if (is_empty(state.board[middle_square]) && is_empty(target))
            {
                moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});
            }
        }
    }

    // Captures (diagonal, obviously)
    int new_row = row + direction;
    int new_column = column - 1;

    if (new_row >= 0 && new_row <= 7 && new_column >= 0 && new_column <= 7)
    {
        int to_square = new_row * 8 + new_column;
        char target = state.board[to_square];

        if (is_enemy(target, state.side_to_move))
        {
            if (row == final_row)
            {
                add_pawn_move(moves, from_square, to_square, true);
            }

            if (row != final_row)
            {
                add_pawn_move(moves, from_square, to_square, false);
            }
        }
    }

    new_column = column + 1;

    if (new_row >= 0 && new_row <= 7 && new_column >= 0 && new_column <= 7)
    {
        int to_square = new_row * 8 + new_column;
        char target = state.board[to_square];

        if (is_enemy(target, state.side_to_move))
        {
            if (row == final_row)
            {
                add_pawn_move(moves, from_square, to_square, true);
            }

            if (row != final_row)
            {
                add_pawn_move(moves, from_square, to_square, false);
            }
        }
    }

    if (state.en_passant_square != -1)
    {
        if (row == en_passant_row)
        {
            int new_row = row + direction;

            // left diagonal
            int new_column = column - 1;
            if (new_column >= 0)
            {
                int to_square = new_row * 8 + new_column;
                if (to_square == state.en_passant_square)
                {
                    moves.push_back(Move{from_square, to_square, MoveType::EnPassant, PieceType::None});
                }
            }

            // right diagonal
            new_column = column + 1;
            if (new_column <= 7)
            {
                int to_square = new_row * 8 + new_column;
                if (to_square == state.en_passant_square)
                {
                    moves.push_back(Move{from_square, to_square, MoveType::EnPassant, PieceType::None});
                }
            }
        }
    }

    return moves;
}

std::vector<Move> generate_castling_moves(const GameState &state)
{
    std::vector<Move> moves;

    if (state.side_to_move == Color::White)
    {
        // White kingside castling
        if (state.white_kingside_castle)
        {
            if (is_empty(state.board[61]) && is_empty(state.board[62]))
            {
                if (!(is_square_attacked(state, 60, Color::Black) || is_square_attacked(state, 61, Color::Black) || is_square_attacked(state, 62, Color::Black)))
                {
                    moves.push_back(Move{60, 62, MoveType::CastleKingside, PieceType::None});
                }
            }
        }

        // White queenside castling
        if (state.white_queenside_castle)
        {
            if (is_empty(state.board[57]) && is_empty(state.board[58]) && is_empty(state.board[59]))
            {
                if (!(is_square_attacked(state, 60, Color::Black) || is_square_attacked(state, 59, Color::Black) || is_square_attacked(state, 58, Color::Black)))
                {
                    moves.push_back(Move{60, 58, MoveType::CastleQueenside, PieceType::None});
                }
            }
        }
    }

    if (state.side_to_move == Color::Black)
    {
    // Black kingside castling
    if (state.black_kingside_castle)
    {
        if (is_empty(state.board[5]) && is_empty(state.board[6]))
        {
            if (!(is_square_attacked(state, 4, Color::White) || is_square_attacked(state, 5, Color::White) || is_square_attacked(state, 6, Color::White)))
            {
                moves.push_back(Move{4, 6, MoveType::CastleKingside, PieceType::None});
            }
        }
    }

    // Black queenside castling
    if (state.black_queenside_castle)
    {
        if (is_empty(state.board[3]) && is_empty(state.board[2]) && is_empty(state.board[1]))
        {
            if (!(is_square_attacked(state, 1, Color::White) || is_square_attacked(state, 2, Color::White) || is_square_attacked(state, 3, Color::White) || is_square_attacked(state, 4, Color::White)))
            {
                moves.push_back(Move{4, 2, MoveType::CastleQueenside, PieceType::None});
            }
        }
    }
}

    return moves;
}

// all pseudo-legal moves --> doesn't filter for check, for example
std::vector<Move> generate_pseudolegal_moves(const GameState &state)
{
    std::vector<Move> moves;

    for (int square = 0; square < 64; ++square)
    {
        char piece = state.board[square];

        if (is_empty(piece))
        {
            continue;
        }

        // skip opponent's pieces
        if (state.side_to_move == Color::White && !is_white_piece(piece))
        {
            continue;
        }
        if (state.side_to_move == Color::Black && !is_black_piece(piece))
        {
            continue;
        }

        std::vector<Move> piece_moves;
        std::vector<Move> castle_moves;

        switch (std::toupper(piece))
        {
        case 'P':
            piece_moves = generate_pawn_moves(state, square);
            break;
        case 'N':
            piece_moves = generate_knight_moves(state, square);
            break;
        case 'B':
            piece_moves = generate_bishop_moves(state, square);
            break;
        case 'R':
            piece_moves = generate_rook_moves(state, square);
            break;
        case 'Q':
            piece_moves = generate_queen_moves(state, square);
            break;
        case 'K':
            piece_moves = generate_king_moves(state, square);
            moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
            piece_moves = generate_castling_moves(state);
            break;
        }

        moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
    }

    return moves;
}

// all legal moves
std::vector<Move> generate_all_moves(const GameState &state)
{
    std::vector<Move> pseudolegals = generate_pseudolegal_moves(state);
    std::vector<Move> legal_moves;

    for (const Move &move : pseudolegals)
    {
        GameState test_state = apply_move(state, move);
        bool unsafe = is_square_attacked(test_state, find_king_square(test_state, state.side_to_move), test_state.side_to_move);
        if (!unsafe)
        {
            legal_moves.push_back(move);
        }
    }

    return legal_moves;
}

// helpers

bool is_white_piece(char piece)
{
    return isupper(piece);
}

bool is_black_piece(char piece)
{
    return islower(piece);
}

bool is_friendly(char piece, Color side)
{
    return (side == Color::White) ? is_white_piece(piece) : is_black_piece(piece);
}

bool is_enemy(char piece, Color side)
{
    return (side == Color::White) ? is_black_piece(piece) : is_white_piece(piece);
}

bool is_empty(char piece)
{
    return piece == '.';
}

bool is_square_attacked(const GameState &state, int square, Color by_color)
{
    int row = square / 8;
    int column = square % 8;

    // --- knight attacks ---
    int knight_offsets[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int r = row + knight_offsets[i][0];
        int c = column + knight_offsets[i][1];

        if (r < 0 || r > 7 || c < 0 || c > 7)
        {
            continue;
        }

        char target = state.board[r * 8 + c];
        if (std::toupper(target) == 'N')
        {
            if ((by_color == Color::White && is_white_piece(target)) ||
                (by_color == Color::Black && is_black_piece(target)))
            {
                return true;
            }
        }
    }

    // --- king attacks (one square in every direction) ---
    int king_offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int r = row + king_offsets[i][0];
        int c = column + king_offsets[i][1];

        if (r < 0 || r > 7 || c < 0 || c > 7)
        {
            continue;
        }

        char target = state.board[r * 8 + c];
        if (std::toupper(target) == 'K')
        {
            if ((by_color == Color::White && is_white_piece(target)) ||
                (by_color == Color::Black && is_black_piece(target)))
            {
                return true;
            }
        }
    }

    // --- sliding pieces: rook/queen (orthogonal), bishop/queen (diagonal) ---
    int orthogonal_offsets[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int diagonal_offsets[4][2] = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    // orthogonal rays -> look for rook or queen
    for (int i = 0; i < 4; ++i)
    {
        int r = row;
        int c = column;

        while (true)
        {
            r += orthogonal_offsets[i][0];
            c += orthogonal_offsets[i][1];

            if (r < 0 || r > 7 || c < 0 || c > 7)
            {
                break;
            }

            char target = state.board[r * 8 + c];

            if (is_empty(target))
            {
                continue; // keep walking
            }

            // hit a piece - check if it's an attacking rook/queen, then stop regardless
            char upper = std::toupper(target);
            if ((upper == 'R' || upper == 'Q') &&
                ((by_color == Color::White && is_white_piece(target)) ||
                 (by_color == Color::Black && is_black_piece(target))))
            {
                return true;
            }
            break; // blocked, stop walking this ray either way
        }
    }

    // diagonal rays -> look for bishop or queen
    for (int i = 0; i < 4; ++i)
    {
        int r = row;
        int c = column;

        while (true)
        {
            r += diagonal_offsets[i][0];
            c += diagonal_offsets[i][1];

            if (r < 0 || r > 7 || c < 0 || c > 7)
            {
                break;
            }

            char target = state.board[r * 8 + c];

            if (is_empty(target))
            {
                continue;
            }

            char upper = std::toupper(target);
            if ((upper == 'B' || upper == 'Q') &&
                ((by_color == Color::White && is_white_piece(target)) ||
                 (by_color == Color::Black && is_black_piece(target))))
            {
                return true;
            }
            break;
        }
    }

    // --- pawn attacks ---
    // an enemy pawn attacks'square' if it sits one row "behind" square
    // (from the attacker's own forward direction) on either diagonal
    int pawn_row = (by_color == Color::White) ? row + 1 : row - 1;

    if (pawn_row >= 0 && pawn_row <= 7)
    {
        int pawn_cols[2] = {column - 1, column + 1};
        for (int i = 0; i < 2; ++i)
        {
            int c = pawn_cols[i];
            if (c < 0 || c > 7)
            {
                continue;
            }
            char target = state.board[pawn_row * 8 + c];
            if (std::toupper(target) == 'P')
            {
                if ((by_color == Color::White && is_white_piece(target)) ||
                    (by_color == Color::Black && is_black_piece(target)))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int find_king_square(const GameState &state, Color king_color)
{
    int king_location = -1;
    char king_char = (king_color == Color::White) ? 'K' : 'k';

    for (int i = 0; i < 64; ++i)
    {
        if (state.board[i] == king_char)
        {
            king_location = i;
            break;
        }
    }

    return king_location;
}

void add_pawn_move(std::vector<Move> &moves, int from, int to, bool is_promotion)
{
    if (is_promotion)
    {
        moves.push_back(Move{from, to, MoveType::Promotion, PieceType::Queen});
        moves.push_back(Move{from, to, MoveType::Promotion, PieceType::Rook});
        moves.push_back(Move{from, to, MoveType::Promotion, PieceType::Bishop});
        moves.push_back(Move{from, to, MoveType::Promotion, PieceType::Knight});
    }
    else
    {
        moves.push_back(Move{from, to, MoveType::Normal, PieceType::None});
    }
}

long long perft(const GameState& state, int depth) {
    if (depth == 0) {
        return 1;
    }

    std::vector<Move> legal_moves = generate_all_moves(state);
    long long nodes = 0;

    for (const Move& move : legal_moves) {
        GameState next_state = apply_move(state, move);
        nodes += perft(next_state, depth - 1);
    }

    return nodes;
}