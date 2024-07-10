#include "Rook.h"
#include "Chessboard.h"


Rook::Rook(int i, int j, string cl) : Piece(i , j, cl) {}
Rook::~Rook() {}
int Rook::get_value() {
  return 5;
}
string Rook::get_name() {
  return "Rook";
}
set<pair<int, int>> Rook::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  for (const auto& dir : directions) {
    int dir_x = dir[0];
    int dir_y = dir[1];

    int i = x + dir_x;
    int j = y + dir_y;

    while (i >= 0 && i < 8 && j >= 0 && j < 8) {
      if (!board->m_square[i][j]) {
        valid_moves.insert({i, j});
      } 
      else if (board->m_square[i][j]->color != color) {
        valid_moves.insert({i, j});
        break;
      } 
      else {
        break;
      }

      i += dir_x;
      j += dir_y;
    }
  }

  return valid_moves;
}