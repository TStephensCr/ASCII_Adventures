#pragma once

#include "Collision.hpp"
#include "Mappa.hpp"
#include <fstream>

class Logic
{
protected:
	WINDOW *curwin;

	WINDOW *menuwin;

	Entities *entitiesOBJ;

	Player *InfoPlayer;

	Collision *collision;

	Events *eventi;

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

	Mappa *map;

private:
	void updateMapRelativeToPlayer();

	void UpdateVariables();

	void handleEnemys(ens entity);

	void handleFollower(ens entity);

	void HandleBot(ens entity);

	void IncrementCounters();

	void ReadGeneral();

	void ReadPlayer();

	void ReadEntities();

	void eliminateMaxRangeBullet(ens Entity);

public:
	//---constructor---//

	Logic(WINDOW *win, WINDOW *menuwin);

	//---return functions---//

	Events *ReturnEventsOBJ();

	Entities *ReturnEntitiesOBJ();

	Player *ReturnInfoPlayer();

	int returnCurMap();

	int returnCurLev();

	//---set or reset functions---//

	void ResetEntities();

	void InitEntities();

	void InitColors();

	void set_dev_mode(bool on);

	bool return_DevMode_status();

	void InitMappa(int curmap, int curLev, bool check);

	//---logic functions---//

	void update_game_logic();

	void render();

	void FileWrite();

	void FileRead();

	void increaseMap();

	void decreaseMap();
};