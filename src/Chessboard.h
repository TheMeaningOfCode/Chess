#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include <deque>
#include <map>

#include "Piece.h"

class Move;
class ChessBoard;

struct Move {
  pair<int, int> m_from;
  pair<int, int> m_to;
  Piece* m_picked;
  Piece* m_taken;

  Piece* m_extra;

  bool castling = false;
  bool promotion = false;
  bool en_passant = false;
};

class ChessBoard {
  private:
  public:
    string turn = "White";
    vector<Piece*> all_pieces;
    Piece* m_square[8][8];
    
    deque<Move> st;
    

    ChessBoard();
    ChessBoard(int tutorial_number);
    ~ChessBoard();

    bool check();
    bool game_over();
    bool position_in_check(pair<int, int> pos) const;
    bool king_in_check();
    void promote();
    void change_promotion(string name);
    map<pair<int, int>, set<pair<int, int>>> legal_moves();

    bool make_move(pair<int, int> from, pair<int, int> to);
    void undo_move();
    
    bool occupied(pair<int, int> pos);
    string picture_name(int x, int y);

};

#endif