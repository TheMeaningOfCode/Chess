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
  for (auto it = legal_moves.begin(); it != legal_moves.end(); it++) {
    if (it->second.size()) {
      this->board->make_move(it->first, *(it->second.begin()));
      return true;
    }
  }
  return false;
}

MediumAI::MediumAI(ChessBoard* board) : AI(board) {}
MediumAI::~MediumAI() {}
string MediumAI::get_type() {return "MediumAI";}


bool MediumAI::make_move() {
  pair<int, int> candidate_first;
  pair<int, int> candidate_second;
  int score = -1;

  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  for (auto it = legal_moves.begin(); it != legal_moves.end(); it++) {
    if (it->second.size()) {
      if (score == -1) {
        candidate_first = it->first;
        candidate_second = *(it->second.begin());
        score = 0;
      }

      /* check whether there is something to take */
      for (auto ut = it->second.begin(); ut != it->second.end(); ut++) {
        if (board->m_square[ut->first][ut->second] == nullptr) continue;

        Piece* piece = board->m_square[ut->first][ut->second];
        //if (piece->color != "White") continue; // This won't work for white AI!

        if (piece->get_value() > score) {
          candidate_first = it->first;
          candidate_second = *ut;
          score = piece->get_value();
        }
      }
    }
  }
  if (score >= 0) {
    this->board->make_move(candidate_first, candidate_second);
    return true;
  }
  return false;
}

HardAI::HardAI(ChessBoard* board) : AI(board) {}
HardAI::~HardAI() {}
string HardAI::get_type() {return "HardAI";}


int HardAI::eval_move(int depth, pair<int, int>& first_candidate, pair<int, int>& candidate_second) {
  int best_score = -10000;
  int score;

  map<pair<int, int>, set<pair<int, int>>> legal_moves = this->board->legal_moves();
  for (auto it = legal_moves.begin(); it != legal_moves.end(); it++) {
    for (auto ut = it->second.begin(); ut != it->second.end(); ut++) {
      Piece* piece = board->m_square[ut->first][ut->second];
      if (piece == nullptr) {
        score = 0;
      } else {
        score = piece->get_value();
      }

      if (depth > 0 && (piece == nullptr || piece->get_name() != "King")) {
        this->board->make_move(it->first, *ut);
        pair<int, int> xfirst;
        pair<int, int> xsecond;
        score -= this->eval_move(depth-1, xfirst, xsecond);
        this->board->undo_move();
      }

      if (score > best_score) {
        first_candidate = it->first;
        candidate_second = *ut;
        best_score = score;
      }
    }
  }

  return best_score;
}

bool HardAI::make_move() {
  pair<int, int> candidate_first;
  pair<int, int> candidate_second;

  if (eval_move(2, candidate_first, candidate_second) == -10000)
    return false;
  this->board->make_move(candidate_first, candidate_second);
  return true;
}
