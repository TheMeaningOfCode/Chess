#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <set>

using namespace std;

class ChessBoard;

class Piece {
  protected:
  public:
    int x;
    int y;
    string color;
    int move_count = 0;

    Piece();
    Piece(int i, int j);
    Piece(int i, int j, string cl);
    virtual ~Piece();
    void update_pos(pair<int, int> location);
    const string & get_color() const;
    
    virtual int get_value() = 0;
    virtual string get_name() = 0;
    virtual set<pair<int, int>> move(const ChessBoard* board) = 0;
};

#endif
