struct MyPosition {
  int x = -1;
  int y = -1;

  void Move(int xDir, int yDir){
    x += xDir;
    y += yDir;
  }

  void Select(int newX, int newY){
    x = newX;
    y = newY;
  }
};
typedef MyPosition* pos;

