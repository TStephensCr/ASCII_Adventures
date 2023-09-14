#include "hpp-files/Entities.hpp"

Entities::Entities(WINDOW* win) {
  curwin = win;
  keypad(curwin, true);
  getmaxyx(curwin, yMax, xMax);
}

WINDOW* Entities::ReturnCurwin() { return curwin; }

ens Entities::Insert(EntityType Type, int x, int y) {
  if (Character(Type) != '?') {
    ens tmp = new entita;
    tmp->type = Type;
    tmp->pos->SelectPosition(x, y);
    tmp->next = entities;
    entities = tmp;
	if(Type == player){
		PlayerPointer = tmp;
    InfoPlayer = new Player;
	}
    return entities;
  }
  return NULL;
}

void Entities::Remove(ens Entity) {
  if (entities != NULL) {
    // Se l'elemento da eliminare è il primo della lista
    if (entities == Entity) {
      ens TmpNext = entities;
      entities = entities->next;
      delete TmpNext;
      TmpNext = NULL; // Set the pointer to NULL after deletion
      return;
    }

    // Scorri la lista per trovare l'elemento da eliminare
    ens tmp = entities;
    while (tmp->next != NULL) {
      if (tmp->next == Entity) {
        ens TmpNext = tmp->next;
        tmp->next = tmp->next->next;
        delete TmpNext;
        TmpNext = NULL; // Set the pointer to NULL after deletion
        return;
      }
      tmp = tmp->next;
    }
  }
}

bool Entities::OutOfBoundary(ens Entity) {
    int x, y;
    getmaxyx(curwin, y, x);
    
    if (xLoc(Entity) < 0 || xLoc(Entity) >= x || yLoc(Entity) < 0 || yLoc(Entity) >= y) {
        return true;  // Entity is out of boundary
    }
    
    return false;  // Entity is within boundary
}

void Entities::RemovePlayer(){  Remove(PlayerPointer); }


ens Entities::ReturnPlayerPointer() {	return PlayerPointer; }

Player *Entities::ReturnPlayerOBJ() { return InfoPlayer; }

ens Entities::SpawnPlayer(){
    return Insert(player, X_PLAYERSPAWN, Y_PLAYERSPAWN);
}

int Entities::GetPlayerLives(){
    if(InfoPlayer){
        return InfoPlayer->hp;
    }else{
      return -1;
    }
}

ens Entities::EntitiesInLocation(MyPosition Loc) {
    ens entity = entities;
    ens Entity_founded = NULL;
    bool Trovato = false;
    while (entity && !Trovato) {
        if (xLoc(entity) == Loc.x && yLoc(entity) == Loc.y) {
            Entity_founded = entity;
            Trovato = true;
        } else {
            entity = entity->next;  // Avanza nell'elenco principale
        }
    }
    if(Trovato)
      return Entity_founded;
    else 
      return NULL;
}


char Entities::Character(EntityType Type) {
  switch (Type) {
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
    default:
      return '?';
      break;
  }
}

int Entities::yLoc(ens Entity) { return Entity->pos->ReturnPos().y; }

int Entities::xLoc(ens Entity) { return Entity->pos->ReturnPos().x; }

void Entities::Display(ens MyEntity) {
  if (MyEntity && !MyEntity->death_flag) {
    mvwaddch(curwin, yLoc(MyEntity), xLoc(MyEntity), Character(MyEntity->type));
  }
}

ens Entities::ReturnList() { return entities; }

void Entities::ClearPosition(ens Entity) {
  if(Entity)
    mvwaddch(curwin, yLoc(Entity), xLoc(Entity), ' ');
}

void Entities::MoveEntity(ens myEntity) {
    int xForce = myEntity->xForce;
    int yForce = myEntity->yForce;
    if(myEntity){
        if(yForce > 0){
          myEntity->pos->Move(0,1);
        }    
        else if(yForce < 0){
          myEntity->pos->Move(0,-1);
        }
        if(xForce > 0){
          myEntity->pos->Move(1,0);
        }    
        else if(xForce < 0){
          myEntity->pos->Move(-1,0);
        }
    }
    
}


void Entities::DecreaseForce(ens myEntity) {
	if(myEntity){
		if (myEntity->xForce <= -1)myEntity->xForce++;
		if (myEntity->xForce >= 1)myEntity->xForce--;
		if (myEntity->yForce <= -1)myEntity->yForce++;
		if (myEntity->yForce >= 1)myEntity->yForce--;
	}
}