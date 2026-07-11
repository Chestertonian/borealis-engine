#include "bitboards.h"
#include "game.h"

Move pick_random_move(const std::vector<Move> &moves)
{
    int index = rand() % moves.size();
    return moves[index];
}

bool is_insufficient_material(const BoardState &board)
{
    // Any pawn, rook, or queen (either color) means there's still enough
    // material to force checkmate in principle — bail out immediately.
    uint64_t major_and_pawn_pieces =
        board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)] | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)] | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)] | board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)] | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)] | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)];

    if (major_and_pawn_pieces != 0)
        return false;

    int white_knights = count_bits(board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)]);
    int white_bishops = count_bits(board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)]);
    int black_knights = count_bits(board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)]);
    int black_bishops = count_bits(board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)]);

    int total_minors = white_knights + white_bishops + black_knights + black_bishops;

    if (total_minors == 0)
        return true; // K vs K
    if (total_minors == 1)
        return true; // K+N vs K, or K+B vs K
    if (total_minors == 2 && white_bishops == 1 && black_bishops == 1)
        return true; // K+B vs K+B

    return false; // anything else treated as sufficient
}

GameResult check_game_end(const BoardState &board)
{
    std::vector<Move> moves = generate_legal_moves(board, board.side_to_move);

    if (moves.empty())
    {
        int king_square = find_king_square(board, board.side_to_move);
        Color enemy = (board.side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (is_square_attacked(board, king_square, enemy))
        {
            return (board.side_to_move == Color::WHITE) ? GameResult::BLACK_WINS : GameResult::WHITE_WINS;
        }
        return GameResult::STALEMATE;
    }

    if (is_insufficient_material(board))
        return GameResult::INSUFFICIENT_MATERIAL;
    if (board.halfmove_clock >= 100)
        return GameResult::FIFTY_MOVE;

    return GameResult::ONGOING;
}

Move get_human_move(const BoardState &board, const std::vector<Move> &legal_moves)
{
    while (true)
    {
        std::cout << "Enter move (e.g. e2e4): ";
        std::string input;
        std::cin >> input;

        if (input.length() < 4)
        {
            std::cout << "Invalid format.\n";
            continue;
        }

        int from = algebraic_to_square(input.substr(0, 2));
        int to = algebraic_to_square(input.substr(2, 2));

        // Collect every legal move matching this from/to — normally one,
        // but four in the promotion case (one per promotion_piece choice).
        std::vector<Move> matches;
        for (const Move &m : legal_moves)
        {
            if (m.from == from && m.to == to)
            {
                matches.push_back(m);
            }
        }

        if (matches.empty())
        {
            std::cout << "Illegal move.\n";
            continue;
        }

        if (matches.size() == 1)
        {
            return matches[0];
        }

        // Promotion: ask which piece.
        std::cout << "Promote to (q/r/b/n): ";
        std::string choice;
        std::cin >> choice;

        PieceType wanted = PieceType::NONE;
        if (!choice.empty())
        {
            switch (std::tolower(choice[0]))
            {
            case 'q':
                wanted = PieceType::QUEEN;
                break;
            case 'r':
                wanted = PieceType::ROOK;
                break;
            case 'b':
                wanted = PieceType::BISHOP;
                break;
            case 'n':
                wanted = PieceType::KNIGHT;
                break;
            default:
                break;
            }
        }

        bool found = false;
        for (const Move &m : matches)
        {
            if (m.promotion_piece == wanted)
            {
                return m;
            }
        }

        std::cout << "Invalid promotion choice.\n";
        // loop back to the top and re-prompt the whole move
    }
}

void run_game()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "Welcome to Borealis 0.2 -- Yggdrasil.\nTo make a move, simply type the first coordinate, then the second.\n";
    BoardState board = starting_position();

    while (true)
    {
        print_board(board);
        std::cout << "\n";

        GameResult result = check_game_end(board);
        if (result != GameResult::ONGOING)
        {
            switch (result)
            {
            case GameResult::WHITE_WINS:
                std::cout << "Checkmate - White wins.\n";
                break;
            case GameResult::BLACK_WINS:
                std::cout << "Checkmate - Black wins.\n";
                break;
            case GameResult::STALEMATE:
                std::cout << "Draw - stalemate.\n";
                break;
            case GameResult::INSUFFICIENT_MATERIAL:
                std::cout << "Draw - insufficient material.\n";
                break;
            case GameResult::FIFTY_MOVE:
                std::cout << "Draw - fifty-move rule.\n";
                break;
            default:
                break;
            }
            break;
        }

        Color enemy = (board.side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (is_square_attacked(board, find_king_square(board, board.side_to_move), enemy))
        {
            std::cout << "King is in check." << "\n";
        }

        std::vector<Move> moves = generate_legal_moves(board, board.side_to_move);

        Move chosen = (board.side_to_move == Color::WHITE)
                          ? get_human_move(board, moves)
                          : pick_random_move(moves);

        print_move(chosen);
        board = apply_move(board, chosen);
    }
}
