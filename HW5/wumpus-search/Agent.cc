// Agent.cc
//
// This code works only for the testworld that comes with the simulator.

#include <iostream>
#include <list>
#include <cstdlib>
#include "Agent.h"

using namespace std;

int MySearchEngine::HeuristicFunction(SearchState* state, SearchState* goalState)
{
	//return 0; // not a good heuristic
	// Good heuristic: city-block distance from state to goalState
	int city_block_distance = 0;
	city_block_distance += abs(goalState->location.X-state->location.X);
	city_block_distance += abs(goalState->location.Y - state->location.Y);
	return city_block_distance;
}

Agent::Agent ()
{
	X = 1;
	Y = 1;
	orientation = RIGHT;
	hasArrow = true;
	agentHasGold = false;
	goldLocation = Location(0,0);
	// assume everywhere is safe first
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			safeLocations.push_back(Location(i,j));
			this->searchEngine.AddSafeLocation(i,j);
		}
	}
}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	X = 1;
	Y = 1;
	orientation = RIGHT;
	hasArrow = true;
	agentHasGold = false;
	visited.clear ();
	visited.push_back(Location(1,1));
	actionList.clear();
}

Action Agent::Process (Percept& percept)
{
	list<Action> actionList2;
	Location curLocation = Location(X,Y);

	if (actionList.empty()) 
	{

		if (! agentHasGold) {
			// if agent does not know where gold is
			if (goldLocation == Location(0,0))
			{
				// pick the last safe unvisited location and go there
				list<Location>::iterator firstGo = safeLocations.begin();
				while (find(visited.begin(), visited.end(),*firstGo) != visited.end())
				{
					firstGo ++;
				}
				
				actionList2 = searchEngine.FindPath(curLocation, orientation, *firstGo, orientation);
				actionList2.splice(actionList.end(), actionList2);
			}
			else
			{
				// if agent know where gold is
				actionList2 = searchEngine.FindPath(curLocation, orientation, goldLocation, orientation);
				actionList2.splice(actionList.end(), actionList2);
			}
			
		}
		else if (agentHasGold)
		{
			// if agent has gold
			if( curLocation ==  Location(1,1))
			{
				// if can get out
				actionList.push_back(CLIMB);
			}
			else if (!(curLocation == Location(1,1)))
			{
				// find a path to get out
				actionList2 = searchEngine.FindPath(curLocation, orientation, Location(1,1), RIGHT);
				actionList2.splice(actionList.end(), actionList2);
			}
		}
	}

	if (percept.Glitter == 1)
	{
		// if get the gold
		// update gold location
		goldLocation =curLocation;
		actionList.push_back(GRAB);
	}

	if (percept.Breeze == true || percept.Bump == true || percept.Stench == true)
	{
		// if breeze or bump or stench
		// unsafe location
		this->searchEngine.RemoveSafeLocation(X,Y);
		this->safeLocations.remove(curLocation);
	}

	Action action = actionList.front();
	actionList.pop_front();
	HandleAction(action, percept);
	this->visited.push_back(curLocation);

	return action;
}


void Agent::HandleAction(Action& action, Percept& percept)
{
	// update based on the action
	// act based on the rules
	if (action == GRAB)
	{
		// If the agent perceives a Glitter, then execute the GRAB action.
		this->hasGold = true;
	}
	else if(action == SHOOT)
	{
		this->hasArrow = false;
	}
	else if (action == TURNRIGHT)
	{
		// turn right based on current orientation
		if (this->orientation == RIGHT)
		{
			this->orientation = DOWN;
		} else if (this->orientation == UP)
		{
			this->orientation = RIGHT;
		} else if (this->orientation == LEFT)
		{
			this->orientation = UP;
		} else if (this->orientation == DOWN)
		{
			this->orientation = LEFT;
		}
	}
	else if (action == TURNLEFT)
	{
		// turn left based on current orientation
		if (this->orientation == RIGHT)
		{
			this->orientation = UP;
		} 
		else if (this->orientation == UP)
		{
			this->orientation = LEFT;
		} 
		else if (this->orientation == LEFT)
		{
			this->orientation = DOWN;
		} 
		else if (this->orientation == DOWN)
		{
			this->orientation = RIGHT;
		}
	}
	else if (action == GOFORWARD)
	{
		// check if go forward is ok
		if (this->orientation == RIGHT)
		{
			// go right, if the cur position no bump.
			if (percept.Bump == false)
			{
				this->X += 1;
			}

		} 
		else if (this->orientation == UP)
		{
			// go up, if the cur position no bump.
			if (percept.Bump == false)
			{
				if (find(visited.begin(), visited.end(), Location(X,Y+1))==visited.end())
				{
					this->Y += 1;
				}
			}
		} 
		else if (this->orientation == LEFT)
		{
			// go left, if the cur position X is larger than 1 and no bump.
			if (this->X > 1&&percept.Bump == false)
			{
				this->X -= 1;
			} 
		} 
		else if (this->orientation == DOWN)
		{
			// go down,if the cur position Y is larger than 1 and no bump.
			if (this->Y > 1 && percept.Bump == false)
			{
				this->Y -= 1;
			}
		}
	}	
}

void Agent::GameOver (int score)
{

}


