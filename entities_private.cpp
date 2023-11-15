#include "hpp-files/Entities.hpp"

void Entities::Remove(ens entityToRemove)
{
  if (entities == entityToRemove)
  {
    ens nextEntity = entities->next;
    delete entities;
    entities = nextEntity;
    return;
  }

  ens currentEntity = entities;
  while (currentEntity->next != NULL)
  {
    if (currentEntity->next == entityToRemove)
    {
      ens nextEntity = currentEntity->next->next;
      delete currentEntity->next;
      currentEntity->next = nextEntity;
      return;
    }
    currentEntity = currentEntity->next;
  }
}

char Entities::Character(EntityType type)
{
  switch (type)
  {
  case player:
    return CHARACTER;
  case enemy:
    return ENEMY;
  case money:
    return MONEY;
  case shoot:
    return SHOOT;
  case powerup:
    return POWERUP;
  case follower:
    return FOLLOWER;
  default:
    return '?';
  }
}

int Entities::yLoc(ens entity)
{
  return entity->pos.y;
}

int Entities::xLoc(ens entity)
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
