#include <ncurses.h>
#include "Player.hpp"
#include "Position.hpp"
#include "globals.hpp"

class Entities {
 protected:
  ens entities = NULL;  // lista entit�

  Player* InfoPlayer = NULL;

  ens PlayerPointer = NULL;

  WINDOW* curwin;  // window in cui verrano stampate le entit�

  int yMax, xMax;

 public:
  // Blocco Azione su liste di entit�
  Entities(WINDOW* win);  // costruttore

  WINDOW* ReturnCurwin();

  ens Insert(EntityType tipo, int x,
             int y);  // inserisce un'entità in base al tipo [ EntityType ] and
                      // his position coordinates [ x , y ]

  char Character(EntityType Type);  // Given a EntityType return the char that
                                    // will show up in the game

  ens EntityInLocation(
      MyPosition Loc);  // Given a position returns the entity in that position
                        // otherwise returns NULL

  void Remove(ens Entity); //SE FAI entita->Remove(j); RICORDA DI METTERE j == NULL.altrimenti 
                           //di da segmentation fault se fai entita->Display(j); per es.

  void RemovePlayer();

  ens SpawnPlayer();

  ens ReturnPlayerPointer();

  Player* ReturnPlayerOBJ();

  ens ReturnList();

  int yLoc(ens Entity);

  int xLoc(ens Entity);

  void Display(ens MyEntity);

  void ClearPosition(ens Entity);

  bool OutOfBoundary(ens Entity);

  void DecreaseForce(ens myEntity);

  void MoveEntity(ens myEntity);
  
};
