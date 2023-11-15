#include "hpp-files/Entities.hpp"

Entities::Entities(WINDOW *win)
{
  curwin = win;
  keypad(curwin, true);
  getmaxyx(curwin, yMax, xMax);
}

WINDOW *Entities::ReturnCurwin() { return curwin; }

ens Entities::ReturnPlayerPointer() { return PlayerPointer; }

Player *Entities::ReturnPlayerOBJ() { return InfoPlayer; }

ens Entities::Insert(EntityType Type, int x, int y, int map = 1, int level = 0)
{
  if (Character(Type) != '?')
  {
    ens tmp = new entita;
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
  return NULL;
}

ens Entities::EntitiesInLocation(MyPosition Loc, int mappa, int livello)
{
  ens entity = entities;
  ens Entity_founded = NULL;
  bool Trovato = false;
  while (entity && !Trovato)
  {
    if (!entity->death_flag &&
        xLoc(entity) == Loc.x &&
        yLoc(entity) == Loc.y &&
        (entity->mappa == mappa) && (entity->livello == livello))
    {
      Entity_founded = entity;
      Trovato = true;
    }
    else
    {
      entity = entity->next; // Avanza nell'elenco principale
    }
  }
  if (Trovato)
    return Entity_founded;
  else
    return NULL;
}

ens Entities::ReturnList() { return entities; }

void Entities::Display(ens MyEntity)
{
  if (MyEntity && !MyEntity->death_flag)
  {
    wattron(curwin, COLOR_PAIR(MyEntity->type + 1));
    mvwaddch(curwin, yLoc(MyEntity), xLoc(MyEntity), Character(MyEntity->type));
    wattroff(curwin, COLOR_PAIR(MyEntity->type + 1));
  }
}

void Entities::ClearPosition(ens Entity)
{
  if (Entity)
    mvwaddch(curwin, yLoc(Entity), xLoc(Entity), ' ');
}

void Entities::MoveEntity(ens myEntity)
{
  int xForce = myEntity->xForce;
  int yForce = myEntity->yForce;
  if (myEntity)
  {
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
}

void Entities::KillEntity(ens Entity)
{
  if (Entity->type != player)
  {
    Entity->death_flag = true;
    ClearPosition(Entity);
  }
}

bool Entities::SameDir(ens Entity1, ens Entity2)
{
  if ((Entity1->xForce > 0) == (Entity2->xForce > 0))
    return true;
  else
    return false;
}

void Entities::DeleteEntities()
{
  entities = NULL;
}

void Entities::RemoveDeadEntities()
{
  ens currentEntity = entities;
  ens prevEntity = NULL;

  while (currentEntity)
  {
    if (currentEntity->death_flag && currentEntity->type != player)
    {
      // Remove the entity with death_flag set to true
      if (prevEntity)
      {
        prevEntity->next = currentEntity->next;
        delete currentEntity;
        currentEntity = prevEntity->next;
      }
      else
      {
        // If the first entity has death_flag set to true
        entities = currentEntity->next;
        delete currentEntity;
        currentEntity = entities;
      }
    }
    else
    {
      // Move to the next entity
      prevEntity = currentEntity;
      currentEntity = currentEntity->next;
    }
  }
}

void Entities::explosionEffect(ens entity)
{
  init_pair(1, COLOR_RED, COLOR_BLACK);

  chtype redCell = ' ' | COLOR_PAIR(1);

  int x = xLoc(entity);
  int y = yLoc(entity);

  for (int dx = -1; dx <= 1; dx++)
  {
    for (int dy = -1; dy <= 1; dy++)
    {
      if (dx == 0 and dy == 0)
        continue;

      int nearX = x + dx;
      int nearY = y + dy;

      mvwaddch(curwin, nearY, nearX, redCell);
    }
  }
  wattroff(curwin, COLOR_PAIR(1));
}

void Entities::DisplayPlayerStats()
{
  int maxX = getmaxx(curwin);

  if (InfoPlayer)
  {
    ClearPlayerStatsDisplay(maxX);
    DisplayHealth(maxX);
    DisplayShield();
    DisplayPlayerInfo();
  }
}

void Entities::inflictDamageToPlayer(int damage)
{
  if (InfoPlayer)
  {
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
}
