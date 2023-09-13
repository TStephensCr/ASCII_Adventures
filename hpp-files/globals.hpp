#define CHARACTER '@'
#define ENEMY '&'
#define MONEY '*'
#define SHOOT '-'
#define HORIZONTAL_WALL '='
#define VERTICAL_WALL '|'
#define FULLFILL_POINT '.'
#define POWERUP 'P'
#define PLAYERLIFES 3
#define X_PLAYERSPAWN 3
#define Y_PLAYERSPAWN 4
#define JUMPHEIGHT 12
#define NAPTIME 30


enum EntityType { player, enemy, money, shoot, powerup };

struct entita {
  EntityType type;
  Position* pos = new Position();
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  entita* next;
};
typedef entita* ens;  // e = entit�, n = nello , s = spazio

enum GameStatus { MenU, Game };