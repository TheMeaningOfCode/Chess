#include "Pawn.h"
#include "Chessboard.h"

Pawn::Pawn(int i, int j, string cl) : Piece(i , j, cl) {}
Pawn::~Pawn() {}
string Pawn::get_name() {
  return "Pawn";
}
int Pawn::get_value() {
  return 1;
}

set<pair<int, int>> Pawn::en_passant(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  if (get_color() == "White") {
    if (y != 4) return valid_moves;

    for (int i = x-1; i <= x+1; i++) {
      if (i == x || i < 0 || i >= 8) continue;

      if (board->m_square[i][y] && 
          dynamic_cast<Pawn*>(board->m_square[i][y]) && 
          board->st.back().m_from.first == i &&
          board->st.back().m_from.second == y+2
      ) {
        valid_moves.insert(pair<int, int>(i, y+1));
      }

    }

  }

  if (get_color() == "Black") {
    if (y != 3) return valid_moves;

    for (int i = x-1; i <= x+1; i++) {
      if (i == x || i < 0 || i >= 8) continue;

      if (board->m_square[i][y] && 
          dynamic_cast<Pawn*>(board->m_square[i][y]) && 
          board->st.back().m_from.first == i &&
          board->st.back().m_from.second == y-2
      ) {
        valid_moves.insert(pair<int, int>(i, y-1));
      }

    }

  }


  return valid_moves;
}

set<pair<int, int>> Pawn::move(const ChessBoard* board) {
  set<pair<int, int>> valid_moves;

  if (color == "White") {
    if (y == 7) return valid_moves;    
    for (int i = -1; i <= 1; i= i+2) {
      if (x+i < 0 || x+i >= 8) continue;
      if (!board->m_square[x+i][y+1]) continue;
      if ( board->m_square[x+i][y+1]->color == color) continue;

      valid_moves.insert(pair<int, int>(x+i, y+1));
    }
    if (!move_count && !board->m_square[x][y+1] && !board->m_square[x][y+2]) valid_moves.insert(pair<int, int>(x, y+2));
    if (!board->m_square[x][y+1]) valid_moves.insert(pair<int, int>(x, y+1));

  }

  if (color == "Black") {
    if (y == 0) return valid_moves;
    for (int i = -1; i <= 1; i= i+2) {
      if (x+i < 0 || x+i >= 8) continue;
      if (!board->m_square[x+i][y-1]) continue;
      if ( board->m_square[x+i][y-1]->color == color) continue;

      valid_moves.insert(pair<int, int>(x+i, y-1));
    }
    if (!move_count && !board->m_square[x][y-1] && !board->m_square[x][y-2]) valid_moves.insert(pair<int, int>(x, y-2));
    if (!board->m_square[x][y-1]) valid_moves.insert(pair<int, int>(x, y-1));

  }


  return valid_moves;
}