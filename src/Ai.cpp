#include "Ai.h"


AI::AI(ChessBoard* board) {
  this->board = board;
}
AI::~AI() {}

EasyAI::EasyAI(ChessBoard* board) : AI(board) {}
EasyAI::~EasyAI() {}
string EasyAI::get_type() {return "EasyAI";}

bool EasyAI::make_move() {
  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  pair<int, int> from;
  pair<int, int> to;
  int random_pos;
  
  if (legal_moves.empty()) return false;

  random_pos = rand() % legal_moves.size();
  auto it = legal_moves.begin();
  advance(it, random_pos);

  random_pos = rand() % legal_moves[it->first].size();
  auto ut = legal_moves.at(it->first).begin();
  advance(ut, random_pos);

  from = it->first;
  to = *ut; 

  this->board->make_move(from, to);
  return true;
}

MediumAI::MediumAI(ChessBoard* board) : AI(board) {}
MediumAI::~MediumAI() {}
string MediumAI::get_type() {return "MediumAI";}


bool MediumAI::make_move() {
  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  pair<int, int> from;
  pair<int, int> to;
  int random_pos;
  int score = -1;

  if (legal_moves.empty()) return false;

  random_pos = rand() % legal_moves.size();
  auto it = legal_moves.begin();
  advance(it, random_pos);

  random_pos = rand() % legal_moves[it->first].size();
  auto ut = legal_moves.at(it->first).begin();
  advance(ut, random_pos);

  from = it->first;
  to = *ut; 

  for (auto it = legal_moves.begin(); it != legal_moves.end(); it++) {
    /* check whether there is something to take */
    for (auto ut = it->second.begin(); ut != it->second.end(); ut++) {
      if (board->m_square[ut->first][ut->second] == nullptr) continue;

      Piece* piece = board->m_square[ut->first][ut->second];
      //if (piece->color != "White") continue; // This won't work for white AI!

      if (piece->get_value() > score) {
        from = it->first;
        to = *ut;
        score = piece->get_value();
      }
    }
  }

  this->board->make_move(from, to);
  return true;
}

HardAI::HardAI(ChessBoard* board) : AI(board) {}
HardAI::~HardAI() {}
string HardAI::get_type() {return "HardAI";}


int HardAI::eval_move(int depth, pair<int, int>& from, pair<int, int>& to) {
  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  int best_score = 0;
  int score = 0;
  Piece* piece;
  pair<int, int> xfirst;
  pair<int, int> xsecond;

  for (auto it = legal_moves.begin(); it != legal_moves.end(); it++) {
    for (auto ut = it->second.begin(); ut != it->second.end(); ut++) {
      piece = board->m_square[ut->first][ut->second];

      if (piece) score = piece->get_value();

      if (depth > 0 && (piece == nullptr || piece->get_name() != "King")) {
        this->board->make_move(it->first, *ut);
        score -= this->eval_move(depth-1, xfirst, xsecond);
        this->board->undo_move();
      }

      if (score > best_score) {
        from = it->first;
        to = *ut;
        best_score = score;
      }
    }
  }

  return best_score;
}

bool HardAI::make_move() {
  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  pair<int, int> from;
  pair<int, int> to;
  int random_pos;

  if (legal_moves.empty()) return false;

  random_pos = rand() % legal_moves.size();
  auto it = legal_moves.begin();
  advance(it, random_pos);

  random_pos = rand() % legal_moves[it->first].size();
  auto ut = legal_moves.at(it->first).begin();
  advance(ut, random_pos);

  from = it->first;
  to = *ut;

  if (eval_move(1, from, to) < -8000)
    return false;
  this->board->make_move(from, to);
  return true;
}
