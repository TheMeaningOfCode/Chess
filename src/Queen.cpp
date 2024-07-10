#include "Queen.h"
#include "Chessboard.h"
#include "Rook.h"
#include "Bishop.h"

Queen::Queen(int i, int j, string cl) : Piece(i , j, cl) {}
Queen::~Queen() {}
int Queen::get_value() {
  return 9;
}
string Queen::get_name() {
  return "Queen";
}
set<pair<int, int>> Queen::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  Rook* r = new Rook(x, y, color);
  Bishop* b = new Bishop(x, y, color);

  set<pair<int, int>> rook_moves, bishop_moves;

  rook_moves = r->move(board);
  bishop_moves = b->move(board);
  
  valid_moves.insert(rook_moves.begin(), rook_moves.end());
  valid_moves.insert(bishop_moves.begin(), bishop_moves.end());
  

  delete r;
  delete b;

  return valid_moves;
}