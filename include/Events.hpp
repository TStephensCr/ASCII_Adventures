#pragma once
#define MaxForce 5
#include "Entities.hpp"

class Events
{
protected:
	Entities *entitiesOBJ;

	Player *InfoPlayer;

	WINDOW *curwin;

	entita_p ListOfEntities;

	entita_p PlayerPointer = NULL;

private:
	//----Update functions----//
	void UpdateVariables();

	//----Movement functions----//
	void mvright(int Force);
	void mvleft(int Force);
	void JumpStraight();
	void Jump();

	//----Shooting functions----//
	void HandleHitTarget(entita_p shooter, entita_p target);
	entita_p getTargetEntity(entita_p shooter, int shootNextX, int shootNextY);
	bool isValidTarget(entita_p target);
	bool checkIfValidShoot(char obstacle, entita_p shooter);
	void HandleValidShot(entita_p shooter, int shooterXPos, int shooterYPos, char lastMovement);

public:
	//----Constructor----//
	Events(Entities *MyEntities);

	//----Player-related functions----//
	void PlayerGravity();
	int getmv();

	//----Entity actions----//
	void Shoot(entita_p Entity, char Last_movement);
	void DecreaseForce(entita_p myEntity);
};