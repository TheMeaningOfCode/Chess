#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class ChessBoard;


class Pawn : public Piece {
  private:
  public:
    Pawn(int i, int j, string cl);
    ~Pawn();
    int get_value() override;
    set<pair<int, int>> en_passant(const ChessBoard* board);

    string get_name() override;
    set<pair<int, int>> move(const ChessBoard* board) override;
};

#endif
