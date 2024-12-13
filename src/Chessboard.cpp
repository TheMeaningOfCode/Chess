#include "Chessboard.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include <unistd.h>

#include <deque>
#include <string>

#include <iostream>


using namespace std;

ChessBoard::ChessBoard() {
  int i, j;
  for (j = 7; j < 8; j++) {
    m_square[0][j] = new Rook(0, j, "Black");
    m_square[1][j] = new Knight(1, j, "Black");
    m_square[2][j] = new Bishop(2, j, "Black");
    m_square[3][j] = new Queen(3, j, "Black");
    m_square[4][j] = new King(4, j, "Black");
    m_square[5][j] = new Bishop(5, j, "Black");
    m_square[6][j] = new Knight(6, j, "Black");
    m_square[7][j] = new Rook(7, j, "Black");
  }
  for (i = 0; i < 8; i++) {
    for (j = 6; j < 7; j++) {
      m_square[i][j] = new Pawn(i, j, "Black");
    }
  }
  for (i = 0; i < 8; i++) {
    for (j = 2; j < 6; j++) {
      m_square[i][j] = nullptr;
    }
  }
  for (i = 0; i < 8; i++) {
    for (j = 1; j < 2; j++) {
      m_square[i][j] = new Pawn(i, j, "White");
    }
  }
  for (j = 0; j < 1; j++) {
    m_square[0][j] = new Rook(0, j, "White");
    m_square[1][j] = new Knight(1, j, "White");
    m_square[2][j] = new Bishop(2, j, "White");
    m_square[3][j] = new Queen(3, j, "White");
    m_square[4][j] = new King(4, j, "White");
    m_square[5][j] = new Bishop(5, j, "White");
    m_square[6][j] = new Knight(6, j, "White");
    m_square[7][j] = new Rook(7, j, "White");
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (m_square[i][j]) all_pieces.push_back(m_square[i][j]);
    }
  }
}

ChessBoard::ChessBoard(int tutorial_number) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      m_square[i][j] = nullptr;
    }
  }

  //Queen
  if (tutorial_number == 1) {
    m_square[2][0] = new Queen(2, 0, "White");
    m_square[3][0] = new Queen(3, 0, "White");
    m_square[4][0] = new Queen(4, 0, "White");
    m_square[5][0] = new Queen(5, 0, "White");
    m_square[3][1] = new Queen(3, 1, "White");
    m_square[4][1] = new Queen(4, 1, "White");

    m_square[0][7] = new Queen(2, 0, "Black");
  }
  //Bishop Knight Rook
  if (tutorial_number == 2) {
    m_square[0][0] = new Rook(0, 0, "White");
    m_square[1][0] = new Bishop(1, 0, "White");
    m_square[2][0] = new Knight(2, 0, "White");
    m_square[5][0] = new Knight(5, 0, "White");
    m_square[6][0] = new Bishop(6, 0, "White");
    m_square[7][0] = new Rook(7, 0, "White");

    m_square[0][7] = new Rook(0, 7, "Black");
    m_square[1][7] = new Bishop(1, 7, "Black");
    m_square[2][7] = new Knight(2, 7, "Black");
    m_square[5][7] = new Knight(5, 7, "Black");
    m_square[6][7] = new Bishop(6, 7, "Black");
    m_square[7][7] = new Rook(7, 7, "Black");    
  }
  //castling
  if (tutorial_number == 3) {
    m_square[0][0] = new Rook(0, 0, "White");
    m_square[4][0] = new King(4, 0, "White");
    m_square[7][0] = new Rook(7, 0, "White");

    m_square[3][7] = new Rook(3, 7, "Black");
    m_square[4][7] = new King(4, 7, "Black");
    m_square[7][7] = new Rook(7, 7, "Black");    
  }
  //en_passant and promotion
  if (tutorial_number == 4) {
    for (int i = 0; i < 8; i++) {
      if (i % 2) {
        m_square[i][3] = new Pawn(i, 3, "White");
      }
      else {
        m_square[i][6] = new Pawn(i, 6, "Black");
      }
    }

  }  

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (m_square[i][j]) all_pieces.push_back(m_square[i][j]);
    }
  }
}

ChessBoard::~ChessBoard() {
  for (auto it = all_pieces.begin(); it != all_pieces.end(); it++) {
   if (*it) delete(*it);
  }
}

