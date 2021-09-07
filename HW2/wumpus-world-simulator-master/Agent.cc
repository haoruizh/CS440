// Agent.cc

#include <iostream>
#include <cstdlib>
#include "Agent.h"
#include <ctime>

using namespace std;

Agent::Agent ()
{
	Initialize();
}

Agent::~Agent ()
{
	//free(curLocate);
}

void Agent::Initialize ()
{
	this->hasArrow = true;
	this->hasGold = false;
	this->curLocate = new Location(1,1);
	this->curOrientation = UP;
}

Action Agent::Process (Percept& percept)
{
	//char c;
	
	Action action;
	

	// act based on the rules
	if (curLocate == new Location(1,1) && hasGold == true)
	{
		action = CLIMB;
	}
	else if (percept.Glitter > 0)
	{
		action = GRAB;
		this->hasGold = true;
	}
	else if(this->hasArrow == true && percept.Stench > 0)
	{
		action = SHOOT;
		this->hasArrow = false;
	}
	else
	{
		int move = rand()%3;
		switch (move)
		{
			case 0:
				action = TURNRIGHT;
				break;
			case 1:
				action = TURNLEFT;
				break;
			case 2:
				action = GOFORWARD;
				break;
			default:
				break;
		}
	}

	return action;
}

void Agent::GameOver (int score)
{

}

