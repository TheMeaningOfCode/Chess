#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class ChessBoard;


class Knight : public Piece {
  private:
  public:
    Knight(int i, int j, string cl);
    ~Knight();
    int get_value() override;
    string get_name() override;
    set<pair<int, int>> move(const ChessBoard* board);
};

#endif