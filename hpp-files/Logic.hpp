#include "Collision.hpp"

class Logic {
protected:

	Entities* entitiesOBJ;

	Player* InfoPlayer;

	Collision *collision;

	Events* eventi;

	GameStatus Status;

public:

	Logic(WINDOW* win);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	void InitEntities(int NumberOfMap);

	void GiveDynamicity();

};