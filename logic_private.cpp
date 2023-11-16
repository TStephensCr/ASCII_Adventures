#include "hpp-files/Logic.hpp"

void Logic::UpdateVariables()
{
	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	if (PlayerPointer)
	{
		PlayerPointer->livello = curLev_;
		PlayerPointer->mappa = curmap_;
	}

	map->leggimappa(curmap_);
	map->stampamappa();
}

void Logic::updateMapRelativeToPlayer()
{
	if (PlayerPointer)
	{
		int playerXloc = PlayerPointer->pos.x;
		int playerYloc = PlayerPointer->pos.y;

		if (playerXloc == 1 && playerYloc == 12)
		{
			decreaseMap();
		}
		else if (playerXloc == maxX - 2 && playerYloc == 12)
		{
			increaseMap();
		}
	}
}

void Logic::HandleBot(ens entity)
{
	if (entity->type == enemy)
	{
		handleEnemys(entity);
	}
	else if (entity->type == follower)
	{
		handleFollower(entity);
	}
}

void Logic::handleEnemys(ens entity)
{
	if (bot_clock == 3)
	{
		if (entity->livello == 2)
		{
			if (counter_bot[curmap_ - 1][curLev_] == 4)
			{
				eventi->Shoot(entity, 'd');
			}
			else if (counter_bot[curmap_ - 1][curLev_] == 13)
			{
				eventi->Shoot(entity, 's');
			}
		}
		if (counter_bot[curmap_ - 1][curLev_] < 9)
		{
			entity->xForce = 1;
		}
		else if (counter_bot[curmap_ - 1][curLev_] >= 9 && counter_bot[curmap_ - 1][curLev_] < 18)
		{
			entity->xForce = -1;
		}
	}
}

void Logic::handleFollower(ens follower)
{
	if (PlayerTrackingQueue.size < FOLLOWER_DELAY)
	{
		MyPosition nullPos;
		PlayerTrackingQueue.enqueue(nullPos);
	}
	else
	{
		bool stuck = false;
		MyPosition positionWithDelay = PlayerTrackingQueue.dequeue();
		if (positionWithDelay.checkValidPos())
		{
			if (follower->pos.x != positionWithDelay.x)
			{
				int direction = (follower->pos.x > positionWithDelay.x) ? -1 : 1;
				char nextBlock = mvwinch(curwin, follower->pos.y, follower->pos.x + direction);

				if (nextBlock != CHARACTER and nextBlock != SPACE and nextBlock != SHOOT)
				{
					follower->yForce = -1;
					stuck = true;
				}
				follower->xForce = direction;
			}
			if (follower->pos.y > positionWithDelay.y)
				follower->yForce = -1;
			else if (follower->pos.y < positionWithDelay.y && !stuck)
				follower->yForce = 1;

			stuck = false;
		}
		PlayerTrackingQueue.enqueue(PlayerPointer->pos);
	}
}

void Logic::IncrementCounters()
{
	bot_clock++;

	if (bot_clock > 3)
	{
		counter_bot[curmap_ - 1][curLev_]++;
		bot_clock = 0;
	}

	if (counter_bot[curmap_ - 1][curLev_] == 18)
	{
		counter_bot[curmap_ - 1][curLev_] = 0;
	}
}

void Logic::ReadGeneral()
{
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");

	do
	{ // mappa
		mychar = myfile.get();
	} while (mychar != 'M');
	mychar = myfile.get();
	curmap_ = mychar - '0'; // per ottenere il valore int di un numero letto come char si sottrae il valore int assegnato a '0' al valore in assegnato al char letto('3'=51, '0'=48, 51-48=3)

	do
	{ // livello
		mychar = myfile.get();
	} while (mychar != 'L');
	mychar = myfile.get();
	curLev_ = mychar - '0';

	do
	{ // bot_clock
		mychar = myfile.get();
	} while (mychar != 'C');
	mychar = myfile.get();
	bot_clock = mychar - '0';

	char number_str[3];
	char *output;
	do
	{ // counter_bot
		mychar = myfile.get();
	} while (mychar != 'B');
	mychar = myfile.get(); // il carattere \n
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			number_str[0] = myfile.get();
			number_str[1] = myfile.get();
			counter_bot[j][i] = strtol(number_str, &output, 10);
			if (number_str[1] != '.')
				mychar = myfile.get();
		}
		mychar = myfile.get(); // il carattere \n
	}
	myfile.close();
}

