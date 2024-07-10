#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class ChessBoard;

class Queen : public Piece {
  private:
  public:
    Queen(int i, int j, string cl);
    ~Queen();
    int get_value() override;
    string get_name() override;
    set<pair<int, int>> move(const ChessBoard* board);
};

#endif