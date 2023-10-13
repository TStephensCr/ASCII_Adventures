#include "hpp-files/Collision.hpp"

void Collision::UpdateVariables(){
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	InfoPlayer    = entitiesOBJ->ReturnPlayerOBJ();
}

void Collision::HandleVerticalCollision(ens Entity, int xPos, int& yPos, int mappa, int livello)
{
    if (Entity->yForce != 0) {
        int c = (Entity->yForce < 0) ? yPos - 1 : yPos + 1;
        char charAboveOrBelow = mvwinch(curwin, c, xPos);
        MyPosition newP;
        newP.x = xPos;
        newP.y = c;
        ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, mappa, livello);

        if (charAboveOrBelow == HORIZONTAL_WALL || charAboveOrBelow == VERTICAL_WALL || charAboveOrBelow == FULLFILL_POINT) {
            Entity->yForce = 0;
        }
        else if (Entity_in_new_loc && !Entity_in_new_loc->death_flag) {
            HandleEntityCollision(Entity, Entity_in_new_loc);
            yPos = c;
        }
        else {
            yPos = c;
        }
    }
}

void Collision::HandleHorizontalCollision(ens Entity, int& xPos, int yPos, int mappa, int livello)
{
    if (Entity->xForce != 0) {
        xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
        char charAtNewPos = mvwinch(curwin, yPos, xPos);
        MyPosition newP;
        newP.x = xPos;
        newP.y = yPos;
        ens Entity_in_new_loc = entitiesOBJ->EntitiesInLocation(newP, mappa, livello);

        if (charAtNewPos == HORIZONTAL_WALL || charAtNewPos == VERTICAL_WALL || charAtNewPos == FULLFILL_POINT) {
            if (Entity->type == shoot)
                Entity->death_flag = true;
            else
                Entity->xForce = 0;
        }
        else if (Entity_in_new_loc && !Entity_in_new_loc->death_flag) {
            HandleEntityCollision(Entity, Entity_in_new_loc);
        }
    }
}

void Collision::HandleEntityCollision(ens Entity, ens OtherEntity)
{
    if (Entity->type == player && OtherEntity->type == money) {
        OtherEntity->death_flag = true;
        entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
    }
    else if (Entity->type == enemy && OtherEntity->type == player) {
        HandleEnemyPlayerCollision(Entity, OtherEntity);
    }
    else if (Entity->type == player && OtherEntity->type == enemy) {
        HandlePlayerEnemyCollision(Entity, OtherEntity);
    }
    else if ((Entity->type == shoot && OtherEntity->type == enemy) || (Entity->type == enemy && OtherEntity->type == shoot)) {
        OtherEntity->death_flag = true;
        Entity->death_flag = true;
        entitiesOBJ->ClearPosition(OtherEntity);
        entitiesOBJ->ClearPosition(Entity);
        entitiesOBJ->ReturnPlayerOBJ()->points += KILL_ENEMYS_POINTS;
    }
    else if (Entity->type == player && OtherEntity->type == powerup) {
        OtherEntity->death_flag = true;
        entitiesOBJ->ReturnPlayerOBJ()->hp = 100;
    }
    else if ((Entity->type == shoot && OtherEntity->type == player) || (Entity->type == player && OtherEntity->type == shoot)) {
        if(OtherEntity->type == shoot)
            OtherEntity->death_flag = true;
        if(Entity->type == shoot)
            Entity->death_flag = true;
        InfoPlayer->hp -= 20;
        PlayerPointer->pos->SelectPosition(X_PLAYERSPAWN,Y_PLAYERSPAWN);
    }
}

void Collision::HandleEnemyPlayerCollision(ens Enemy, ens Player)
{
    if (Enemy->xForce >= 1)
        Player->xForce = 1 * REPELLING_FORCE_OF_ENEMYS;
    else
        Player->xForce = -1 * REPELLING_FORCE_OF_ENEMYS;

    Player->yForce = -10;//lo fa saltare in alto

    InfoPlayer->hp -= 20;
}


void Collision::HandlePlayerEnemyCollision(ens Player, ens Enemy)
{
    if(InfoPlayer->LastMovement == 'd'){
        Player->xForce = -10; Player->yForce = -10;
    }
    else{
        Player->xForce = 10; Player->yForce = -10;
    }
    InfoPlayer->hp -= 20;
}
