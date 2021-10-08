// Agent.cc
//
// This code works only for the testworld that comes with the simulator.

#include <iostream>
#include <list>
#include <cstdlib>
#include "Agent.h"
#include <algorithm>

using namespace std;

int MySearchEngine::HeuristicFunction(SearchState* state, SearchState* goalState)
{
	//return 0; // not a good heuristic
	// Good heuristic: city-block distance from state to goalState
	int city_block_distance = 0;
	city_block_distance += abs(goalState->location.X - state->location.X);
	city_block_distance += abs(goalState->location.Y - state->location.Y);
	return city_block_distance;
}

Agent::Agent ()
{
	X = 1;
	Y = 1;
	orientation = RIGHT;
	hasArrow = true;
	hasGold = false;
	goldLocation = Location(0,0);
	safeLocations.clear();
	this->searchEngine = MySearchEngine();
}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	cout << "Unsafe Location: " << X << " " << Y<<endl;
	this->safeLocations.remove(Location(X,Y));
	this->searchEngine.RemoveSafeLocation(X,Y);

	X = 1;
	Y = 1;
	orientation = RIGHT;
	hasArrow = true;
	hasGold = false;
	visited.clear ();
	actionList.clear();
}

Action Agent::Process (Percept& percept)
{
	list<Action> actionList2;
	Location curLocation = Location(X,Y);
	visited.push_back(curLocation);
	this->safeLocations.push_back(curLocation);
	this->searchEngine.AddSafeLocation(X,Y);
	cout << "CurentLocation " << X << " " << Y << endl ;
	cout << "Gold Location " << goldLocation.X << " " << goldLocation.Y << endl;

	if (percept.Breeze == 0 && percept.Stench == 0)
	{
		AddAdjacent();
	}
	

	if (!hasGold) 
	{
		// if agent does not know where gold is
		if (goldLocation == Location(0,0))
		{
			// pick the last safe unvisited location and go there
			list<Location>::iterator firstGo = safeLocations.end();
			while (std::find(visited.begin(), visited.end(),*firstGo) != visited.end())
			{
				firstGo --;
			}
			
			actionList2 = searchEngine.FindPath(curLocation, RIGHT, *firstGo, RIGHT);
			actionList.splice(actionList.end(), actionList2);
		}
		else
		{
			// if agent know where gold is
			actionList2 = searchEngine.FindPath(curLocation, RIGHT, goldLocation, RIGHT);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(GRAB);

		}
	}
	else if (hasGold)
	{
		// if agent has gold
		if( curLocation ==  Location(1,1))
		{
			// if can get out
			return CLIMB;
		}
		else if (curLocation.X != 1 || curLocation.Y != 1)
		{
			// find a path to get out
			actionList2 = searchEngine.FindPath(curLocation, RIGHT, Location(1,1), RIGHT);
			actionList.splice(actionList.end(), actionList2);
		}
	}

	if (percept.Glitter == 1)
	{
		// if get the gold
		// update gold location
		goldLocation = curLocation;
		actionList.push_back(GRAB);
	}

	Action action;
	if (actionList.empty())
	{
		list<Location>::iterator firstGo = safeLocations.begin();
		while (std::find(visited.begin(), visited.end(),*firstGo) != visited.end())
		{
			firstGo --;
		}
		
		actionList2 = searchEngine.FindPath(curLocation, orientation, *firstGo, orientation);
		actionList.splice(actionList.end(), actionList2);
	}
	else
	{
		action = actionList.front();
		actionList.pop_front();
	}
	cout << "Gold: "+ goldLocation.X + ' ' + goldLocation.Y + '\n';
	HandleAction(action, percept);

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
				if (find(visited.begin(), visited.end(), Location(X+1,Y))==visited.end()&&find(safeLocations.begin(), safeLocations.end(), Location(X+1,Y))!= safeLocations.end())
				{
					this->X += 1;
				}
			}

		} 
		else if (this->orientation == UP)
		{
			// go up, if the cur position no bump.
			if (percept.Bump == false)
			{
				if (find(visited.begin(), visited.end(), Location(X,Y+1))==visited.end() && find(safeLocations.begin(), safeLocations.end(), Location(X,Y-1))!= safeLocations.end())
				{
					this->Y += 1;
				}
			}
		} 
		else if (this->orientation == LEFT)
		{
			// go left, if the cur position X is larger than 1 and no bump.
			if (percept.Bump == false)
			{
				if (find(visited.begin(), visited.end(), Location(X-1,Y))==visited.end() && find(safeLocations.begin(), safeLocations.end(), Location(X-1,Y))!= safeLocations.end())
				{
					this->X -= 1;
				}
			} 
		} 
		else if (this->orientation == DOWN)
		{
			// go down,if the cur position Y is larger than 1 and no bump.
			if (percept.Bump == false)
			{
				if (find(visited.begin(), visited.end(), Location(X,Y-1))==visited.end() && find(safeLocations.begin(), safeLocations.end(), Location(X,Y-1))!= safeLocations.end())
				{
					this->Y -= 1;
				}
			}
		}
	}	
}


void Agent::AddAdjacent()
{
	// add adjacent nodes of current location
		if (find(safeLocations.begin(), safeLocations.end(), Location(X+1, Y))==safeLocations.end())
		{
			this->safeLocations.push_back(Location(X+1,Y));
			this->searchEngine.AddSafeLocation(X+1,Y);
		}

		if (find(safeLocations.begin(), safeLocations.end(), Location(X, Y+1))==safeLocations.end())
		{
			this->safeLocations.push_back(Location(X,Y+1));
			this->searchEngine.AddSafeLocation(X,Y+1);
		}

		if (find(safeLocations.begin(), safeLocations.end(), Location(X-1, Y))==safeLocations.end())
		{
			this->safeLocations.push_back(Location(X-1,Y));
			this->searchEngine.AddSafeLocation(X-1,Y);
		}

		if (find(safeLocations.begin(), safeLocations.end(), Location(X, Y-1))==safeLocations.end())
		{
			this->safeLocations.push_back(Location(X,Y-1));
			this->searchEngine.AddSafeLocation(X,Y-1);
		}
}

void Agent::GameOver (int score)
{
}


