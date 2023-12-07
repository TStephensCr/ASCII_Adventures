#include "hpp-files/Collision.hpp"

//----Update functions----//

void Collision::UpdateVariables()
{
    PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
}

//----Collision handling functions----//

void Collision::HandleVerticalCollision(ens Entity, int xPos, int &yPos)
{
    if (Entity->yForce != 0)
    {
        int dir = (Entity->yForce < 0) ? -1 : 1;
        char charAboveOrBelow = mvwinch(curwin, yPos + dir, xPos);

        Position newP;
        newP.Select(xPos, yPos + dir);

        ens EntityInNewLoc = entitiesOBJ->EntitiesInLocation(newP, Entity->mappa, Entity->livello);

        if (charAboveOrBelow == HORIZONTAL_WALL || charAboveOrBelow == VERTICAL_WALL || charAboveOrBelow == FULLFILL_POINT)
        {
            Entity->yForce = 0;
            return;
        }
        else if (EntityInNewLoc && !EntityInNewLoc->death_flag)
        {
            HandleEntityCollision(Entity, EntityInNewLoc);
        }

        yPos = yPos + dir;
    }
}

void Collision::HandleHorizontalCollision(ens Entity, int xPos, int yPos)
{
    if (Entity->xForce != 0)
    {
        xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
        char charAtNewPos = mvwinch(curwin, yPos, xPos);

        Position newP;
        newP.Select(xPos, yPos);

        ens EntityInNewLoc = entitiesOBJ->EntitiesInLocation(newP, Entity->mappa, Entity->livello);

        if (charAtNewPos == HORIZONTAL_WALL || charAtNewPos == VERTICAL_WALL || charAtNewPos == FULLFILL_POINT)
        {
            if (Entity->type == shoot)
                entitiesOBJ->KillEntity(Entity);
            else
                Entity->xForce = 0;
        }
        else if (EntityInNewLoc && !EntityInNewLoc->death_flag && (!entitiesOBJ->SameDir(Entity, EntityInNewLoc) || EntityInNewLoc->xForce == 0))
        {
            HandleEntityCollision(Entity, EntityInNewLoc);
        }
    }
}

void Collision::HandleEntityCollision(ens Entity, ens CollidingEntity)
{
    if (!PlayerPointer || !InfoPlayer)
    {
        return;
    }

    switch (Entity->type)
    {
    case player:
        HandlePlayerCollision(CollidingEntity);
        break;

    case enemy:
        HandleEnemyCollision(Entity, CollidingEntity);
        break;

    case shoot:
        HandleShootCollision(Entity, CollidingEntity);
        break;

    case follower:
        HandleFollowerCollision(Entity, CollidingEntity);
        break;

    default:
        break;
    }
}

void Collision::HandlePlayerCollision(ens CollidingEntity)
{
    if (CollidingEntity->type == money)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->ReturnPlayerOBJ()->Money += 1;
    }
    else if (CollidingEntity->type == enemy)
    {
        HandlePlayerEnemyCollision();
    }
    else if (CollidingEntity->type == powerup && InfoPlayer->hp < 100)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->ReturnPlayerOBJ()->hp = 100;
    }
    else if (CollidingEntity->type == shoot)
    {
        entitiesOBJ->inflictDamageToPlayer(SHOOT_DAMAGE * difficulty);
        PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
        if (CollidingEntity->type == shoot)
        {
            entitiesOBJ->KillEntity(CollidingEntity);
        }
    }
    else if (CollidingEntity->type == follower)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->inflictDamageToPlayer(FOLLOWER_DAMAGE * difficulty);
    }
}

void Collision::HandleEnemyCollision(ens Entity, ens CollidingEntity)
{
    if (CollidingEntity->type == player)
    {
        HandleEnemyPlayerCollision(Entity);
    }
    else if (CollidingEntity->type == shoot)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->KillEntity(Entity);
        entitiesOBJ->ReturnPlayerOBJ()->points += KILL_ENEMYS_POINTS;
    }
}

void Collision::HandleShootCollision(ens Entity, ens CollidingEntity)
{
    if (CollidingEntity->type == enemy)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->ReturnPlayerOBJ()->points += KILL_ENEMYS_POINTS;
        entitiesOBJ->KillEntity(Entity);
    }
    else if (CollidingEntity->type == player)
    {
        entitiesOBJ->inflictDamageToPlayer(SHOOT_DAMAGE * difficulty);
        PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
        entitiesOBJ->KillEntity(Entity);
    }
    else if (CollidingEntity->type == follower)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->ReturnPlayerOBJ()->points += KILL_FOLLOWER_POINTS;
        entitiesOBJ->KillEntity(Entity);
    }
}

void Collision::HandleFollowerCollision(ens Entity, ens CollidingEntity)
{
    if (CollidingEntity->type == player)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->KillEntity(Entity);
        entitiesOBJ->inflictDamageToPlayer(FOLLOWER_DAMAGE * difficulty);
    }
    else if (CollidingEntity->type == shoot)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->KillEntity(Entity);
        entitiesOBJ->ReturnPlayerOBJ()->points += KILL_FOLLOWER_POINTS;
    }
}

void Collision::HandleEnemyPlayerCollision(ens Enemy)
{
    if (Enemy->xForce > 0)
        PlayerPointer->xForce = 1 * REPELLING_XFORCE_OF_ENEMYS;
    else
        PlayerPointer->xForce = -1 * REPELLING_XFORCE_OF_ENEMYS;

    PlayerPointer->yForce = REPELLING_YFORCE_OF_ENEMYS;

    entitiesOBJ->inflictDamageToPlayer(PLAYER_ENEMY_COLLISION_DAMAGE * difficulty);
}

void Collision::HandlePlayerEnemyCollision()
{
    if (InfoPlayer->LastMovement == 'd')
        PlayerPointer->xForce = -1 * REPELLING_XFORCE_OF_ENEMYS;
    else
        PlayerPointer->xForce = 1 * REPELLING_XFORCE_OF_ENEMYS;

    PlayerPointer->yForce = REPELLING_YFORCE_OF_ENEMYS;

    entitiesOBJ->inflictDamageToPlayer(PLAYER_ENEMY_COLLISION_DAMAGE * difficulty);
}
