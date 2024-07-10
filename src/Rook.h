#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class ChessBoard;

class Rook : public Piece {
  private:
  public:
    Rook(int i, int j, string cl);
    ~Rook();
    int get_value() override;
    string get_name() override;
    set<pair<int, int>> move(const ChessBoard* board);
};

#endif