void ChessBoard::promote() {
  for (int i = 0; i < 8; i++) {
    if (dynamic_cast<Pawn*>(m_square[i][0])) {
      st.back().promotion = true;
      st.back().m_extra = new Queen(st.back().m_to.first, st.back().m_to.second, turn);
      all_pieces.push_back(st.back().m_extra);
      m_square[i][0] = st.back().m_extra;

    }
    if (dynamic_cast<Pawn*>(m_square[i][7])) {
      st.back().promotion = true;
      st.back().m_extra = new Queen(st.back().m_to.first, st.back().m_to.second, turn);
      all_pieces.push_back(st.back().m_extra);
      m_square[i][7] = st.back().m_extra;

    }
  }
}

void ChessBoard::change_promotion(string name) {
  turn == "White" ? turn = "Black" : turn = "White";

  if (name == "q") {
    st.back().m_extra = new Queen(st.back().m_to.first, st.back().m_to.second, turn);
  }
  else if (name == "r") {
    st.back().m_extra = new Rook(st.back().m_to.first, st.back().m_to.second, turn);
  }
  else if (name == "b") {
    st.back().m_extra = new Bishop(st.back().m_to.first, st.back().m_to.second, turn);
  }
  else if (name == "k") {
    st.back().m_extra = new Knight(st.back().m_to.first, st.back().m_to.second, turn);
  }
  else {
    turn == "White" ? turn = "Black" : turn = "White";
    return;
  }

  turn == "White" ? turn = "Black" : turn = "White";
  all_pieces.push_back(st.back().m_extra);
  m_square[st.back().m_to.first][st.back().m_to.second] = st.back().m_extra;
}


bool ChessBoard::position_in_check(pair<int, int> pos) const {
  Rook* r = new Rook(pos.first, pos.second, turn);
  King* k = new King(pos.first, pos.second, turn);
  Queen* q = new Queen(pos.first, pos.second, turn);
  Pawn* p = new Pawn(pos.first, pos.second, turn);
  Knight* n = new Knight(pos.first, pos.second, turn);
  Bishop* b = new Bishop(pos.first, pos.second, turn);

  set<pair<int, int>> all_moves;

  all_moves = r->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    Rook* ptr = dynamic_cast<Rook*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }

  all_moves.clear();
  all_moves = k->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    King* ptr = dynamic_cast<King*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }

  all_moves.clear();
  all_moves = q->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    Queen* ptr = dynamic_cast<Queen*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }

  all_moves.clear();
  all_moves = p->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    Pawn* ptr = dynamic_cast<Pawn*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }

  all_moves.clear();
  all_moves = n->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    Knight* ptr = dynamic_cast<Knight*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }

  all_moves.clear();
  all_moves = b->move(this);
  for (auto it = all_moves.begin(); it != all_moves.end(); it++) {
    if (!m_square[it->first][it->second]) continue;
    Bishop* ptr = dynamic_cast<Bishop*>(m_square[it->first][it->second]);
    if (ptr && m_square[it->first][it->second]->color != turn) return true;
  }


  delete r;
  delete k;
  delete q;
  delete p;
  delete n;
  delete b;

  return false;
}


bool ChessBoard::king_in_check() {
  set<pair<int, int>> opponent_moves;
  set<pair<int, int>> tmp;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (!m_square[i][j] || m_square[i][j]->color != turn) continue;

      tmp = m_square[i][j]->move(this);
      opponent_moves.insert(tmp.begin(), tmp.end());
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (!m_square[i][j]) continue;
      if (m_square[i][j]->color != turn && m_square[i][j]->get_name() == "King") {
        return (opponent_moves.find(pair<int, int>(i, j)) != opponent_moves.end());
      }
    }
  }

  return false;
}


map<pair<int, int>, set<pair<int, int>>> ChessBoard::legal_moves() {
  map<pair<int, int>, set<pair<int, int>>> possible_moves;

  set<pair<int, int>> piece_moves;
  set<pair<int, int>> illegal_moves;


  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (!m_square[i][j] || m_square[i][j]->color != turn) continue; 
      illegal_moves.clear();
      piece_moves.clear();

      piece_moves = m_square[i][j]->move(this);



      //filter here
      for (auto it = piece_moves.begin(); it != piece_moves.end(); it++) {
        //cout << (*it).first << " " << (*it).second << endl;
        make_move(pair<int, int>(i, j), *it);
        if (king_in_check()) illegal_moves.insert(*it);
        undo_move();
      }

      //castling
      King* kng = dynamic_cast<King*>(m_square[i][j]);
      if (kng && kng->get_color() == turn) {
        set<pair<int, int>> to_be_added = kng->castling(this);
        piece_moves.insert(to_be_added.begin(), to_be_added.end());
      }

      //en_passant
      Pawn* pwn = dynamic_cast<Pawn*>(m_square[i][j]);
      if (pwn) {
        set<pair<int, int>> to_be_added = pwn->en_passant(this);
        piece_moves.insert(to_be_added.begin(), to_be_added.end());
      }

      for (auto& e: illegal_moves) {
        piece_moves.erase(e);
      }

      if (piece_moves.empty()) continue; 

      possible_moves.insert({pair<int, int>(i, j), piece_moves});
    }
  }
  return possible_moves;
}



