#include "bitboards.h"
#include "bitboard_utils.h"

char piece_letter(PieceType type)
{
    switch (type)
    {
    case PieceType::KNIGHT:
        return 'N';
    case PieceType::BISHOP:
        return 'B';
    case PieceType::ROOK:
        return 'R';
    case PieceType::QUEEN:
        return 'Q';
    case PieceType::KING:
        return 'K';
    default:
        return '\0'; // PAWN, NONE
    }
}

std::string move_to_san(const Move &move,
                        const BoardState &before,
                        const std::vector<Move> &legal_moves_before,
                        const BoardState &after,
                        const std::vector<Move> &legal_moves_after)
{
    // 1. Castling short-circuits everything else.
    if (move.type == MoveType::CastleKingside)
    {
        return "O-O";
    }
    if (move.type == MoveType::CastleQueenside)
    {
        return "O-O-O";
    }

    Color opponent_color = before.side_to_move == Color::WHITE ? Color::BLACK : Color::WHITE;
    PieceType mover_type = piece_at(before, move.from, before.side_to_move);
    bool is_capture = (move.type == MoveType::EnPassant) ||
                      (piece_at(before, move.to, opponent_color) != PieceType::NONE);

    std::string san;

    if (mover_type == PieceType::PAWN)
    {
        // 2. Pawn moves: no piece letter.
        if (is_capture)
        {
            std::string from_sq = square_to_algebraic(move.from);
            san += from_sq[0]; // origin file only
            san += 'x';
        }
        san += square_to_algebraic(move.to);

        if (move.type == MoveType::Promotion)
        {
            san += '=';
            san += piece_letter(move.promotion_piece);
        }
    }
    else
    {
        // 3. Piece moves: letter + optional disambiguation + optional x + dest.
        san += piece_letter(mover_type);

        // 4. Disambiguation.
        int from_file = move.from % 8;
        int from_rank = move.from / 8;

        // A competitor sharing our file means file alone is NOT enough -> need rank too (or both).
        bool any_competitor = false;
        bool same_file_exists = false;
        bool same_rank_exists = false;
        for (const Move &other : legal_moves_before)
        {
            if (other.to != move.to || other.from == move.from)
            {
                continue;
            }
            PieceType other_type = piece_at(before, other.from, before.side_to_move);
            if (other_type != mover_type)
            {
                continue;
            }
            any_competitor = true;
            if (other.from % 8 == from_file)
                same_file_exists = true;
            if (other.from / 8 == from_rank)
                same_rank_exists = true;
        }

        if (any_competitor)
        {
            std::string origin = square_to_algebraic(move.from);
            if (!same_file_exists)
            {
                san += origin[0]; // file alone disambiguates
            }
            else if (!same_rank_exists)
            {
                san += origin[1]; // rank alone disambiguates
            }
            else
            {
                san += origin; // need both
            }
        }

        if (is_capture)
        {
            san += 'x';
        }
        san += square_to_algebraic(move.to);
    }

    // 5. Check / checkmate suffix, using post-move state.
    bool opponent_in_check = is_square_attacked(
        after,
        find_king_square(after, (before.side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE),
        (after.side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE);

    if (opponent_in_check)
    {
        san += legal_moves_after.empty() ? '#' : '+';
    }

    return san;
}