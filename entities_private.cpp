#include "hpp-files/Entities.hpp"

void Entities::Remove(ens entityToRemove) {
  if (entities == entityToRemove) {
    ens nextEntity = entities->next;
    delete entities;
    entities = nextEntity;
    return;
  }

  ens currentEntity = entities;
  while (currentEntity->next != NULL) {
    if (currentEntity->next == entityToRemove) {
      ens nextEntity = currentEntity->next->next;
      delete currentEntity->next;
      currentEntity->next = nextEntity;
      return;
    }
    currentEntity = currentEntity->next;
  }
}

char Entities::Character(EntityType type) {
  switch (type) {
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
    default:
      return '?';
  }
}

int Entities::yLoc(ens entity) { 
  return entity->pos->ReturnPos().y; 
}

int Entities::xLoc(ens entity) { 
  return entity->pos->ReturnPos().x; 
}
