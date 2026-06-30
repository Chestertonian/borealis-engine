#include "Move.h"
#include "Board.h"
#include <iostream>

void print_move(const Move& move) {
    std::cout << square_to_coordinate(move.from) << " -> " << square_to_coordinate(move.to);

    switch (move.type) {
        case MoveType::Normal:
            break;
        case MoveType::DoublePawnPush:
            std::cout << " (double pawn push)";
            break;
        case MoveType::EnPassant:
            std::cout << " (en passant)";
            break;
        case MoveType::CastleKingside:
            std::cout << " (castle kingside)";
            break;
        case MoveType::CastleQueenside:
            std::cout << " (castle queenside)";
            break;
        case MoveType::Promotion:
            std::cout << " (promotion to ";
            switch (move.promotion_piece) {
                case PieceType::Queen:  std::cout << "Queen"; break;
                case PieceType::Rook:   std::cout << "Rook"; break;
                case PieceType::Bishop: std::cout << "Bishop"; break;
                case PieceType::Knight: std::cout << "Knight"; break;
                default: std::cout << "?"; break;
            }
            std::cout << ")";
            break;
    }

    std::cout << '\n';
}