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
	
	void HandleVerticalCollision(ens Entity, int xPos, int &yPos, int mappa, int livello);

	void HandleHorizontalCollision(ens Entity, int& xPos, int yPos, int mappa, int livello);

	void HandleEntityCollision(ens Entity, ens OtherEntity);

	void HandleEnemyPlayerCollision(ens Player, ens Enemy);

	void HandlePlayerEnemyCollision(ens Player, ens Enemy);
public:

	Collision(Entities* MyEntities);

	void ManageJump(ens Entity);

	void OutOfBounds();

	void ManageCollisions(ens Entity, int mappa, int livello);
};