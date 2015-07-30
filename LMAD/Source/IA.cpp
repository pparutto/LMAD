#include <iostream>
#include "IA.h"

#include <BWAPI.h>
#include <BWAPI/Client.h>

using namespace BWAPI;

void ia()
{
	while (Broodwar->isInGame())
	{
		Broodwar->sendText("proute");
		BWAPIClient.update();
	}
}