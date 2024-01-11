#include "../include/Events.hpp"

//----Constructor----//
Events::Events(Entities *MyEntities)
{
	entitiesOBJ = MyEntities;

	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();

	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();

	curwin = entitiesOBJ->ReturnCurwin();
}

//----Player-related functions----//

void Events::PlayerGravity()
{
	if (PlayerPointer)
		PlayerPointer->yForce++;
}

int Events::getmv()
{
	int choice = wgetch(curwin);

	UpdateVariables();

	if (!PlayerPointer && !InfoPlayer)
		return choice;

	switch (choice)
	{
	case KEY_RIGHT:
	case (int)'d':
	case (int)'D':
		InfoPlayer->LastMovement = 'd';
		mvright(1);
		break;
	case KEY_LEFT:
	case (int)'a':
	case (int)'A':
		InfoPlayer->LastMovement = 's';
		mvleft(1);
		break;
	case KEY_DOWN:
	case (int)'s':
  case (int)'S':
		Shoot(PlayerPointer, InfoPlayer->LastMovement);
		break;
	case ' ':
		JumpStraight();
		break;
	case KEY_UP:
	case (int)'w':
	case (int)'W':
		Jump();
		break;
	case (int)'q':
	case (int)'Q':
		InfoPlayer->LastMovement = 's';
		break;
	case (int)'e':
	case (int)'E':
		InfoPlayer->LastMovement = 'd';
		break;
	}

	return choice;
}

//----Entity actions----//

void Events::DecreaseForce(entita_p myEntity)
{
	if (myEntity)
	{
		if (myEntity->xForce <= -1)
			myEntity->xForce++;
		else if (myEntity->xForce >= 1)
			myEntity->xForce--;
		if (myEntity->yForce <= -1)
			myEntity->yForce++;
		else if (myEntity->yForce >= 1)
			myEntity->yForce--;
	}
}

void Events::Shoot(entita_p shooter, char lastMovement)
{
	int shooterXPos = shooter->pos.x;
	int shooterYPos = shooter->pos.y;
	int xDelta = (lastMovement == 'd') ? 1 : -1;

	entita_p targetEntity = getTargetEntity(shooter, shooterXPos + xDelta, shooterYPos);

	if (isValidTarget(targetEntity) == true)
	{
		HandleHitTarget(shooter, targetEntity);
	}
	else
	{
		char obstacle = mvwinch(curwin, shooterYPos, shooterXPos + xDelta);

		if (checkIfValidShoot(obstacle, shooter))
		{
			HandleValidShot(shooter, shooterXPos + xDelta, shooterYPos, lastMovement);
		}
	}
}
