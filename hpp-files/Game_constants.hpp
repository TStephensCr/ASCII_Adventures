#define CHARACTER '@'
#define ENEMY '&'
#define MONEY 'o'
#define SHOOT '-'
#define POWERUP 'H'
#define SPACE ' '
#define HORIZONTAL_WALL '='
#define VERTICAL_WALL '|'
#define FULLFILL_POINT '.'
#define FOLLOWER 'F'

#define PLAYERLIFES 3
#define X_PLAYERSPAWN 2
#define Y_PLAYERSPAWN 12
#define JUMPHEIGHT 12

#define NAPTIME 40
#define FOLLOWER_DELAY 40
#define KILL_ENEMYS_POINTS 20
#define KILL_FOLLOWER_POINTS 20
#define FOLLOWER_DAMAGE 40
#define FALL_DAMAGE 20
#define SHOOT_DAMAGE 20
#define PLAYER_ENEMY_COLLISION_DAMAGE 20
#define REPELLING_XFORCE_OF_ENEMYS 10
#define REPELLING_YFORCE_OF_ENEMYS -10
#define MAX_BULLET_RANGE 200
#define PLAYER_MAX_HP 100

#define PLAYER_COLOR 1
#define ENEMY_COLOR 2
#define MONEY_COLOR 3
#define SHOOT_COLOR 4
#define POWERUP_COLOR 5
#define FOLLOWER_COLOR 6
#define SHIELD_COLOR 7

#define ESC_KEY 27

#define STATS_DISTANCE_FROM_RIGHT 32

#define DAMAGE_SCALE_FACTOR 2

enum menuChoice
{
    NewGame,
    LoadGame,
    Shop,
    Exit
};

enum EntityType
{
    player,
    enemy,
    money,
    shoot,
    powerup,
    follower
};

enum GameStatus
{
    MenU,
    Running,
    Shopping
};
