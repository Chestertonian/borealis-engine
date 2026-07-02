#include "GameState.h"
#include <iostream>
#include <sstream>
#include "Move.h"
#include "MoveGen.h"

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

    if (move.type == MoveType::EnPassant)
    {
        int direction;

        if (state.side_to_move == Color::White)
        {
            direction = -1;
        }
        else
        {
            direction = 1;
        }
        state.side_to_move = (state.side_to_move == Color::White)
                                 ? Color::Black
                                 : Color::White;

        state.board[move.to - (direction * 8)] = '.';
        state.board[move.to] = state.board[move.from];
        state.board[move.from] = '.';
        state.en_passant_square = -1;
        state.halfmove_clock = 0;
        return state;
    }

    if (move.to == 63)
        state.white_kingside_castle = false;
    if (move.to == 56)
        state.white_queenside_castle = false;
    if (move.to == 7)
        state.black_kingside_castle = false;
    if (move.to == 0)
        state.black_queenside_castle = false;

    if (move.from == 63)
        state.white_kingside_castle = false;
    if (move.from == 56)
        state.white_queenside_castle = false;
    if (move.from == 60)
        state.white_kingside_castle = false;
    if (move.from == 60)
        state.white_queenside_castle = false;
    if (move.from == 7)
        state.black_kingside_castle = false;
    if (move.from == 0)
        state.black_queenside_castle = false;
    if (move.from == 4)
        state.black_kingside_castle = false;
    if (move.from == 4)
        state.black_queenside_castle = false;

    state.side_to_move = (state.side_to_move == Color::White)
                             ? Color::Black
                             : Color::White;

    if (move.type == MoveType::Promotion)
    {
        state.board[move.from] = piece_type_to_notation(move.promotion_piece, state);
        state.halfmove_clock = -1;
    }

    if (!is_empty(state.board[move.to]))
    {
        state.halfmove_clock = -1;
    }

    char piece = std::tolower(static_cast<unsigned char>(state.board[move.from]));

    if (piece == 'p')
    {
        state.halfmove_clock = -1;
    }

    state.board[move.to] = state.board[move.from];
    state.board[move.from] = '.';

    state.en_passant_square = -1;

    if (move.type == MoveType::CastleKingside)
    {
        state.board[move.from + 1] = state.board[move.to + 1];
        state.board[move.to + 1] = '.';

        if (state.side_to_move == Color::Black)
        {
            state.white_kingside_castle = false;
            state.white_queenside_castle = false;
        }
        else
        {
            state.black_kingside_castle = false;
            state.black_queenside_castle = false;
        }
    }

    if (move.type == MoveType::CastleQueenside)
    {
        state.board[move.from - 1] = state.board[move.to - 2];
        state.board[move.to - 2] = '.';

        if (state.side_to_move == Color::Black)
        {
            state.white_kingside_castle = false;
            state.white_queenside_castle = false;
        }
        else
        {
            state.black_kingside_castle = false;
            state.black_queenside_castle = false;
        }
    }

    if (move.type == MoveType::DoublePawnPush)
    {
        int direction;

        if (state.side_to_move == Color::White)
        {
            direction = -1;
        }
        else
        {
            direction = 1;
        }

        state.en_passant_square = move.to + (direction * 8);
    }

    state.halfmove_clock += 1;

    return state;
}

GameStatus get_game_status(const GameState &state)
{
    if (generate_all_moves(state).empty())
    {
        Color attacker = (state.side_to_move == Color::White) ? Color::Black : Color::White;
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

char piece_type_to_notation(PieceType piece, const GameState &state)
{
    char c = '?';

    switch (piece)
    {
    case PieceType::King:
        c = 'K';
        break;
    case PieceType::Queen:
        c = 'Q';
        break;
    case PieceType::Rook:
        c = 'R';
        break;
    case PieceType::Bishop:
        c = 'B';
        break;
    case PieceType::Knight:
        c = 'N';
        break;
    case PieceType::Pawn:
        c = 'P';
        break;
    default:
        c = '?';
        break;
    }

    // White to move -> lowercase, Black to move -> uppercase
    if (state.side_to_move == Color::White)
    {
        return static_cast<char>(std::tolower(c));
    }
    else
    {
        return c;
    }
}

PieceType notation_to_piece_type(char piece)
{
    PieceType type = PieceType::None;

    switch (std::tolower(piece))
    {
    case 'q':
        type=PieceType::Queen;
        break;
    case 'k':
        type=PieceType::King;
        break;
    case 'r':
        type=PieceType::Rook;
        break;
    case 'b':
        type=PieceType::Bishop;
        break;
    case 'n':
        type=PieceType::Knight;
        break;
    case 'p':
        type=PieceType::Pawn;
        break;

    default:
        type = PieceType::None;
        break;
    }

    return type;
}


bool is_insufficient_material(const GameState &state)
{
    int white_bishops = 0, black_bishops = 0;
    int white_knights = 0, black_knights = 0;

    for (int sq = 0; sq < 64; sq++)
    {
        char piece = state.board[sq];
        if (piece == 'p' || piece == 'P' || piece == 'r' || piece == 'R' || piece == 'Q' || piece == 'q')
        {
            return false;
        }
        // tally bishops/knights
        if (piece == 'b')
        {
            black_bishops += 1;
        }
        if (piece == 'n')
        {
            black_knights += 1;
        }
        if (piece == 'B')
        {
            white_bishops += 1;
        }
        if (piece == 'N')
        {
            white_knights += 1;
        }
    }

    // pattern match against tallies
    bool no_black_pieces = (black_bishops == 0 && black_knights == 0);
    bool no_white_pieces = (white_bishops == 0 && white_knights == 0);

    // K vs K
    if (no_white_pieces && no_black_pieces)
        return true;

    // K+B vs K (either side)
    if (white_bishops == 1 && white_knights == 0 && no_black_pieces)
        return true;
    if (black_bishops == 1 && black_knights == 0 && no_white_pieces)
        return true;

    // K+N vs K (either side)
    if (white_knights == 1 && white_bishops == 0 && no_black_pieces)
        return true;
    if (black_knights == 1 && black_bishops == 0 && no_white_pieces)
        return true;

    // K+B vs K+B (treated as always insufficient for now, ignoring square color)
    if (white_bishops == 1 && white_knights == 0 &&
        black_bishops == 1 && black_knights == 0)
        return true;

    return false;
}