bool ChessBoard::make_move(pair<int, int> from, pair<int, int> to) {
  Move last;
  last.m_from = from;
  last.m_to = to;
  last.m_picked = m_square[from.first][from.second];
  last.m_taken = m_square[to.first][to.second];

  st.push_back(last);

  m_square[to.first][to.second] = m_square[from.first][from.second];
  m_square[from.first][from.second] = nullptr;
  
  m_square[to.first][to.second]->update_pos(to);

  st.back().m_picked->move_count++;

  //check for castling and switch rook
  if (st.size() && st.back().m_picked->get_name() == "King" && st.back().m_from.first == 4) {
    st.back().castling = true;
    if (st.back().m_to.first == 2) {
      st.back().m_extra = m_square[0][st.back().m_from.second];
      m_square[0][st.back().m_from.second] = nullptr;
      m_square[3][st.back().m_from.second] = st.back().m_extra;
      st.back().m_extra->update_pos(pair<int, int>(3, st.back().m_extra->y));
    }

    if (st.back().m_to.first == 6) {
      st.back().m_extra = m_square[7][st.back().m_from.second];
      m_square[7][st.back().m_from.second] = nullptr;
      m_square[5][st.back().m_from.second] = st.back().m_extra;
      st.back().m_extra->update_pos(pair<int, int>(5, st.back().m_extra->y));
    }
  }

  //check for en_passant
  if (st.back().m_from.first != st.back().m_to.first && !st.back().m_taken && st.back().m_picked->get_name() == "Pawn") {
    st.back().en_passant = true;
    st.back().m_extra = m_square[st.back().m_to.first][st.back().m_from.second];
    m_square[st.back().m_to.first][st.back().m_from.second] = nullptr;
  }

  //check for promotion
  promote();

  turn == "White" ? turn = "Black" : turn = "White";

  return true;
}

void ChessBoard::undo_move() {
  if (st.empty()) return;
  
  //revert castling for tower
  if (st.back().castling) {
    if (st.back().m_to.first == 2) {
      m_square[3][st.back().m_to.second] = nullptr;
      m_square[0][st.back().m_to.second] = st.back().m_extra;
      st.back().m_extra->update_pos(pair<int, int>(0, st.back().m_to.second));
    }

    if (st.back().m_to.first == 6) {
      m_square[5][st.back().m_to.second] = nullptr;
      m_square[7][st.back().m_to.second] = st.back().m_extra;
      st.back().m_extra->update_pos(pair<int, int>(7, st.back().m_to.second));
    }
  }

  //revert en_passant
  if (st.back().en_passant) {
    m_square[st.back().m_to.first][st.back().m_from.second] = st.back().m_extra;
  }
  
  
  st.back().m_picked->move_count--;

  m_square[st.back().m_from.first][st.back().m_from.second] = st.back().m_picked;
  m_square[st.back().m_to.first][st.back().m_to.second] = st.back().m_taken;

  m_square[st.back().m_from.first][st.back().m_from.second]->update_pos(st.back().m_from);



  turn == "White" ? turn = "Black" : turn = "White";


  st.pop_back();
}

bool ChessBoard::occupied(pair<int, int> pos) {
  return m_square[pos.first][pos.second];
}

string ChessBoard::picture_name(int x, int y) {
  string filename;
  filename.clear();
  filename.append(m_square[x][y]->get_color()).append("_").append(m_square[x][y]->get_name());
  return filename;
}

bool ChessBoard::game_over() {
  map<pair<int, int>, set<pair<int, int>>> possible_moves = legal_moves();
  

  for (auto it = possible_moves.begin(); it != possible_moves.end(); it++) {
    //moves available
    if (it->second.size()) {
      return false;
    }
  }
  
  system("clear");

  turn == "White" ? turn = "Black" : turn = "White";
  if (king_in_check()) {
    cout << turn << " Won" << endl;
  }
  else {
    cout << "Tie" << endl;
  }
  turn == "White" ? turn = "Black" : turn = "White";


  return true;
}
