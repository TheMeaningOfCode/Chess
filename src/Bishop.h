#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class ChessBoard;


class Bishop : public Piece {
  private:
  public:
    Bishop(int i, int j, string cl);
    ~Bishop();
    int get_value() override;
    string get_name() override;
    set<pair<int, int>> move(const ChessBoard* board) override;
    void add_in_direction(const ChessBoard* board, bool up, bool right, set<pair<int, int>>& valid_moves);
};


#endif
