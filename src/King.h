#ifndef KING_H
#define KING_H

#include <set>

#include "Piece.h"

class ChessBoard;

class King : public Piece {
  private:
  public:
    King(int i, int j, string cl);
    ~King();

    set<pair<int, int>> castling(const ChessBoard* board);
    set<pair<int, int>> move(const ChessBoard* board) override;

    int get_value() override;
    string get_name() override;
};

#endif
