#include "hpp-files/Position.hpp"

Position::Position() {
  MyPosition Pos;
  EntityPosition = Pos;
}

void Position::Move(int xDir, int yDir) {
  MyPosition MyPos;
  EntityPosition.x += xDir;
  EntityPosition.y += yDir;
}

void Position::SelectPosition(int x, int y) {
  MyPosition MyPos;
  MyPos.x = x;
  MyPos.y = y;
  EntityPosition = MyPos;
}

MyPosition Position::ReturnPos() { return EntityPosition; };