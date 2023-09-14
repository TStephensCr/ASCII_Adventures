#include "Collision.hpp"
#include "Mappa.hpp"

class Logic {
protected:

	Entities* entitiesOBJ;

	Player* InfoPlayer;

	Collision *collision;

	Events* eventi;

	GameStatus Status;

	int counter_bot = 0;

	int counter = 0;

	int curmap = 1;

	int curLev = 1;

	Mappa* map;

public:

	Logic(WINDOW* win);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	void InitMappa(char curmap, int curLev);

	void InitEntities(char NumberOfMap, int curLev);

	void GiveDynamicity();

};