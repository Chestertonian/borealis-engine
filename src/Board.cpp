#include "Board.h"
#include <iostream>
#include <string>

void setup_starting_position(Board &board)
{
    // Black's back rank (row 0, squares 0-7)
    board[0] = 'r';
    board[1] = 'n';
    board[2] = 'b';
    board[3] = 'q';
    board[4] = 'k';
    board[5] = 'b';
    board[6] = 'n';
    board[7] = 'r';

    // Black pawns (row 1, squares 8-15)
    for (int i = 8; i <= 15; ++i)
    {
        board[i] = 'p';
    }

    // Empty middle rows (squares 16-47)
    for (int i = 16; i <= 47; ++i)
    {
        board[i] = '.';
    }

    // White pawns (row 6, squares 48-55)
    for (int i = 48; i <= 55; ++i)
    {
        board[i] = 'P';
    }

    // White's back rank (row 7, squares 56-63)
    board[56] = 'R';
    board[57] = 'N';
    board[58] = 'B';
    board[59] = 'Q';
    board[60] = 'K';
    board[61] = 'B';
    board[62] = 'N';
    board[63] = 'R';
}

void print_board(const Board &board)
{
    for (int row = 0; row < 8; ++row)
    {
        std::cout << 8 - row << ' ';
        for (int col = 0; col < 8; ++col)
        {
            int square = row * 8 + col;
            std::cout << board[square] << ' ';
        }
        std::cout << '\n';
    }
    std::cout <<"  a b c d e f g h" << '\n';
}

std::string square_to_coordinate(int square)
{
    int row = square / 8;
    int col = square % 8;
    int rank = 8 - row;
    char file = 'a' + col;
    return std::string(1, file) + std::to_string(rank);
}

int coordinate_to_square(const std::string &coord)
{
    char file = coord[0];
    char rank_char = coord[1];
    int col = file - 'a';
    int rank = rank_char - '0';
    int row = 8 - rank;
    return row * 8 + col;
}

void fen_to_board(const std::string& fen, Board& board) {
    // Turns Forsyth-Edwards notation into chess position.
    std::string placement = fen.substr(0, fen.find(' '));

    int square = 0;
    for (char c : placement) {
        if (c == '/') {
            continue;
        } else if (std::isdigit(c)) {
            int empty_count = c - '0';
            for (int i = 0; i < empty_count; ++i) {
                board[square] = '.';
                ++square;
            }
        } else {
            board[square] = c;
            ++square;
        }
    }
}