#include <iostream>
#include "IA.h"

#include <BWAPI.h>
#include <BWAPI/Client.h>

#include "agent/main-eco-agent.hh"
#include "agent/base-agent.hh"

using namespace BWAPI;

void ia()
{
	MainEcoAgent* eco = new MainEcoAgent();
	BaseAgent* main_base = nullptr;

	for (const Unit& u : Broodwar->self()->getUnits())
	{
		if (u->getType().isResourceDepot())
		{
			HQAgent* hq = new HQAgent(u);
			eco->add_HQ(hq);
			main_base = new BaseAgent(hq);
		}
	}

	for (const Unit& u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker())
		{
			WorkerAgent* wo = new WorkerAgent(u);
			eco->add_worker(wo);
			main_base->associate_worker(wo);
		}
	}

	eco->run();

	while (Broodwar->isInGame())
	{
		eco->run();
		main_base->create_pylon();
		for (auto &e : Broodwar->getEvents())
		{
			switch (e.getType())
			{
			case EventType::UnitComplete:
				Unit u = e.getUnit();
				if (u->getPlayer()->getID() == Broodwar->self()->getID())
				{
					if (u->getType().isWorker())
					{
						WorkerAgent* wo = new WorkerAgent(u);
						eco->add_worker(wo);
						main_base->associate_worker(wo);
					}
				}
				break;
			}
		}
		//std::cout << "yolo" << std::endl;
		Broodwar->sendText("proute");
		BWAPIClient.update();
	}
}