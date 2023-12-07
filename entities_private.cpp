#include "hpp-files/Entities.hpp"

char Entities::Character(EntityType type)
{
  switch (type)
  {
  case player:
    return CHARACTER;
    break;
  case enemy:
    return ENEMY;
    break;
  case money:
    return MONEY;
    break;
  case shoot:
    return SHOOT;
    break;
  case powerup:
    return POWERUP;
    break;
  case follower:
    return FOLLOWER;
    break;
  default:
    return '?';
    break;
  }
}

int Entities::yLoc(entita_p entity)
{
  return entity->pos.y;
}

int Entities::xLoc(entita_p entity)
{
  return entity->pos.x;
}

void Entities::ClearPlayerStatsDisplay(int maxX)
{
  for (int i = 2; i <= 6; i++)
  {
    mvwprintw(curwin, i, maxX - STATS_DISTANCE_FROM_RIGHT, "                          ");
  }
}

void Entities::DisplayHealth(int maxX)
{
  mvwprintw(curwin, 2, maxX - STATS_DISTANCE_FROM_RIGHT, "hp : ");
  int health = InfoPlayer->hp;
  int bars = health / 5;

  for (int i = 0; i < bars && i < 20; i++)
  {
    waddch(curwin, '/');
  }
}

void Entities::DisplayShield()
{
  if (InfoPlayer->shield > 0)
  {
    wattron(curwin, COLOR_PAIR(SHIELD_COLOR));
    int shield = InfoPlayer->shield;
    int shieldBars = shield / 5;

    for (int i = 0; i < shieldBars && i < 20; i++)
    {
      waddch(curwin, '/');
    }
    wattroff(curwin, COLOR_PAIR(SHIELD_COLOR));
  }
}

void Entities::DisplayPlayerInfo()
{
  int maxX = getmaxx(curwin);
  mvwprintw(curwin, 3, maxX - STATS_DISTANCE_FROM_RIGHT, "soldi : %d", InfoPlayer->Money);
  mvwprintw(curwin, 4, maxX - STATS_DISTANCE_FROM_RIGHT, "colpi : %d", InfoPlayer->colpi);
  mvwprintw(curwin, 5, maxX - STATS_DISTANCE_FROM_RIGHT, "punti : %d", InfoPlayer->points);

  if (InfoPlayer->LastMovement == 'd')
    mvwprintw(curwin, 6, maxX - STATS_DISTANCE_FROM_RIGHT, "last direction : -->");
  else
    mvwprintw(curwin, 6, maxX - STATS_DISTANCE_FROM_RIGHT, "last direction : <--");
}
