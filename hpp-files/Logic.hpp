#include "Collision.hpp"
#include "Mappa.hpp"
#include <fstream>

class Logic {
protected:
	WINDOW* curwin;

	WINDOW* menuwin;

	Entities* entitiesOBJ;

	Player* InfoPlayer;

	Collision *collision;

	Events* eventi;

	GameStatus Status;

	ens PlayerPointer;

	int counter_bot[8][3];

	int bot_clock = 0;

	int curmap_ = 1;

	int curLev_ = 0;

	bool Developer_mode = false;

	int maxX;

	Queue PlayerTrackingQueue;

	MyPosition PlayerPriviusPosition;

	Mappa* map;

private:
	void CheckChangeMap();

	void UpdateVariables();

	void handleEnemys(ens entity);

	void handleFollower(ens entity);

	void HandleBot(ens entity);

	void IncrementCounters();

	void ReadGeneral();

	void ReadPlayer();

	void ReadEntities();

public:

	Logic(WINDOW* win, WINDOW* menuwin);

	Events* ReturnEventsOBJ();

	Entities* ReturnEntitiesOBJ();	

	Player* ReturnInfoPlayer();

	void ResetEntities();

	void InitEntities();

	void InitMappa(int curmap, int curLev, bool check);

	void update_game_logic();

	void render();

	void FileWrite();

	void FileRead();

	int returnCurMap();

	int returnCurLev();

	void set_dev_mode(bool on);

	bool return_DevMode_status();

	void InitColors();
};