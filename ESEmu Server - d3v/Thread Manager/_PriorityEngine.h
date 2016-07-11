#pragma once
#ifndef _PRIORITYENGINE_H_
#define _PRIORITYENGINE_H_

#ifdef IS_DEVELOPMENT

#include <iostream>
#include "..\ConfManager\ConfigReader.h"

#define TPRIORITY_LOW_BELOW				CM->getNumber(CM->PRIORITY_LOW_BELOW)
#define TPRIORITY_LOW_ABOVE				CM->getNumber(CM->PRIORITY_LOW_ABOVE)
#define TPRIORITY_MEDIUM_BELOW			CM->getNumber(CM->PRIORITY_MEDIUM_BELOW)
#define TPRIORITY_MEDIUM_ABOVE			CM->getNumber(CM->PRIORITY_MEDIUM_ABOVE)
#define TPRIORITY_HIGH_BELOW			CM->getNumber(CM->PRIORITY_HIGH_BELOW)
#define TPRIORITY_HIGH_ABOVE			CM->getNumber(CM->PRIORITY_HIGH_ABOVE)
#define TPRIORITY_CRITICAL_BELOW		CM->getNumber(CM->PRIORITY_CRITICAL_BELOW)
#define TPRIORITY_CRITICAL_ABOVE		CM->getNumber(CM->PRIORITY_CRITICAL_ABOVE)

#define CHECK_INRANGE(Highest, Lowest)  Players <= Highest && !(Players < Lowest)

#define LEVEL_LOW		1
#define LEVEL_MEDIUM	2
#define LEVEL_HIGH		3
#define LEVEL_CRITICAL	4
#define LEVEL_DEAD		-1

class _PriorityEngine
{
protected:

public:

	short GetPriorityLevel(unsigned long long Players, ConfigManager* CM)
	{
		if (CHECK_INRANGE(TPRIORITY_LOW_BELOW, TPRIORITY_HIGH_ABOVE))
			return LEVEL_LOW;
		if (CHECK_INRANGE(TPRIORITY_MEDIUM_BELOW, TPRIORITY_MEDIUM_ABOVE))
			return LEVEL_MEDIUM;
		if (CHECK_INRANGE(TPRIORITY_HIGH_BELOW, TPRIORITY_HIGH_ABOVE))
			return LEVEL_HIGH;
		if (CHECK_INRANGE(TPRIORITY_CRITICAL_BELOW, TPRIORITY_CRITICAL_ABOVE))
			return LEVEL_CRITICAL;
		if (Players > TPRIORITY_CRITICAL_ABOVE)
			return LEVEL_DEAD;
		return LEVEL_DEAD;
	}
};

#endif

#endif