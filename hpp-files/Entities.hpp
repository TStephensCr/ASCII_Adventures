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

 private:
    char Character(EntityType Type); 

    void Remove(ens Entity); //SE FAI entita->Remove(j); RICORDA DI METTERE j == NULL.altrimenti

    int yLoc(ens Entity);

    int xLoc(ens Entity); 
 public:
  // Blocco Azione su liste di entit�
  Entities(WINDOW* win);  // costruttore

  WINDOW* ReturnCurwin();

  ens Insert(EntityType tipo, int x,
             int y);  // inserisce un'entità in base al tipo [ EntityType ] and
                      // his position coordinates [ x , y ]


  ens EntitiesInLocation(
      MyPosition Loc, int mappa, int livello);  // Given a position returns the entity in that position
                        // otherwise returns NULL

  ens ReturnPlayerPointer();

  Player* ReturnPlayerOBJ();

  ens ReturnList();

  void Display(ens MyEntity);

  void ClearPosition(ens Entity);

  void MoveEntity(ens myEntity);
  
};