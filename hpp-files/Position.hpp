struct MyPosition {
  int x = -1;
  int y = -1;
};
typedef MyPosition* pos;

class Position {
 protected:
  MyPosition EntityPosition;

 public:
  Position();

  void Move(int xDir, int yDir);  // data una direzione ti restituisce la
                                  // posizione in cui Andrebbe

  void SelectPosition(int x, int y);  // cambia la posizione

  MyPosition ReturnPos();
};

