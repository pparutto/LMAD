#include <iostream>
#include "IA.h"

#include <BWAPI.h>
#include <BWAPI/Client.h>

#include "agent/main-eco-agent.hh"

using namespace BWAPI;

class Behavior
{
public:
	Behavior(const Unit u)
		: in_progress_(false)
		, unit_(u)
	{
	}

protected:
	bool in_progress_;
	const Unit unit_;
};

class WorkerBehavior : public UnitType, public Behavior
{
public:
	WorkerBehavior(const Unit u):
		Behavior(u)
	{}

	Unit closest_mineral(const Unit u)
	{
		Unit res = nullptr;
		Unitset minerals = Broodwar->getMinerals();

		for (auto &m : minerals)
		{
			if (!res || u->getDistance(m) < u->getDistance(res))
				res = m;
		}
		return res;
	}

	void collect(bool force)
	{
		if (force || !in_progress_)
		{
			Unit cm = closest_mineral(unit_);
			if (cm)
			{
				unit_->rightClick(cm);
				in_progress_ = true;
			}
		}
	}
};


class HQBehavior : public UnitType, public Behavior
{
public:
	HQBehavior(const Unit u) :
		Behavior(u)
	{}

	void produce_worker()
	{
		if (Broodwar->self()->minerals() >= UnitTypes::Protoss_Probe.mineralPrice())
			unit_->train(Broodwar->self()->getRace().getWorker());
	}
};

void ia()
{
	MainEcoAgent* eco = new MainEcoAgent();

	for (const Unit& u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker())
			eco->add_worker(u);
		else if (u->getType().isResourceDepot())
			eco->add_HQ(u);
	}

	eco->run();

	while (Broodwar->isInGame())
	{
		eco->run();
		for (auto &e : Broodwar->getEvents())
		{
			switch (e.getType())
			{
			case EventType::UnitComplete:
				Unit u = e.getUnit();
				if (u->getPlayer()->getID() == Broodwar->self()->getID())
				{
					if (u->getType().isWorker())
						eco->add_worker(u);
				}
				break;
			}
		}
		//std::cout << "yolo" << std::endl;
		Broodwar->sendText("proute");
		BWAPIClient.update();
	}
}