#include "Bishop.h"
#include "Chessboard.h"


Bishop::Bishop(int i, int j, string cl) : Piece(i , j, cl) {}
Bishop::~Bishop() {}
int Bishop::get_value() {
  return 3;
}
string Bishop::get_name() {
  return "Bishop";
}


void Bishop::add_in_direction(const ChessBoard* board, bool up, bool right, set<pair<int, int>>& valid_moves) {
  int a, b;

  for (int i = 1; i < 8; i++) {
    up ? b = y+i : b = y-i;
    right ? a = x+i : a = x-i;

    if (a < 0 || a >= 8 || b < 0 || b >= 8) break;

    if (!board->m_square[a][b]) {
      valid_moves.insert(pair<int, int>(a, b));
      continue;
    }
    if (board->m_square[a][b]->color != color) {
      valid_moves.insert(pair<int, int>(a, b));
    }
    return;
  }
}

set<pair<int, int>> Bishop::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  add_in_direction(board, true, true, valid_moves);
  add_in_direction(board, true, false, valid_moves);
  add_in_direction(board, false, true, valid_moves);
  add_in_direction(board, false, false, valid_moves);

  return valid_moves;
}