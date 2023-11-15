#include <ncurses.h>
#include "Position.hpp"
#include "Player.hpp"
#include "globals.hpp"
#pragma once

class Entities
{
protected:
   ens entities = NULL; // lista entit�

   Player *InfoPlayer = NULL;

   ens PlayerPointer = NULL;

   WINDOW *curwin; // window in cui verrano stampate le entit�

   int yMax, xMax;

private:
   char Character(EntityType Type);

   void Remove(ens Entity);

   int yLoc(ens Entity);

   int xLoc(ens Entity);

   void ClearPlayerStatsDisplay(int maxX);

   void DisplayHealth(int maxX);

   void DisplayShield();

   void DisplayPlayerInfo();

public:
   // Blocco Azione su liste di entit�
   Entities(WINDOW *win); // costruttore

   WINDOW *ReturnCurwin();

   ens Insert(EntityType tipo, int x,
              int y, int map, int level); // inserisce un'entità in base al tipo [ EntityType ] and
                                          // his position coordinates [ x , y ]

   ens EntitiesInLocation(
       MyPosition Loc, int mappa, int livello); // Given a position returns the entity in that position
                                                // otherwise returns NULL

   ens ReturnPlayerPointer();

   Player *ReturnPlayerOBJ();

   ens ReturnList();

   void Display(ens MyEntity);

   void ClearPosition(ens Entity);

   void KillEntity(ens Entity);

   void MoveEntity(ens myEntity);

   bool SameDir(ens Entity, ens Entity2);

   void DeleteEntities();

   void RemoveDeadEntities();

   void explosionEffect(ens entity);

   void DisplayPlayerStats();

   void inflictDamageToPlayer(int damage);
};