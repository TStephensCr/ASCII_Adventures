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

	int counter_bot = 0;

	int counter = 0;

	char curmap_ = '0';

	int curLev_ = 0;

	Mappa* map;

public:

	Logic(WINDOW* win);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	Player* ReturnInfoPlayer();

	void DisplayPlayerStats();

	void InitMappa(char curmap, int curLev);

	void InitEntities(int curLev);

	void GiveDynamicity();

	void FileSave();

	void CheckGameOver();
};