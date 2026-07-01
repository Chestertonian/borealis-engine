#include "MoveGen.h" 
#include <cctype>
#include <iostream>

std::vector<Move> generate_queen_moves(const GameState& state, int from_square) {
    // 8 directions
    int offsets[8][2] = {
    {-1, -1}, {0, -1},
    {1, -1}, {-1, 0},
    { 1, 0}, { -1, 1},
    { 0, 1}, { 1, 1}
    };

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 8; ++i) {
        int current_row = row;
        int current_col = column;

        while (true) {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7) {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move)) {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.') {  
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

std::vector<Move> generate_rook_moves(const GameState& state, int from_square) {
    // 4 directions: up, down, left, right
    int offsets[4][2] = {
        {-1, 0}, {1, 0},
        {0, -1}, {0, 1}
    };

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 4; ++i) {
        int current_row = row;
        int current_col = column;

        while (true) {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7) {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move)) {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.') {  
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

std::vector<Move> generate_bishop_moves(const GameState& state, int from_square) {
    // 4 directions
    int offsets[4][2] = {
        {-1, 1}, {1, -1},
        {1, 1}, {-1, -1}
    };

    int row = from_square / 8;
    int column = from_square % 8;

    std::vector<Move> moves;

    for (int i = 0; i < 4; ++i) {
        int current_row = row;
        int current_col = column;

        while (true) {
            current_row += offsets[i][0];
            current_col += offsets[i][1];

            // off the board -> stop walking this direction
            if (current_row < 0 || current_row > 7 || current_col < 0 || current_col > 7) {
                break;
            }

            int to_square = current_row * 8 + current_col;
            char target = state.board[to_square];

            // own piece -> stop walking, not a valid move
            if (is_friendly(target, state.side_to_move)) {
                break;
            }

            // empty or enemy piece -> valid move
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None});

            // enemy piece -> can capture it, but can't jump past it
            if (target != '.') {  
                break;
            }

            // otherwise: empty square, keep walking in this direction
        }
    }

    return moves;
}

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

        // construct move
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None}); }

    return moves;
}

// TODO: add check
std::vector<Move> generate_king_moves(const GameState& state, int from_square) {
    // from_square = where the king is now.

    // moves of the king
    int offsets[8][2] = {
    {-1, -1}, {0, -1},
    {1, -1}, {-1, 0},
    { 1, 0}, { -1, 1},
    { 0, 1}, { 1, 1}
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

        // construct new move
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None}); }
        
    return moves;
}

std::vector<Move> generate_pawn_moves(const GameState& state, int from_square) {
    // from_square = where the pawn is now.


    // define row/column 
    int row = from_square / 8;
    int column = from_square % 8;

    int direction;
    int starting_row;

    if (state.side_to_move == Color::White) {
        direction = -1;
        starting_row = 6;
    } else {
        direction = 1;
        starting_row = 1;
    }


    std::vector<Move> moves;
    for (int i = 0; i < 1; ++i) {
        int new_row = row + direction;
        // boundary check
        if (new_row < 0 || new_row > 7) {
            continue;
        }

        int to_square = new_row * 8 + column;
        char target = state.board[to_square];

        // is own piece?
        if (is_friendly(target, state.side_to_move)) {
            continue;
        }    

        if (is_enemy(target, state.side_to_move)) {
            continue;
        }   

        // construct new move
        moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None}); }

    // initial two-space push

    for (int i = 0; i < 1; ++i) {
        if (row == starting_row) {
        int new_row = row + (direction*2);

        if (new_row < 0 || new_row > 7) {
            continue;
        }

        int to_square = new_row * 8 + column;
        int middle_square = (row + direction) *8 + column;
        char target = state.board[to_square];

        if (is_empty(state.board[middle_square]) && is_empty(target)) {
            std::cout << is_empty(state.board[middle_square]);
            moves.push_back(Move{from_square, to_square, MoveType::Normal, PieceType::None}); 
            moves.push_back(Move{from_square, middle_square, MoveType::Normal, PieceType::None}); }
        }
    }
        
    return moves;

    
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