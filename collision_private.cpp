#include "hpp-files/Collision.hpp"

void Collision::UpdateVariables(){
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	InfoPlayer    = entitiesOBJ->ReturnPlayerOBJ();
}

void Collision::HandleVerticalCollision(ens Entity, int xPos, int& yPos)
{
    if (Entity->yForce != 0) {
        int  dir = (Entity->yForce < 0) ? - 1 : 1;
        char charAboveOrBelow = mvwinch(curwin, yPos + dir, xPos);

        MyPosition newP;
        newP.Select(xPos, yPos + dir);

        ens EntityInNewLoc = entitiesOBJ->EntitiesInLocation(newP, Entity->mappa, Entity->livello);

        if (charAboveOrBelow == HORIZONTAL_WALL || charAboveOrBelow == VERTICAL_WALL || charAboveOrBelow == FULLFILL_POINT) {
            Entity->yForce = 0;
            return;
        }
        else if (EntityInNewLoc && !EntityInNewLoc->death_flag){
            HandleEntityCollision(Entity, EntityInNewLoc);
        }
        
        yPos = yPos + dir;
    }
}

void Collision::HandleHorizontalCollision(ens Entity, int& xPos, int yPos)
{
    if (Entity->xForce != 0) {
        xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
        char charAtNewPos = mvwinch(curwin, yPos, xPos);

        MyPosition newP;
        newP.Select(xPos, yPos);

        ens EntityInNewLoc = entitiesOBJ->EntitiesInLocation(newP, Entity->mappa, Entity->livello);

        if (charAtNewPos == HORIZONTAL_WALL || charAtNewPos == VERTICAL_WALL || charAtNewPos == FULLFILL_POINT) {
            if (Entity->type == shoot)
                entitiesOBJ->KillEntity(Entity);
            else
                Entity->xForce = 0;
        }
        else if (EntityInNewLoc && !EntityInNewLoc->death_flag && (!entitiesOBJ->SameDir(Entity, EntityInNewLoc) ||
            EntityInNewLoc->xForce == 0)) {
            HandleEntityCollision(Entity, EntityInNewLoc);
        }
    }
}

void Collision::HandleEntityCollision(ens Entity, ens CollidingEntity)
{
    if(PlayerPointer && InfoPlayer){
        if (Entity->type == player && CollidingEntity->type == money) {
            entitiesOBJ->KillEntity(CollidingEntity);
            entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
        }
        else if (Entity->type == enemy && CollidingEntity->type == player) {
            HandleEnemyPlayerCollision(CollidingEntity);
        }
        else if (Entity->type == player && CollidingEntity->type == enemy) {
            HandlePlayerEnemyCollision();
        }
        else if ((Entity->type == shoot && CollidingEntity->type == enemy) || (Entity->type == enemy && CollidingEntity->type == shoot)) {
            entitiesOBJ->KillEntity(CollidingEntity);    
            entitiesOBJ->KillEntity(Entity);
            entitiesOBJ->ReturnPlayerOBJ()->points += KILL_ENEMYS_POINTS;
        }
        else if (Entity->type == player && CollidingEntity->type == powerup) {
            entitiesOBJ->KillEntity(CollidingEntity); 
            entitiesOBJ->ReturnPlayerOBJ()->hp = 100;
        }
        else if ((Entity->type == shoot && CollidingEntity->type == player) || (Entity->type == player && CollidingEntity->type == shoot)) {
            if(CollidingEntity->type == shoot)
                entitiesOBJ->KillEntity(CollidingEntity); 
            if(Entity->type == shoot)
                entitiesOBJ->KillEntity(Entity);
            InfoPlayer->hp -= SHOOT_DAMAGE;
            PlayerPointer->pos.Select(X_PLAYERSPAWN,Y_PLAYERSPAWN);
        }
        else if((Entity->type == follower && CollidingEntity->type == player) || (Entity->type == player && CollidingEntity->type == follower)){
            if(CollidingEntity->type == follower)
                entitiesOBJ->KillEntity(CollidingEntity); 
            if(Entity->type == follower)
                entitiesOBJ->KillEntity(Entity);
            entitiesOBJ->ReturnPlayerOBJ()->hp -= FOLLOWER_DAMAGE;
        }
        else if((Entity->type == follower && CollidingEntity->type == shoot) || (Entity->type == shoot && CollidingEntity->type == follower)){
            entitiesOBJ->KillEntity(CollidingEntity);    
            entitiesOBJ->KillEntity(Entity);
            entitiesOBJ->ReturnPlayerOBJ()->points += KILL_FOLLOWER_POINTS;
        }
    }
}

void Collision::HandleEnemyPlayerCollision(ens Enemy)
{
    if (Enemy->xForce >= 1)
        PlayerPointer->xForce = 1 * REPELLING_XFORCE_OF_ENEMYS;
    else
        PlayerPointer->xForce = -1 * REPELLING_XFORCE_OF_ENEMYS;

    PlayerPointer->yForce = REPELLING_YFORCE_OF_ENEMYS;

    InfoPlayer->hp -= PLAYER_ENEMY_COLLISION_DAMAGE;
}


void Collision::HandlePlayerEnemyCollision()
{
    if(InfoPlayer->LastMovement == 'd')
        PlayerPointer->xForce = 1 * REPELLING_XFORCE_OF_ENEMYS;
    else
        PlayerPointer->xForce = -1 * REPELLING_XFORCE_OF_ENEMYS;

    PlayerPointer->yForce = REPELLING_YFORCE_OF_ENEMYS;

    InfoPlayer->hp -= PLAYER_ENEMY_COLLISION_DAMAGE;
}
