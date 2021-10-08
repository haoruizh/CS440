// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"

#include "Location.h"
#include "Orientation.h"
#include "Search.h"
#include <list>

class MySearchEngine: public SearchEngine {
	virtual int HeuristicFunction (SearchState* state, SearchState* goalState);
};

class Agent
{
public:
	Location goldLocation;
	int X;
	int Y;
	Orientation orientation;
	bool hasArrow;
	bool hasGold;
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
	void HandleAction(Action& action, Percept& percept);
	bool agentHasGold;
	void AddAdjacent();
	list<Action> actionList;
	MySearchEngine searchEngine;
	list<Location> visited;
	list<Location> safeLocations;
};

#endif // AGENT_H
