#define CHARACTER '@'
#define ENEMY '&'
#define MONEY '0'
#define SHOOT '-'
#define POWERUP 'H'
#define HORIZONTAL_WALL '='
#define VERTICAL_WALL '|'
#define FULLFILL_POINT '.'
#define POWERUP 'P'
#define PLAYERLIFES 3
#define X_PLAYERSPAWN 2
#define Y_PLAYERSPAWN 12
#define JUMPHEIGHT 12
#define NAPTIME 30
#define KILL_ENEMYS_POINTS 20
#define FALL_DAMAGE 20
#define SHOOT_DAMAGE 20
#define PLAYER_ENEMY_COLLISION_DAMAGE 20
#define REPELLING_XFORCE_OF_ENEMYS 10
#define REPELLING_YFORCE_OF_ENEMYS -10

enum EntityType { player, enemy, money, shoot, powerup };

struct entita {
  EntityType type;
  Position* pos = new Position();
  int xForce = 0;
  int yForce = 0;
  bool death_flag = false;
  int mappa = -1;
  int livello = -1;
  entita* next;
};
typedef entita* ens;  // e = entit�, n = nello , s = spazio

enum GameStatus { MenU, Game };