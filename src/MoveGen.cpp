#include "MoveGen.h" 
#include <cctype>

std::vector<Move> generate_knight_moves(const GameState& state, int from_square) {
    // from_square = where the knight is now.

    // moves of the knight
    int offsets[8][2] = {
    {-2, -1}, {-2, 1},
    {-1, -2}, {-1, 2},
    { 1, -2}, { 1, 2},
    { 2, -1}, { 2, 1}
    };

    // define row/column 
    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;
    for (int i = 0; i < 8; ++i) {
        int new_row = row + offsets[i][0];
        int new_col = column + offsets[i][1];
        // boundary check
        if (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7) {
            continue;
        }

        int to_square = new_row * 8 + new_col;
        char target = state.board[to_square];

        // is own piece?
        if (is_friendly(target, state.side_to_move)) {
            continue;
        }    

        // is own piece?
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});
}

// helpers

bool is_white_piece(char piece) {
    return isupper(piece);
}

bool is_black_piece(char piece)
{
    return islower(piece);
}

bool is_friendly(char piece, Color side) {
    return (side == Color::White) ? is_white_piece(piece) : is_black_piece(piece);
}

bool is_enemy(char piece, Color side) {
    return (side == Color::White) ? is_black_piece(piece) : is_white_piece(piece);
}

bool is_empty(char piece)
{
    return piece = '.';
}