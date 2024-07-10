#include<cstdio>
#include<string>

#include"Piece.h"

using namespace std;

Piece::Piece() {}
Piece::Piece(int i, int j) {
  x = i;
  y = j;
}
Piece::Piece(int i, int j, string cl) {
  x = i;
  y = j;
  color = cl;
}
Piece::~Piece() {}

void Piece::update_pos(pair<int, int> location) {
  x = location.first;
  y = location.second;
}

const string& Piece::get_color() const {
  return color;
}
