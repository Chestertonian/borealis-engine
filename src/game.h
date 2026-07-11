#include "bitboards.h"

enum class GameStatus { ONGOING, CHECKMATE, STALEMATE, FIFTY_MOVE_DRAW, INSUFFICIENT_MATERIAL, REPETITION };

enum class GameResult { ONGOING, WHITE_WINS, BLACK_WINS, STALEMATE, INSUFFICIENT_MATERIAL, FIFTY_MOVE };

Move pick_random_move(const std::vector<Move>& moves);

Move get_human_move(const BoardState& board, const std::vector<Move>& legal_moves);

bool is_insufficient_material(const BoardState& board);
GameResult check_game_end(const BoardState& board);

void run_game();