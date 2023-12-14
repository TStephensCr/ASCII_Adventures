#include "../include/Collision.hpp"

//----Update functions----//

void Collision::UpdateVariables()
{
    PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
    InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
}

//----Collision handling functions----//

void Collision::handleCollisions(entita_p Entity)
{
    int xPos = Entity->pos.x;
    int yPos = Entity->pos.y;

    if (Entity->yForce != 0)
        HandleVerticalCollision(Entity, xPos, yPos);
    if (Entity->xForce != 0)
        HandleHorizontalCollision(Entity, xPos, yPos);
}

void Collision::HandleVerticalCollision(entita_p Entity, int xPos, int &yPos)
{
    int dir = (Entity->yForce < 0) ? -1 : 1;

    char obstacle = mvwinch(curwin, yPos + dir, xPos);

    if (isMapCollision(obstacle))
    {
        handleVerticalMapCollision(Entity);
        return;
    }
    else
    {
        entita_p CollidingEntity = getCollidingEntity(Entity, xPos, yPos + dir);

        if (checkExistenceOfEntity(CollidingEntity) == true)
        {
            HandleEntityCollision(Entity, CollidingEntity);
        }

        yPos = yPos + dir;
    }
}

void Collision::HandleHorizontalCollision(entita_p Entity, int xPos, int yPos)
{
    xPos = (Entity->xForce < 0) ? xPos - 1 : xPos + 1;
    char obstacle = mvwinch(curwin, yPos, xPos);

    entita_p CollidingEntity = getCollidingEntity(Entity, xPos, yPos);

    if (isMapCollision(obstacle))
    {
        handleHorizontalMapCollision(Entity);
    }
    else if (checkExistenceOfEntity(CollidingEntity) == true && isPossibleEntitiesCollision(Entity, CollidingEntity))
    {
        HandleEntityCollision(Entity, CollidingEntity);
    }
}

bool Collision::isMapCollision(char posInNextFrame)
{
    return (posInNextFrame == HORIZONTAL_WALL || posInNextFrame == VERTICAL_WALL || posInNextFrame == FULLFILL_POINT);
}

bool Collision::isPossibleEntitiesCollision(entita_p Entity, entita_p CollidingEntity)
{
    return (!entitiesOBJ->SameDir(Entity, CollidingEntity) || CollidingEntity->xForce == 0);
}

entita_p Collision::getCollidingEntity(entita_p Entity, int entityNextX, int entityNextY)
{
    Position positionAtNewFrame;

    positionAtNewFrame.Select(entityNextX, entityNextY);

    entita_p CollidingEntity = entitiesOBJ->EntitiesInLocation(positionAtNewFrame, Entity->mappa, Entity->livello);

    return CollidingEntity;
}

void Collision::handleHorizontalMapCollision(entita_p entity)
{
    if (entity->type == shoot)
    {
        entitiesOBJ->KillEntity(entity);
    }
    else
    {
        entity->xForce = 0;
    }
}

void Collision::handleVerticalMapCollision(entita_p entity)
{
    entity->yForce = 0;
}

bool Collision::checkExistenceOfEntity(entita_p collidingEntity)
{
    return (collidingEntity != NULL);
}

void Collision::HandleEntityCollision(entita_p Entity, entita_p CollidingEntity)
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

void Collision::HandlePlayerCollision(entita_p CollidingEntity)
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
    else if (CollidingEntity->type == powerup && InfoPlayer->hp < PLAYER_MAX_HP)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->ReturnPlayerOBJ()->hp = PLAYER_MAX_HP;
    }
    else if (CollidingEntity->type == shoot)
    {
        entitiesOBJ->inflictDamageToPlayer(SHOOT_DAMAGE * difficulty);
        PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
        entitiesOBJ->KillEntity(CollidingEntity);
    }
    else if (CollidingEntity->type == follower)
    {
        entitiesOBJ->KillEntity(CollidingEntity);
        entitiesOBJ->inflictDamageToPlayer(FOLLOWER_DAMAGE * difficulty);
    }
}

void Collision::HandleEnemyCollision(entita_p Entity, entita_p CollidingEntity)
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

void Collision::HandleShootCollision(entita_p Entity, entita_p CollidingEntity)
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

void Collision::HandleFollowerCollision(entita_p Entity, entita_p CollidingEntity)
{
    if (CollidingEntity->type == player)
    {
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

void Collision::HandleEnemyPlayerCollision(entita_p Enemy)
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
