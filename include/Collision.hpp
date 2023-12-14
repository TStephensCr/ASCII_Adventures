#pragma once
#include "Events.hpp"

class Collision
{
protected:
    Entities *entitiesOBJ;

    WINDOW *curwin;

    entita_p ListOfEntities;

    entita_p PlayerPointer = NULL;

    Player *InfoPlayer;

    int difficulty = 1;

private:
    //----Update functions----//
    void UpdateVariables();
    //----Collision handling functions----//
    void handleCollisions(entita_p Entity);

    void HandleVerticalCollision(entita_p Entity, int xPos, int &yPos);
    void HandleHorizontalCollision(entita_p Entity, int xPos, int yPos);

    void handleVerticalMapCollision(entita_p Entity);
    void handleHorizontalMapCollision(entita_p Entity);

    void HandleEntityCollision(entita_p Entity, entita_p OtherEntity);

    void HandleEnemyPlayerCollision(entita_p Enemy);
    void HandlePlayerEnemyCollision();
    void HandlePlayerCollision(entita_p CollidingEntity);
    void HandleEnemyCollision(entita_p Entity, entita_p CollidingEntity);
    void HandleShootCollision(entita_p Entity, entita_p CollidingEntity);
    void HandleFollowerCollision(entita_p Entity, entita_p CollidingEntity);
    //----Condition checking functions----//
    bool isMapCollision(char charAtNewPos);
    bool isPossibleEntitiesCollision(entita_p Entity, entita_p CollidingEntity);
    bool checkExistenceOfEntity(entita_p Entity);
    //----get info functions----//
    entita_p getCollidingEntity(entita_p Entity, int entityNextX, int entityNextY);

public:
    //----Constructor----//
    Collision(Entities *MyEntities);

    //----set functions----//

    void setDifficulty(int newDifficulty);

    //----Collision management functions----//
    void ManageJump(entita_p Entity);
    void OutOfBounds(entita_p Entity);
    void ManageCollisions(entita_p Entity);
};