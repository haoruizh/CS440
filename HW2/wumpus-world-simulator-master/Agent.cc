// Agent.cc

#include <iostream>
#include <cstdlib>
#include "Agent.h"
#include <ctime>

using namespace std;

Agent::Agent ()
{
	// call initialize function
	Initialize();
}

Agent::~Agent ()
{
	// free cur location pointer
	free(curLocate);
}

void Agent::Initialize ()
{
	this->hasArrow = true;
	this->hasGold = false;
	this->curLocate = new Location(1,1);
	this->curOrientation = RIGHT;
}

Action Agent::Process (Percept& percept)
{	
	Action action;

	// act based on the rules
	if (curLocate->X == 1 && curLocate->Y == 1 && hasGold == true)
	{
		// If the agent is in the (1,1) location and has the gold, then CLIMB.
		action = CLIMB;
	}
	else if (percept.Glitter == 1)
	{
		// If the agent perceives a Glitter, then execute the GRAB action.
		action = GRAB;
		this->hasGold = true;
	}
	else if(this->hasArrow == true && percept.Stench == 1)
	{
		// If the agent perceives a Stench and has an arrow, then SHOOT.
		action = SHOOT;
		this->hasArrow = false;
	}
	else
	{
		// If none of the above conditions are met, then the agent should randomly choose one
		// of the actions: GOFORWARD, TURNLEFT, TURNRIGHT.
		int move = rand()%3;
		switch (move)
		{
			case 0:
				// turn right based on current orientation
				action = TURNRIGHT;
				if (this->curOrientation == RIGHT)
				{
					this->curOrientation = DOWN;
				} else if (this->curOrientation == UP)
				{
					this->curOrientation = RIGHT;
				} else if (this->curOrientation == LEFT)
				{
					this->curOrientation = UP;
				} else if (this->curOrientation == DOWN)
				{
					this->curOrientation = LEFT;
				}
				break;
			case 1:
				// turn left based on current orientation
				action = TURNLEFT;
				if (this->curOrientation == RIGHT)
				{
					this->curOrientation = UP;
				} 
				else if (this->curOrientation == UP)
				{
					this->curOrientation = LEFT;
				} 
				else if (this->curOrientation == LEFT)
				{
					this->curOrientation = DOWN;
				} 
				else if (this->curOrientation == DOWN)
				{
					this->curOrientation = RIGHT;
				}
				break;
			case 2:
				action = GOFORWARD;
				
				// check if go forward is ok
				if (this->curOrientation == RIGHT)
				{
					// go right, if the cur position X is less than 4 and no bump.
					// for PA2 always assume world is 4*4
					if (this->curLocate->X < 4&&percept.Bump == false)
					{
						this->curLocate->X += 1;
					} 
				} 
				else if (this->curOrientation == UP)
				{
					// go up, if the cur position Y is less than 4 and no bump.
					// for PA2 always assume world is 4*4
					if (this->curLocate->Y < 4&&percept.Bump == false)
					{
						this->curLocate->Y+=1;
					} 
				} 
				else if (this->curOrientation == LEFT)
				{
					// go left, if the cur position X is larger than 1 and no bump.
					if (this->curLocate->X > 1&&percept.Bump == false)
					{
						this->curLocate->X-=1;
					} 
				} 
				else if (this->curOrientation == DOWN)
				{
					// go down,if the cur position Y is larger than 1 and no bump.
					if (this->curLocate->Y > 1&&percept.Bump == false)
					{
						this->curLocate->Y-=1;
					}
				}
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

