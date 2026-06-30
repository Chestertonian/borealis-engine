#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>

using Board = std::array<char, 64>;

void setup_starting_position(Board& board);
void print_board(const Board& board);

std::string square_to_coordinate(int square);
int coordinate_to_square(const std::string& coord);

void fen_to_board(const std::string& fen, Board& board);

#endif