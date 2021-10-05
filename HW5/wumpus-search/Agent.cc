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
	city_block_distance += abs(goalState->x-state->x);
	city_block_distance += abs(goalState->y - state->y);
	return city_block_distance;
}

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	// Works only for test world.
	// You won't initially know safe locations or world size.
	//for (int x = 1; x <= 4; x++) {
	//	for (int y = 1; y <= 4; y++) {
	//		searchEngine.AddSafeLocation(x,y);
	//	}
	//}

	//searchEngine.RemoveSafeLocation(1,3); // wumpus
	//searchEsearchEngine.RemoveSafeLocation(3,1); // pit
	//searchEsearchEngine.RemoveSafeLocation(3,3); // pit
	//searchEsearchEngine.RemoveSafeLocation(4,4); // pit

	agentHasGold = false;
	actionList.clear();
}

Action Agent::Process (Percept& percept)
{
	list<Action> actionList2;
	if (actionList.empty()) {

		// Works only for test world (you won't initially know gold location)
		if (! agentHasGold) {
			// if agent does not know where gold is
			// if agent know where gold is
		else if (agentHasGold){
			if( location is (1,1))
			{
				actionList.push_back(CLIMB);
			}
			else if (location is not (1,1))
			{
				actionList2 = searchEngine.FindPath(curlocation, RIGHT, Location(1,1), RIGHT);
				actionList2.splice(actionList.end(), actionList2);
			}

		}
		else if (percept.Glitter == true)
		{
			// update gold location
		}
		else if (percept.Scream == true)
		{
			
		}
		else if (percept.Breeze 


	}
	Action action = actionList.front();
	actionList.pop_front();
	return action;
}

void Agent::GameOver (int score)
{

}


