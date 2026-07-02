#include "game.h"
#include "MoveGen.h"
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
    std::cout << "  0.1 Ginnungagap \n";
    std::cout << "Do you want to play (w)hite or (b)lack?\n";
    std::cout << "If you do not give valid input, you will play black.\n";

    char color_input;
    std::cin >> color_input;
    std::cin.ignore(); // eat the leftover newline before any getline

    Color result = (std::tolower(color_input) == 'w') ? Color::White : Color::Black;

    std::cout << "To move, type the initial square and destination square, separated by a space. "
                 "To promote, a third argument: the lowercase symbol of the piece to which you want to promote.\n";
    std::cout << "To quit, type 'quit.'\n";

    return result;
}

InputResult get_human_move(const GameState& state, const std::vector<Move>& legal_moves, Move& out_move)
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

    std::optional<int> from_sq = coordinate_to_square(from_str);
    std::optional<int> to_sq   = coordinate_to_square(to_str);

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
    GameState state;
    setup_starting_gamestate(state);
    Color human = choose_human_side();

    while (true)
    {
        print_gamestate(state);

        std::vector<Move> legal_moves = generate_all_moves(state);

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
            print_gamestate(state);
            report_game_end(status);
            break;
        }
    }
}