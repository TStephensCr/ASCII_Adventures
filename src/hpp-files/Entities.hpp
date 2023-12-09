#include <ncurses.h>
#include "Game_constants.hpp"
#include "Player.hpp"
#include "Entities_structure.hpp"
#pragma once

class Entities
{
protected:
   entita_p entities = NULL; // lista entit�

   Player *InfoPlayer = NULL;

   entita_p PlayerPointer = NULL;

   WINDOW *curwin; // window in cui verrano stampate le entit�

   int yMax, xMax;

private:
   //----Entity-info functions----//
   char Character(EntityType Type);
   int yLoc(entita_p Entity);
   int xLoc(entita_p Entity);

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
   entita_p ReturnPlayerPointer();
   Player *ReturnPlayerOBJ();
   entita_p ReturnList();

   //----Entity Management----//
   entita_p Insert(EntityType tipo, int x, int y, int map, int level);
   entita_p EntitiesInLocation(Position Loc, int mappa, int livello);
   bool isValidEntity(entita_p entity, Position Loc, int mappa, int livello);
   void Display(entita_p MyEntity);
   void ClearPosition(entita_p Entity);
   void KillEntity(entita_p Entity);
   void MoveEntity(entita_p myEntity);
   bool SameDir(entita_p Entity, entita_p Entity2);
   void DeleteEntities();
   void RemoveDeadEntities();

   //----Visual Effects and Player Stats----//
   void explosionEffect(entita_p entity);
   void DisplayPlayerStats();
   void inflictDamageToPlayer(int damage);
   void moneyGrabberEffect(entita_p Money);
};