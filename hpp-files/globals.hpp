#define CHARACTER '@'
#define ENEMY '&'
#define MONEY '0'
#define SHOOT '-'
#define POWERUP 'P'
#define HORIZONTAL_WALL '='
#define VERTICAL_WALL '|'
#define FULLFILL_POINT '.'
#define POWERUP 'P'
#define PLAYERLIFES 3
#define X_PLAYERSPAWN 2
#define Y_PLAYERSPAWN 12
#define JUMPHEIGHT 12
#define NAPTIME 30


enum EntityType { player, enemy, money, shoot, powerup };

struct entita {
  EntityType type;
  Position* pos = new Position();
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  int mappa = -1;
  entita* next;
};
typedef entita* ens;  // e = entit�, n = nello , s = spazio

enum GameStatus { MenU, Game };