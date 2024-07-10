#include "King.h"
#include "Chessboard.h"

King::King(int i, int j, string cl) : Piece(i , j, cl) {}
King::~King() {}



set<pair<int, int>> King::castling(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;
  if (move_count) return valid_moves;
  
  if (!move_count          && !board->position_in_check(pair<int, int>(x, y)) && 
  !board->m_square[x-1][y] && !board->position_in_check(pair<int, int>(x-1, y)) &&
  !board->m_square[x-2][y] && !board->position_in_check(pair<int, int>(x-2, y)) &&
  !board->m_square[x-3][y] && 
   board->m_square[x-4][y] && !board->m_square[x-4][y]->move_count) {
    valid_moves.insert(pair<int, int>(x-2, y));
  }

  if (!move_count          && !board->position_in_check(pair<int, int>(x, y)) && 
  !board->m_square[x+1][y] && !board->position_in_check(pair<int, int>(x+1, y)) &&
  !board->m_square[x+2][y] && !board->position_in_check(pair<int, int>(x+2, y)) &&
   board->m_square[x+3][y] && !board->m_square[x+3][y]->move_count) {
    valid_moves.insert(pair<int, int>(x+2, y));
  }

  return valid_moves;
}



set<pair<int, int>> King::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if (x+i < 0 || x+i >= 8 || y+j < 0 || y+j >= 8) continue;

      if (!board->m_square[x+i][y+j] || board->m_square[x+i][y+j]->color != color) {
        valid_moves.insert(pair<int, int>(x+i, y+j));
      }
    }
  }

  return valid_moves;
}

string King::get_name() {
  return "King";
}

int King::get_value() {
  return 999;
}
