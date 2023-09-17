#include "hpp-files/Entities.hpp"

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