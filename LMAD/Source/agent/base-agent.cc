#include "base-agent.hh"

#include "requests/requests.hh"

#include "utils.hh"

#include <BWAPI/Position.h>

BaseAgent::BaseAgent(HQAgent* hq)
	: hq_(hq)
{
	add_sub_agent(hq_);
	set_max_workers(16, 0);
}

BaseAgent::~BaseAgent()
{
}

void
BaseAgent::protected_on_frame()
{
	if (workers_.size() < max_mineral_)
	{
		hq_->train_worker();
	}
}

void
BaseAgent::associate_worker(WorkerAgent* w)
{
	add_sub_agent(w);
	workers_.insert(w);
}

void
BaseAgent::create_pylon()
{
	/*
	WorkerAgent* w = *workers_.begin();
	//std::cout << hq_->unit()->getPosition() << " |||| " << p << std::endl;

	//std::cout << BWAPI::Broodwar->canBuildHere(p, BWAPI::UnitTypes::Protoss_Pylon, nullptr, true) << std::endl;
	if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Pylon.mineralPrice())
	{
		//w->unit()->move(static_cast<BWAPI::Position>(p));
		//std::cout << w->unit()->build(BWAPI::UnitTypes::Protoss_Pylon, p) << std::endl;
		w->unit_get()->build(BWAPI::UnitTypes::Protoss_Pylon, p);
	}*/
}

void 
BaseAgent::create_gate()
{
	//BWAPI::TilePosition p = utils::find_valid_location_circle((*pylons_.begin())->getPosition(), BWAPI::UnitTypes::Protoss_Pylon., BWAPI::UnitTypes::Protoss_Pylon);
}

void BaseAgent::accept(PylonRequest* r)
{
	PylonRequestData* data = static_cast<PylonRequestData*>(r->data_get());

	switch (data->phase_get())
	{

	case 0:
	{
		data->timeout_set(100);
		for (auto w : workers_)
		{
			if (!w->has_orders_get())
			{
				w->has_orders_set(true);
				data->position_set(utils::find_valid_location_circle(hq_->unit_get()->getPosition(), 320, BWAPI::UnitTypes::Protoss_Pylon));
				data->phase_set(1);
				data->worker_set(w);
				break;
			}
		}
		break;
	}

	case 1:
	{
		BWAPI::Position current = data->worker_get()->unit_get()->getPosition();

		int x1 = data->position_get().x * BWAPI::TILEPOSITION_SCALE;
		int x2 = data->position_get().x * BWAPI::TILEPOSITION_SCALE + BWAPI::TILEPOSITION_SCALE;
		int y1 = data->position_get().y * BWAPI::TILEPOSITION_SCALE;
		int y2 = data->position_get().y * BWAPI::TILEPOSITION_SCALE + BWAPI::TILEPOSITION_SCALE;

		BWAPI::Position obj = BWAPI::Position((x1 + x2) / 2,
																					(y1 + y2) / 2);

		BWAPI::Broodwar->drawCircleMap(obj, 20, BWAPI::Colors::Red);
		BWAPI::Broodwar->drawCircleMap(current, 20, BWAPI::Colors::Red);


		if (current != obj)
		{
			data->worker_get()->unit_get()->move(obj);
		}
		else
		{
			if (data->worker_get()->unit_get()->build(BWAPI::UnitTypes::Protoss_Pylon, data->position_get()))
			{
				data->timeout_set(100);
				data->phase_set(2);
			}
		}
		break;
	}

	case 2:
	{
		if (r->is_created())
		{
			data->phase_set(3);
		}
		else if (data->timeout_get() == 0)
		{
			data->phase_set(2);
		}
		break;
	}

	case 3:
	{
		if (r->is_completed())
		{
			data->phase_set(4);
		}
		else if (r->is_dead())
		{
			std::cout << "Pylon got killed :(, retrying" << std::endl;
			data->phase_set(2);
		}
		break;
	}

	case 4:
	{
		std::cout << "Pylon request finished" << std::endl;
		
		break;
	}

	}

	//create_pylon();
}
