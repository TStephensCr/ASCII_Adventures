#include "hpp-files/Position.hpp"

Position::Position() {
  MyPosition EntityPosition;
}

void Position::Move(int xDir, int yDir) {
  EntityPosition.x += xDir;
  EntityPosition.y += yDir;
}

void Position::SelectPosition(int x, int y) {
  EntityPosition.x = x;
  EntityPosition.y = y;
}

MyPosition Position::ReturnPos() { return EntityPosition; };