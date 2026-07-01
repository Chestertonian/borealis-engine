#include "GameState.h"
#include <iostream>
#include <sstream>
#include "Move.h"

void setup_starting_gamestate(GameState &state)
{
    fen_to_gamestate("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", state);
}

void fen_to_gamestate(const std::string &fen, GameState &state)
{
    std::istringstream stream(fen);
    std::string placement, side, castling, en_passant;
    int halfmove, fullmove;

    stream >> placement >> side >> castling >> en_passant >> halfmove >> fullmove;

    fen_to_board(placement, state.board);

    state.side_to_move = (side == "w") ? Color::White : Color::Black;

    state.white_kingside_castle = (castling.find('K') != std::string::npos);
    state.white_queenside_castle = (castling.find('Q') != std::string::npos);
    state.black_kingside_castle = (castling.find('k') != std::string::npos);
    state.black_queenside_castle = (castling.find('q') != std::string::npos);

    state.en_passant_square = (en_passant == "-") ? -1 : coordinate_to_square(en_passant);

    state.halfmove_clock = halfmove;
    state.fullmove_number = fullmove;
}

void print_gamestate(const GameState &state)
{
    print_board(state.board);

    std::cout << "Side to move: " << (state.side_to_move == Color::White ? "White" : "Black") << '\n';
    std::cout << "Castling: "
              << (state.white_kingside_castle ? "K" : "")
              << (state.white_queenside_castle ? "Q" : "")
              << (state.black_kingside_castle ? "k" : "")
              << (state.black_queenside_castle ? "q" : "") << '\n';
    std::cout << "En passant square: " << state.en_passant_square << '\n';
    std::cout << "Halfmove clock: " << state.halfmove_clock << '\n';
    std::cout << "Fullmove number: " << state.fullmove_number << '\n';
}

GameState apply_move(GameState state, const Move &move)
{
    // state is already a copy — mutate it directly
    // Pseudocode:
    // Get piece on move.from
    // Move it to move.to
    // Update side to move
    // Update from square to null
    // Half-move counter, en passant, castling: later

    state.side_to_move = (state.side_to_move == Color::White)
                             ? Color::Black
                             : Color::White;

    state.board[move.to] = state.board[move.from];
    state.board[move.from] = '.';

    return state;
}
