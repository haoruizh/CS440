// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include "Orientation.h"
#include "Location.h"

class Agent
{
public:
	Location *curLocate;
	bool hasGold;
	bool hasArrow;
	Orientation curOrientation;
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
};

#endif // AGENT_H
