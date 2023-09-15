#include "Collision.hpp"
#include "Mappa.hpp"

class Logic {
protected:
	WINDOW* curwin;

	Entities* entitiesOBJ;

	Player* InfoPlayer;

	Collision *collision;

	Events* eventi;

	GameStatus Status;

	int counter_bot[5];

	int counter;

	int curmap_ = 1;

	int curLev_ = 0;

	Mappa* map;

public:

	Logic(WINDOW* win);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	Player* ReturnInfoPlayer();

	void DisplayPlayerStats();

	void InitMappa(int curmap, int curLev);

	void InitEntities(int curLev);

	void GiveDynamicity();

	void FileSave();

	void CheckChangeMap();

	void CheckGameOver();
};