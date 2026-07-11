#ifndef GAME_H
#define GAME_H

#include "bitboards.h"
#include "MoveStruct.h"
#include <vector>

// Runs the full human-vs-bot game loop until the game ends or the human quits.
void play_game();

// Prompts for and returns which side the human wants to play.
Color choose_human_side();

// Outcome of a single attempt to read a move from the human.
enum class InputResult { Move, Quit, Invalid };

// Reads a move string from stdin, matches it against the legal move list.
// On InputResult::Move, out_move is set to the matched legal move.
InputResult get_human_move(const BoardState& state, const std::vector<Move>& legal_moves, Move& out_move);

// Picks a move for the bot's turn. Random for now; swappable for search later.
Move get_bot_move(const std::vector<Move>& legal_moves);

// Prints a human-readable message for final GameStatus.
void report_game_end(GameStatus status);

std::string game_status_to_string(GameStatus status)
PieceType notation_to_piece_type(char piece)

enum class GameStatus { ONGOING, CHECKMATE, STALEMATE, FIFTY_MOVE_DRAW, INSUFFICIENT_MATERIAL, REPETITION };

bool is_insufficient_material(const BoardState& board);

#endif
