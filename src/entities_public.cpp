#include "../include/Entities.hpp"

// ---- Constructor ---- //
Entities::Entities(WINDOW *win)
{
  curwin = win;
  keypad(curwin, true);
  getmaxyx(curwin, yMax, xMax);
}

// ---- Return Functions ---- //
WINDOW *Entities::ReturnCurwin() { return curwin; }

entita_p Entities::ReturnPlayerPointer() { return PlayerPointer; }

Player *Entities::ReturnPlayerOBJ() { return InfoPlayer; }

entita_p Entities::ReturnList() { return entities; }

// ---- Entity Management ---- //
entita_p Entities::Insert(EntityType Type, int x, int y, int map, int level)
{
  if (Character(Type) == '?')
    return NULL;

  entita_p tmp = new Entita;
  tmp->type = Type;
  tmp->pos.Select(x, y);
  tmp->next = entities;
  tmp->livello = level;
  tmp->mappa = map;
  entities = tmp;
  if (Type == player)
  {
    PlayerPointer = tmp;
    InfoPlayer = new Player;
  }
  return entities;
}

entita_p Entities::EntitiesInLocation(Position Loc, int mappa, int livello)
{
  entita_p currentEntity = entities;
  bool found = false;

  while (currentEntity && !found)
  {
    if (isValidEntity(currentEntity, Loc, mappa, livello))
    {
      found = true;
    }
    else
    {
      currentEntity = currentEntity->next;
    }
  }

  if (found)
  {
    return currentEntity;
  }
  else
  {
    return NULL;
  }
}

bool Entities::isValidEntity(entita_p entity, Position Loc, int mappa, int livello)
{
  return !entity->death_flag &&
         xLoc(entity) == Loc.x &&
         yLoc(entity) == Loc.y &&
         entity->mappa == mappa &&
         entity->livello == livello;
}

// ---- Display Functions ---- //
void Entities::Display(entita_p MyEntity)
{
  if (MyEntity && !MyEntity->death_flag)
  {
    wattron(curwin, COLOR_PAIR(MyEntity->type + 1));
    mvwaddch(curwin, yLoc(MyEntity), xLoc(MyEntity), Character(MyEntity->type));
    wattroff(curwin, COLOR_PAIR(MyEntity->type + 1));
  }
}

void Entities::ClearPosition(entita_p Entity)
{
  if (Entity)
    mvwaddch(curwin, yLoc(Entity), xLoc(Entity), ' ');
}

// ---- Movement and Deletion Functions ---- //
void Entities::MoveEntity(entita_p myEntity)
{
  if (!myEntity)
    return;

  int xForce = myEntity->xForce;
  int yForce = myEntity->yForce;

  if (yForce > 0)
  {
    myEntity->pos.Move(0, 1);
  }
  else if (yForce < 0)
  {
    myEntity->pos.Move(0, -1);
  }
  if (xForce > 0)
  {
    myEntity->pos.Move(1, 0);
  }
  else if (xForce < 0)
  {
    myEntity->pos.Move(-1, 0);
  }
}

void Entities::KillEntity(entita_p Entity)
{
  if (Entity->type != player)
  {
    Entity->death_flag = true;
    ClearPosition(Entity);
  }
}

bool Entities::SameDir(entita_p Entity1, entita_p Entity2)
{
  if ((Entity1->xForce > 0) == (Entity2->xForce > 0))
    return true;
  else
    return false;
}

void Entities::DeleteEntities()
{
  delete entities;
  entities = NULL;
}

void Entities::RemoveDeadEntities()
{
  entita_p currentEntity = entities;
  entita_p prevEntity = NULL;

  while (currentEntity)
  {
    if (currentEntity->death_flag && currentEntity->type != player)
    {
      if (prevEntity)
      {
        prevEntity->next = currentEntity->next;
        delete currentEntity;
        currentEntity = NULL;
        currentEntity = prevEntity->next;
      }
      else
      {
        entities = currentEntity->next;
        delete currentEntity;
        currentEntity = NULL;
        currentEntity = entities;
      }
    }
    else
    {
      prevEntity = currentEntity;
      currentEntity = currentEntity->next;
    }
  }
}

// ---- Visual Effects and Player Stats ---- //
void Entities::explosionEffect(entita_p entity)
{
  int x = xLoc(entity);
  int y = yLoc(entity);

  for (int radius = 1; radius <= 2; radius++)
  {
    init_pair(8, COLOR_RED, COLOR_YELLOW);
    wattron(curwin, COLOR_PAIR(8));

    for (int dx = -radius; dx <= radius; dx++)
    {
      for (int dy = (InfoPlayer->inJump) ? radius : 0; dy >= -radius; dy--)
      {
        int nearX = x + dx;
        int nearY = y + dy;

        if (dx * dx + dy * dy <= (radius * radius))
        {
          mvwaddch(curwin, nearY, nearX, ' ');
        }
      }
    }

    wattroff(curwin, COLOR_PAIR(8));
  }
}

void Entities::DisplayPlayerStats()
{
  if (!InfoPlayer)
    return;

  int maxX = getmaxx(curwin);

  ClearPlayerStatsDisplay(maxX);
  DisplayHealth(maxX);
  DisplayShield();
  DisplayPlayerInfo();
}

void Entities::inflictDamageToPlayer(int damage)
{
  if (!InfoPlayer)
    return;

  if (InfoPlayer->shield > 0)
  {
    InfoPlayer->shield -= damage;

    if (InfoPlayer->shield < 0)
    {
      InfoPlayer->shield = 0;
    }
  }
  else
  {
    InfoPlayer->hp -= damage;
  }
}

void Entities::moneyGrabberEffect(entita_p Money)
{
  init_pair(8, COLOR_YELLOW, COLOR_BLACK);
  wattron(curwin, COLOR_PAIR(8));

  mvwaddch(curwin, Money->pos.y - 2, Money->pos.x, MONEY);

  wattroff(curwin, COLOR_PAIR(8));
}
