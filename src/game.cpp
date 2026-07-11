#include "bitboards.h"
#include "MoveStruct.h"
#include <optional>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <iostream>
#include <cctype>
#include <vector>

Color choose_human_side()
{
    std::cout << "Welcome to Borealis!\n";
    std::cout << "  0.2 Yggdrasil \n";
    std::cout << "Do you want to play (w)hite or (b)lack?\n";
    std::cout << "If you do not give valid input, you will play black.\n";

    char color_input;
    std::cin >> color_input;
    std::cin.ignore(); // eat the leftover newline before any getline

    Color result = (std::tolower(color_input) == 'w') ? Color::WHITE : Color::BLACK;

    std::cout << "To move, type the initial square and destination square, separated by a space. "
                 "To promote, a third argument: the lowercase symbol of the piece to which you want to promote.\n";
    std::cout << "To quit, type 'quit.'\n";

    return result;
}

InputResult get_human_move(const BoardState& state, const std::vector<Move>& legal_moves, Move& out_move)
{
    std::string line;
    std::getline(std::cin, line);

    if (line == "quit")
    {
        return InputResult::Quit;
    }

    std::istringstream stream(line);
    std::string from_str, to_str, promo_str;

    if (!(stream >> from_str >> to_str))
    {
        std::cout << "Couldn't parse that: expected format like 'e2 e4'.\n";
        return InputResult::Invalid;
    }

    bool has_promo = static_cast<bool>(stream >> promo_str);

    std::optional<int> from_sq = algebraic_to_square(from_str);
    std::optional<int> to_sq   = square_to_algebraic(to_str);

    if (!from_sq || !to_sq)
    {
        std::cout << "Invalid square name.\n";
        return InputResult::Invalid;
    }

    char promo_char = has_promo ? promo_str[0] : '\0';

    for (const Move& m : legal_moves)
    {
        bool square_match = (m.from == *from_sq && m.to == *to_sq);
        if (!square_match) continue;

        bool is_promo_move = (m.type == MoveType::Promotion);

        if (is_promo_move)
        {
            if (has_promo && m.promotion_piece == notation_to_piece_type(promo_char))
            {
                out_move = m;
                return InputResult::Move;
            }
        }
        else
        {
            if (!has_promo)
            {
                out_move = m;
                return InputResult::Move;
            }
        }
    }

    std::cout << "That's not a legal move.\n";
    return InputResult::Invalid;
}

Move get_bot_move(const std::vector<Move>& legal_moves)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, legal_moves.size() - 1);
    return legal_moves[dist(rng)];
}

void report_game_end(GameStatus status)
{
    switch (status)
    {
        case GameStatus::CHECKMATE:
            std::cout << "Checkmate.\n";
            break;
        case GameStatus::STALEMATE:
            std::cout << "Stalemate.\n";
            break;
        case GameStatus::FIFTY_MOVE_DRAW:
            std::cout << "Draw by fifty-move rule.\n";
            break;
        case GameStatus::INSUFFICIENT_MATERIAL:
            std::cout << "Draw by insufficient material.\n";
            break;
        case GameStatus::REPETITION:
            std::cout << "Draw by repetition.\n";
            break;
        default:
            std::cout << "Game over.\n";
            break;
    }
}

void play_game()
{
    BoardState state;
    setup_starting_BoardState(state);
    Color human = choose_human_side();
    Color computer = (human == Color::WHITE) ? Color::BLACK : Color::WHITE;

    while (true)
    {
        print_board(state);

        std::vector<Move> legal_moves = generate_legal_moves(state, computer);

        if (state.side_to_move == human)
        {
            Move chosen;
            InputResult result = get_human_move(state, legal_moves, chosen);

            if (result == InputResult::Quit)
            {
                std::cout << "Goodbye.\n";
                break;
            }
            if (result == InputResult::Invalid)
            {
                continue; // re-prompt
            }
            state = apply_move(state, chosen);
        }
        else
        {
            Move chosen = get_bot_move(legal_moves);
            state = apply_move(state, chosen);
            print_move(chosen);
        }

        GameStatus status = get_game_status(state);
        if (status != GameStatus::ONGOING)
        {
            std::cout << "\n";
            print_board(state);
            std::cout << "\n";
            report_game_end(status);
            break;
        }
    }
}

PieceType notation_to_piece_type(char piece)
{
    PieceType type = PieceType::None;

    switch (std::tolower(piece))
    {
    case 'q':
        type=PieceType::QUEEN;
        break;
    case 'k':
        type=PieceType::KING;
        break;
    case 'r':
        type=PieceType::ROOK;
        break;
    case 'b':
        type=PieceType::BISHOP;
        break;
    case 'n':
        type=PieceType::KNIGHT;
        break;
    case 'p':
        type=PieceType::PAWN;
        break;

    default:
        type = PieceType::NONE;
        break;
    }

    return type;
}

std::string game_status_to_string(GameStatus status)
{
    switch (status)
    {
    case GameStatus::ONGOING:
        return "Ongoing\n";
    case GameStatus::CHECKMATE:
        return "Checkmate\n";
    case GameStatus::STALEMATE:
        return "Stalemate\n";
    case GameStatus::FIFTY_MOVE_DRAW:
        return "Draw by fifty-move rule\n";
    case GameStatus::INSUFFICIENT_MATERIAL:
        return "Draw by insufficient material\n";
    }
    return "Unknown"; // safety net, shouldn't be reached
}

GameStatus get_game_status(const GameState &state)
{
    if (generate_legal_moves(state).empty())
    {
        Color attacker = (state.side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (is_square_attacked(state, find_king_square(state, state.side_to_move), attacker))
        {
            return GameStatus::CHECKMATE;
        }

        else
        {
            return GameStatus::STALEMATE;
        }
    }

    if (state.halfmove_clock >= 100)
    {
        return GameStatus::FIFTY_MOVE_DRAW;
    }

    if (is_insufficient_material(state))
    {
        return GameStatus::INSUFFICIENT_MATERIAL;
    }

    else
    {
        return GameStatus::ONGOING;
    }
}

bool is_insufficient_material(const BoardState& board) {
    // Any pawn, rook, or queen (either color) means there's still enough
    // material to force checkmate in principle — bail out immediately.
    uint64_t major_and_pawn_pieces =
        board.bitboards[piece_index(Color::WHITE, PieceType::PAWN)]
      | board.bitboards[piece_index(Color::WHITE, PieceType::ROOK)]
      | board.bitboards[piece_index(Color::WHITE, PieceType::QUEEN)]
      | board.bitboards[piece_index(Color::BLACK, PieceType::PAWN)]
      | board.bitboards[piece_index(Color::BLACK, PieceType::ROOK)]
      | board.bitboards[piece_index(Color::BLACK, PieceType::QUEEN)];

    if (major_and_pawn_pieces != 0) return false;

    int white_knights = count_bits(board.bitboards[piece_index(Color::WHITE, PieceType::KNIGHT)]);
    int white_bishops = count_bits(board.bitboards[piece_index(Color::WHITE, PieceType::BISHOP)]);
    int black_knights = count_bits(board.bitboards[piece_index(Color::BLACK, PieceType::KNIGHT)]);
    int black_bishops = count_bits(board.bitboards[piece_index(Color::BLACK, PieceType::BISHOP)]);

    int total_minors = white_knights + white_bishops + black_knights + black_bishops;

    if (total_minors == 0) return true;                     // K vs K
    if (total_minors == 1) return true;                     // K+N vs K, or K+B vs K
    if (total_minors == 2 && white_bishops == 1 && black_bishops == 1) return true; // K+B vs K+B

    return false; // anything else treated as sufficient
}