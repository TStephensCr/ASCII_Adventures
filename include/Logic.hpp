#pragma once

#include "Collision.hpp"
#include "Queue.hpp"
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

	entita_p PlayerPointer;

	int counter_bot[8][3];

	int bot_clock = 0;

	int curmap_ = 1;

	int curLev_ = 0;

	int difficulty = 1;

	bool Developer_mode = false;

	int maxX;

	int mapArray[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	int mapCounter = 1;

	Queue PlayerTrackingQueue;

	Position PlayerPriviusPosition;

	Mappa *map;

private:
	// Initialization functions
	void UpdateVariables();
	void ReadGeneral();
	void ReadPlayer();
	void ReadEntities();

	// Entity handling functions
	void handleEnemies(entita_p entity);
	void handleEnemiesShots(entita_p enemy);
	void letEnemiesShoot(entita_p enemy);
	void handleEnemysMovement(entita_p entity);
	void handleFollower(entita_p entity);
	void letFollowerMove(entita_p follower, Position playerPositionWithDelay);
	void moveFollowerHorizontally(entita_p follower, Position playerPositionWithDelay, bool &stuck);
	void moveFollowerVertically(entita_p follower, Position playerPositionWithDelay, bool &stuck);
	bool isFollowerValidMove(char block);
	void HandleBot(entita_p entity);
	void IncrementCounters();
	void eliminateMaxRangeBullet(entita_p Entity);
	void resetCounter_bot();

	// Map-related functions
	void updateMapRelativeToPlayer();

public:
	//---constructor---//

	Logic(WINDOW *win, WINDOW *menuwin);

	//---return functions---//

	Events *ReturnEventsOBJ();

	Entities *ReturnEntitiesOBJ();

	Player *ReturnInfoPlayer();

	int returnCurMap();

	int returnCurLev();

	int returnDifficulty();

	int returnMapCounter();

	bool return_DevMode_status();

	//---set or reset functions---//

	void ResetEntities();

	void initEntities();

	void initEntitiesInMap1();
	void initEntitiesInMap2();
	void initEntitiesInMap3();
	void initEntitiesInMap4();
	void initEntitiesInMap5();
	void initEntitiesInMap6();
	void initEntitiesInMap7();
	void initEntitiesInMap8();

	void InitColors();

	void set_dev_mode(bool on);

	void InitMappa(int curmap, int curLev, bool check);

	//---logic functions---//

	void update_game_logic();

	void render();

	void FileWrite();

	void FileRead();

	void increaseMap();

	void increaseMapStat();

	void decreaseMap();

	void scrambleArray();

	void setNewGame(int diff, int curCounter);
};