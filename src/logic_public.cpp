#include "hpp-files/Logic.hpp"
//---constructor---//

Logic::Logic(WINDOW *win, WINDOW *menuuwin)
{

	curwin = win;

	entitiesOBJ = new Entities(win);

	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

	collision = new Collision(entitiesOBJ);

	eventi = new Events(entitiesOBJ);

	map = new Mappa(win);

	Status = Running;

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	menuwin = menuuwin;

	maxX = getmaxx(curwin);
}

//---return functions---//

Events *Logic::ReturnEventsOBJ()
{
	return eventi;
}

Entities *Logic::ReturnEntitiesOBJ()
{
	return entitiesOBJ;
}

Player *Logic::ReturnInfoPlayer()
{
	return InfoPlayer;
}

int Logic::returnCurMap()
{
	return curmap_;
}

int Logic::returnCurLev()
{
	return curLev_;
}

int Logic::returnDifficulty()
{
	return difficulty;
}

int Logic::returnMapCounter()
{
	return mapCounter;
}

bool Logic::return_DevMode_status()
{
	return Developer_mode;
}

//---set or reset functions---//

void Logic::initEntities()
{
	entitiesOBJ->Insert(player, X_PLAYERSPAWN, Y_PLAYERSPAWN, 1, 0);

	initEntitiesInMap1();
	initEntitiesInMap2();
	initEntitiesInMap3();
	initEntitiesInMap4();
	initEntitiesInMap5();
	initEntitiesInMap6();
	initEntitiesInMap7();
	initEntitiesInMap8();
}

void Logic::ResetEntities()
{
	entitiesOBJ->DeleteEntities();
	bot_clock = 0;
	PlayerTrackingQueue.clear();
	PlayerTrackingQueue.initialize(FOLLOWER_DELAY);
	resetCounter_bot();
}
void Logic::initEntitiesInMap1()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 1, x);
		}

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 21, 11, 1, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 36, 6, 1, x);
		}

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 55, 9, 1, x);
		}

		entitiesOBJ->Insert(money, 78, 8, 1, x);
	}
}

void Logic::initEntitiesInMap2()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 2, x);
		}

		entitiesOBJ->Insert(money, 31, 12, 2, x);

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 16, 9, 2, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 38, 8, 2, x);
		}

		entitiesOBJ->Insert(money, 54, 12, 2, x);

		entitiesOBJ->Insert(powerup, 68, 14, 2, x);

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 77, 10, 2, x);
		}
	}
}
void Logic::initEntitiesInMap3()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 3, x);
		}

		entitiesOBJ->Insert(money, 22, 5, 3, x);

		entitiesOBJ->Insert(powerup, 22, 14, 3, x);

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 30, 11, 3, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 32, 6, 3, x);
		}

		entitiesOBJ->Insert(money, 60, 6, 3, x);

		entitiesOBJ->Insert(money, 73, 13, 3, x);
	}
}

void Logic::initEntitiesInMap4()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 4, x);
		}

		entitiesOBJ->Insert(money, 37, 7, 4, x);

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 51, 7, 4, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 29, 13, 4, x);
		}

		entitiesOBJ->Insert(money, 53, 13, 4, x);

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 68, 11, 4, x);
		}

		entitiesOBJ->Insert(powerup, 22, 10, 4, x);
	}
}

void Logic::initEntitiesInMap5()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 5, x);
		}

		entitiesOBJ->Insert(money, 42, 5, 5, x);

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 19, 13, 5, x);
		}

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 25, 9, 5, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 49, 8, 5, x);
		}

		entitiesOBJ->Insert(money, 73, 10, 5, x);

		entitiesOBJ->Insert(powerup, 45, 14, 5, x);
	}
}

void Logic::initEntitiesInMap6()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 6, x);
		}

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 19, 14, 6, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 45, 14, 6, x);
		}

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 76, 9, 6, x);
		}

		entitiesOBJ->Insert(money, 35, 11, 6, x);

		entitiesOBJ->Insert(powerup, 64, 11, 6, x);
	}
}

