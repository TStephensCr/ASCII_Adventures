#include <ncurses.h>
#include "Game_constants.hpp"
#include "Position.hpp"
#include "Player.hpp"
#include "Entities_structure.hpp"
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
   //----Entity-info functions----//
   char Character(EntityType Type);
   int yLoc(ens Entity);
   int xLoc(ens Entity);

   //----Player stats display functions----//
   void ClearPlayerStatsDisplay(int maxX);
   void DisplayHealth(int maxX);
   void DisplayShield();
   void DisplayPlayerInfo();

public:
   //----Constructor----//
   Entities(WINDOW *win);

   //----Return Functions----//
   WINDOW *ReturnCurwin();
   ens ReturnPlayerPointer();
   Player *ReturnPlayerOBJ();
   ens ReturnList();

   //----Entity Management----//
   ens Insert(EntityType tipo, int x, int y, int map, int level);
   ens EntitiesInLocation(MyPosition Loc, int mappa, int livello);
   bool isValidEntity(ens entity, MyPosition Loc, int mappa, int livello);
   void Display(ens MyEntity);
   void ClearPosition(ens Entity);
   void KillEntity(ens Entity);
   void MoveEntity(ens myEntity);
   bool SameDir(ens Entity, ens Entity2);
   void DeleteEntities();
   void RemoveDeadEntities();

   //----Visual Effects and Player Stats----//
   void explosionEffect(ens entity);
   void DisplayPlayerStats();
   void inflictDamageToPlayer(int damage);
   void moneyGrabberEffect(ens Money);
};