#include "Knight.h"
#include "Chessboard.h"


Knight::Knight(int i, int j, string cl) : Piece(i , j, cl) {}
Knight::~Knight() {}
int Knight::get_value() {
  return 3;
}
string Knight::get_name() {
  return "Knight";
}
set<pair<int, int>> Knight::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  int a, b;
  a = x;
  b = y;

  for (int i=-2; i <= 2; i++) {
    for (int j=-2; j <= 2; j++) {
      if (i == 0 || j == 0 || i == j || i == -j) continue;

      a = x+i;
      b = y+j;

      if (a < 0 || a >= 8 || b < 0 || b >= 8) continue;

      if (board->m_square[a][b] && board->m_square[a][b]->color == color) continue;
      valid_moves.insert(pair<int, int>(a, b));
    }
  }

  return valid_moves;
}