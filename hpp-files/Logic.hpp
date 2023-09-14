#include "Collision.hpp"

class Logic {
protected:

	Entities* entitiesOBJ;

	Player* InfoPlayer;

	Collision *collision;

	Events* eventi;

	GameStatus Status;

	int counter_bot = 0;

	int counter = 0;

public:

	Logic(WINDOW* win);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	void InitEntities(int NumberOfMap);

	void GiveDynamicity();

};