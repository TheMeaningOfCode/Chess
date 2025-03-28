#ifndef AI_H
#define AI_H

//not AI, opponent

class AI;

#include "Chessboard.h"
#include <unistd.h>
#include <iostream>

using namespace std;

class AI {
  public:
    AI(ChessBoard* board);
    virtual ~AI();
    virtual string get_type() = 0;
    virtual bool make_move() = 0;

  protected:
    ChessBoard* board;
};

class EasyAI : public AI {
  public:
    EasyAI(ChessBoard* board);
    ~EasyAI();
    string get_type();
    bool make_move();
};

class MediumAI : public AI {
  public:
    MediumAI(ChessBoard* board);
    ~MediumAI();
    string get_type();
    bool make_move();
};

class HardAI : public AI {
  public:
    HardAI(ChessBoard* board);
    ~HardAI();
    string get_type();
    bool make_move();
    int eval_move(int depth, pair<int, int>& first_candidate, pair<int, int>& candidate_second);
};

#endif
