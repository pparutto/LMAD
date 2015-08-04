#include <iostream>
#include "IA.h"

#include <BWAPI.h>
#include <BWAPI/Client.h>
#include <set>

#include "agent/main-eco-agent.hh"
#include "agent/base-agent.hh"
#include "agent/main-army-agent.hh"

#include "utils/game-info.hh"

GameInfo* GameInfo::instance_ = 0;

class Behavior
{
public:
	Behavior(const BWAPI::Unit u)
		: in_progress_(false)
		, unit_(u)
	{
	}

protected:
	bool in_progress_;
	const BWAPI::Unit unit_;
};

class WorkerBehavior : public BWAPI::UnitType, public Behavior
{
public:
	WorkerBehavior(const BWAPI::Unit u) :
		Behavior(u)
	{}

	BWAPI::Unit closest_mineral(const BWAPI::Unit u)
	{
		BWAPI::Unit res = nullptr;
		BWAPI::Unitset minerals = BWAPI::Broodwar->getMinerals();

		for (auto &m : minerals)
		{
			if (!res || u->getDistance(m) < u->getDistance(res))
				res = m;
		}
		return res;
	}

};


class HQBehavior : public BWAPI::UnitType, public Behavior
{
public:
	HQBehavior(const BWAPI::Unit u) :
		Behavior(u)
	{}

	void produce_worker()
	{
		if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Probe.mineralPrice())
			unit_->train(BWAPI::Broodwar->self()->getRace().getWorker());
	}
};

void ia()
{
	MainEcoAgent* eco = new MainEcoAgent();
	BaseAgent* main_base = nullptr;
	MainArmyAgent* army = new MainArmyAgent();

	for (const BWAPI::Unit& u : BWAPI::Broodwar->self()->getUnits())
	{
		if (u->getType().isResourceDepot())
		{
			HQAgent* hq = new HQAgent(u);
			eco->add_HQ(hq);
			main_base = new BaseAgent(hq);
		}
	}
			BWAPI::Unit cm = closest_mineral(unit_);
			if (cm)
			{
				unit_->rightClick(cm);
				in_progress_ = true;
			}
		}
	}

	eco->run();

	GameInfo::instance_get()->init();

	while (BWAPI::Broodwar->isInGame())
	{
		//GameInfo::instance_get()->init();
		eco->run();
		main_base->create_pylon();
		for (auto &e : BWAPI::Broodwar->getEvents())
		{
			switch (e.getType())
			{
			case BWAPI::EventType::UnitComplete:
				BWAPI::Unit u = e.getUnit();
				if (u->getPlayer()->getID() == BWAPI::Broodwar->self()->getID())
				{
					if (u->getType().isWorker())
					{
						WorkerAgent* wo = new WorkerAgent(u);
						eco->add_worker(wo);
						main_base->associate_worker(wo);
					}
					else if (!u->getType().isBuilding())
					{
						army->add_unit(u);
					}
				}
				break;
			}
		}


		BWAPI::BWAPIClient.update();
	}

	GameInfo::instance_clean();
}