void Logic::initEntitiesInMap7()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 7, x);
		}

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 15, 8, 7, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 44, 9, 7, x);
		}

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 73, 10, 7, x);
		}

		entitiesOBJ->Insert(money, 62, 12, 7, x);
	}
}

void Logic::initEntitiesInMap8()
{
	for (int x = 0; x < 3; x++)
	{
		if (x > 0)
		{
			entitiesOBJ->Insert(follower, 5, 4, 8, x);
		}

		if (x >= 0)
		{
			entitiesOBJ->Insert(enemy, 17, 7, 8, x);
		}

		if (x >= 1)
		{
			entitiesOBJ->Insert(enemy, 31, 10, 8, x);
		}

		if (x >= 2)
		{
			entitiesOBJ->Insert(enemy, 58, 8, 8, x);
		}

		entitiesOBJ->Insert(money, 49, 13, 8, x);

		entitiesOBJ->Insert(powerup, 79, 7, 8, x);
	}
}

void Logic::InitColors()
{
	init_pair(PLAYER_COLOR, COLOR_WHITE, COLOR_WHITE);
	init_pair(ENEMY_COLOR, COLOR_RED, COLOR_RED);
	init_pair(MONEY_COLOR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(SHOOT_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(POWERUP_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(FOLLOWER_COLOR, COLOR_CYAN, COLOR_BLACK);
	init_pair(SHIELD_COLOR, COLOR_MAGENTA, COLOR_BLACK);
}

void Logic::set_dev_mode(bool on)
{
	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
	Developer_mode = on;
	if (InfoPlayer && on)
	{
		InfoPlayer->colpi = 10000;
		InfoPlayer->hp = 10000;
	}
}

void Logic::InitMappa(int curCounter, int curLev, bool check)
{
	if (check)
	{
		curmap_ = mapArray[curCounter - 1];
		curLev_ = curLev;
	}

	if (curCounter < 1 || curCounter > 8)
	{
		map->leggimappa(curCounter);
		map->stampamappa();
	}
	else
	{
		map->leggimappa(mapArray[curCounter - 1]);
		map->stampamappa();
	}
}

//---logic functions---//
void Logic::FileWrite()			// scrive il salvataggio su file
{ 
	std::ofstream myfile;
	myfile.open("Salvataggio.txt", std::ofstream::trunc);

	//---General---//

	myfile << curmap_ << '\n'; // mappa

	myfile << curLev_ << '\n'; // livello

	myfile << difficulty << '\n'; // difficoltà

	myfile << bot_clock << '\n'; // pacing del gioco

	// pacing dei bot
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			myfile << counter_bot[j][i] << '.';
		}
		myfile << '\n';
	}

	// array mappe
	for (int i = 0; i < 8; i++)
	{
		myfile << mapArray[i] << '.';
	}
	myfile << '\n';

	myfile << mapCounter << '\n'; // counter mappe

	//---Player---//

	Player *tmpPlay = ReturnInfoPlayer();

	myfile << 'U' << '\n';

	myfile << 'h' << tmpPlay->hp << '\n';
	
	myfile << 's' << tmpPlay->shield << '\n';
	
	myfile << 'm' << tmpPlay->Money << '\n';
	
	myfile << 'c' << tmpPlay->colpi << '\n';
	
	myfile << 'p' << tmpPlay->points << '\n';
	
	myfile << 'r' << tmpPlay->bulletRange << '\n';
	
	myfile << 'l' << tmpPlay->LastMovement << '\n';
	
	myfile << 'b' << tmpPlay->inJump << '\n';
	
	myfile << 'x' << PlayerPointer->pos.x << '.' << PlayerPointer->pos.y << '.' << '\n';

	//---Entities---//

	entita_p tmp = entitiesOBJ->ReturnList();
	while (tmp != NULL)
	{
		if (tmp->type != 3)
		{
			myfile << '_' << '\n';

			myfile << 't' << tmp->type << '\n';

			myfile << 'P' << tmp->pos.x << '.' << tmp->pos.y << '.' << '\n';

			myfile << 'm' << tmp->mappa << '\n';

			myfile << 'l' << tmp->livello << '\n';

			myfile << 'D' << tmp->death_flag << '\n';

			myfile << 'x' << tmp->xForce << '\n';

			myfile << 'y' << tmp->yForce << '\n';
		}

		tmp = tmp->next;
	}

	myfile << '<';

	myfile.close();
} // considerazioni per il read: dopo ogni valore di counter bot c'è un punto, il death flag è 0 vivo e 1 morto, tra i due valori di position c'è un punto

void Logic::FileRead()
{
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");

	if (myfile.good())
	{
		ReadGeneral();

		ReadPlayer();

		ReadEntities();
	}
	myfile.close();
}

void Logic::update_game_logic()
{
	entita_p tmp = entitiesOBJ->ReturnList();

	UpdateVariables();

	updateMapRelativeToPlayer();

	collision->setDifficulty(difficulty);

	eventi->PlayerGravity();

	Position rememberPosition;

	rememberPosition.Select(PlayerPointer->pos.x, PlayerPointer->pos.y);

	while (tmp)
	{
		if ((!tmp->death_flag) && tmp->mappa == curmap_ && tmp->livello == curLev_)
		{
			entitiesOBJ->DisplayPlayerStats();

			HandleBot(tmp);

			collision->ManageCollisions(tmp);

			eliminateMaxRangeBullet(tmp);

			if (!tmp->death_flag)
			{
				entitiesOBJ->MoveEntity(tmp);

				eventi->DecreaseForce(tmp);
			}
		}

		tmp = tmp->next;
	}

	InfoPlayer->previusPosition.Select(rememberPosition.x, rememberPosition.y);

	entitiesOBJ->RemoveDeadEntities();

	IncrementCounters();
}

void Logic::render()
{
	entita_p tmp = entitiesOBJ->ReturnList();
	while (tmp)
	{
		if (tmp->mappa == curmap_ && tmp->livello == curLev_)
		{
			entitiesOBJ->ClearPosition(tmp);
			entitiesOBJ->Display(tmp);
		}
		tmp = tmp->next;
	}
}

void Logic::decreaseMap()
{
	if (mapCounter == 1 && curLev_ > 0)
	{
		mapCounter = 8;
		curmap_ = mapArray[mapCounter - 1];
		curLev_--;
		PlayerPointer->pos.Select(maxX - 3, Y_PLAYERSPAWN);
		PlayerTrackingQueue.clear();
	}
	else
	{
		if (curLev_ == 0 && mapCounter == 1)
		{
			if (difficulty > 1)
			{
				difficulty--;
				curLev_ = 2;
				mapCounter = 8;
				curmap_ = mapArray[mapCounter - 1];
				PlayerPointer->pos.Select(maxX - 3, Y_PLAYERSPAWN);
			}
			PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
			PlayerTrackingQueue.clear();
		}
		else
		{
			mapCounter--;
			curmap_ = mapArray[mapCounter - 1];
			PlayerPointer->pos.Select(maxX - 3, Y_PLAYERSPAWN);
			PlayerTrackingQueue.clear();
		}
	}
}

void Logic::increaseMap()
{
	if (mapCounter == 8 && curLev_ < 2)
	{
		curLev_++;
		mapCounter = 1;
		curmap_ = mapArray[mapCounter - 1];
		PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
		PlayerTrackingQueue.clear();
	}
	else
	{
		if (curLev_ == 2 && mapCounter == 8)
		{
			difficulty++;
			curLev_ = 0;
			mapCounter = 1;
			curmap_ = mapArray[mapCounter - 1];
			PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
			PlayerTrackingQueue.clear();
		}
		else
		{
			mapCounter++;
			curmap_ = mapArray[mapCounter - 1];
			PlayerPointer->pos.Select(X_PLAYERSPAWN, Y_PLAYERSPAWN);
			PlayerTrackingQueue.clear();
		}
	}
}

void Logic::scrambleArray()
{
	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);
	int temp;
	int randomIndex;
	for (int i = 0; i < 8; i++)
	{
		randomIndex = abs(rand()) % 8;
		temp = mapArray[i];
		mapArray[i] = mapArray[randomIndex];
		mapArray[randomIndex] = temp;
	}
}

void Logic::setNewGame(int diff, int curCounter)
{
	difficulty = diff;
	mapCounter = curCounter;
}