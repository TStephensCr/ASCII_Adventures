#include "events.hpp"


class Collision {
protected:

	Entities* entitiesOBJ;

	WINDOW* curwin;

	ens ListOfEntities;

	ens PlayerPointer = NULL;

	Player* InfoPlayer;

private:
    void UpdateVariables();
    void HandleVerticalCollision(ens Entity, int xPos, int &yPos);
    void HandleHorizontalCollision(ens Entity, int& xPos, int yPos);
    void HandleEntityCollision(ens Entity, ens OtherEntity);
    void HandleEnemyPlayerCollision(ens Enemy);
    void HandlePlayerEnemyCollision();
    void HandlePlayerCollision(ens CollidingEntity);
    void HandleEnemyCollision(ens Entity, ens CollidingEntity);
    void HandleShootCollision(ens Entity, ens CollidingEntity);
    void HandleFollowerCollision(ens Entity, ens CollidingEntity);

public:

	Collision(Entities* MyEntities);

	void ManageJump(ens Entity);

	void OutOfBounds();

	void ManageCollisions(ens Entity);
};