void Logic::ReadPlayer()
{ // manca leggere positionWithDelay per l'insert
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");
	char number_str[3];
	char *output;

	ens tmp = entitiesOBJ->Insert(player, X_PLAYERSPAWN, Y_PLAYERSPAWN, curmap_, curLev_); // nella lista la pos del player viene aggiornata quando cambio la pos di Infoplayer(perche?)
	UpdateVariables();
	do
	{ // hp
		mychar = myfile.get();
	} while (mychar != 'h');
	number_str[0] = myfile.get();
	if (number_str[0] != '0')
	{
		number_str[1] = myfile.get();
		number_str[2] = myfile.get();
		InfoPlayer->hp = strtol(number_str, &output, 10);
	}
	else
		InfoPlayer->hp = 0;
	number_str[2] = 'f';

	do
	{ // shield
		mychar = myfile.get();
	} while (mychar != 's');
	number_str[0] = myfile.get();
	number_str[1] = myfile.get();
	InfoPlayer->shield = strtol(number_str, &output, 10);

	do
	{ // soldi
		mychar = myfile.get();
	} while (mychar != 'm');
	number_str[0] = myfile.get();
	number_str[1] = myfile.get();
	InfoPlayer->Money = strtol(number_str, &output, 10);

	do
	{ // colpi
		mychar = myfile.get();
	} while (mychar != 'c');
	number_str[0] = myfile.get();
	number_str[1] = myfile.get();
	InfoPlayer->colpi = strtol(number_str, &output, 10);

	do
	{ // punti
		mychar = myfile.get();
	} while (mychar != 'p');
	number_str[0] = myfile.get();
	if (number_str[0] != '0')
	{
		number_str[1] = myfile.get();
		number_str[2] = myfile.get();
		InfoPlayer->points = strtol(number_str, &output, 10);
	}
	else
		InfoPlayer->points = 0;
	number_str[2] = 'f';

	do
	{ // lasy movement
		mychar = myfile.get();
	} while (mychar != 'l');
	mychar = myfile.get();
	InfoPlayer->LastMovement = mychar;

	do
	{ // InJump
		mychar = myfile.get();
	} while (mychar != 'b');
	mychar = myfile.get();
	if (mychar == '1')
		InfoPlayer->inJump = true;
	else
		InfoPlayer->inJump = false;

	int xtemp, ytemp;
	do
	{ // position
		mychar = myfile.get();
	} while (mychar != 'x');
	number_str[0] = myfile.get();
	number_str[1] = myfile.get();
	xtemp = strtol(number_str, &output, 10);
	if (number_str[1] != '.')
		mychar = myfile.get();
	number_str[0] = myfile.get();
	number_str[1] = myfile.get();
	ytemp = strtol(number_str, &output, 10);
	tmp->pos.Select(xtemp, ytemp);

	myfile.close();
}

void Logic::ReadEntities()
{
	char mychar;
	std::ifstream myfile;
	myfile.open("Salvataggio.txt");
	char number_str[3];
	char *output;

	int xtemp, ytemp;
	while (myfile.good() && mychar != '<')
	{ // valore di fine file
		ens tmp = new entita;
		do
		{ // type
			mychar = myfile.get();
		} while (mychar != 't' && myfile.good());
		mychar = myfile.get();
		switch (mychar)
		{
		case '1':
			tmp->type = enemy;
			break;
		case '2':
			tmp->type = money;
			break;
		case '4':
			tmp->type = powerup;
			break;
		case '5':
			tmp->type = follower;
			break;
		default:
			continue;
		}

		do
		{ // position
			mychar = myfile.get();
		} while (mychar != 'P' && myfile.good());
		number_str[0] = myfile.get();
		number_str[1] = myfile.get();
		xtemp = strtol(number_str, &output, 10);
		if (number_str[1] != '.')
			mychar = myfile.get();
		number_str[0] = myfile.get();
		number_str[1] = myfile.get();
		ytemp = strtol(number_str, &output, 10);
		tmp->pos.Select(xtemp, ytemp);

		do
		{ // mappa entita
			mychar = myfile.get();
		} while (mychar != 'm' && myfile.good());
		mychar = myfile.get();
		tmp->mappa = mychar - '0';

		do
		{ // livello entita
			mychar = myfile.get();
		} while (mychar != 'l' && myfile.good());
		mychar = myfile.get();
		tmp->livello = mychar - '0';

		do
		{ // death flag
			mychar = myfile.get();
		} while (mychar != 'D' && myfile.good());
		if (mychar == '1')
			tmp->death_flag = true;
		else
			tmp->death_flag = false;

		do
		{ // xForce
			mychar = myfile.get();
		} while (mychar != 'x' && myfile.good());
		mychar = myfile.get();
		tmp->xForce = mychar - '0';

		do
		{ // yForce
			mychar = myfile.get();
		} while (mychar != 'y' && myfile.good());
		mychar = myfile.get();
		tmp->yForce = mychar - '0';

		entitiesOBJ->Insert(tmp->type, tmp->pos.x, tmp->pos.y, tmp->mappa, tmp->livello);

		mychar = myfile.get();
		mychar = myfile.get(); // due get nel caso sia l'ultimo elemento, in tal caso questo mychar sarebbe <(fine file)
	}

	myfile.close();
}

void Logic::eliminateMaxRangeBullet(ens Entity)
{
	if (!Entity)
		return;

	if (Entity->type == shoot && (Entity->xForce == 1 || Entity->xForce == -1))
	{
		entitiesOBJ->KillEntity(Entity);
	}
}