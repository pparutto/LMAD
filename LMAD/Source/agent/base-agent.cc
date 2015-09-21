#include "base-agent.hh"

#include "requests/requests.hh"

#include "utils.hh"
#include "../utils/game-info.hh"

#include <BWAPI/Position.h>

BaseAgent::BaseAgent(HQAgent* hq)
	: hq_(hq)
{
	add_sub_agent(hq_);
	set_max_workers(16, 0);
	mineral_line_ = GameInfo::instance_get()->get_nearest_mineral_line(hq_->unit_get()->getPosition());
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
	std::set<Resource*> minerals = mineral_line_->mineral_patches_get();

	unsigned int best_count = 10;
	double best_dist = DBL_MAX;
	BWAPI::Position pos = hq_->unit_get()->getPosition();

	Resource* best_resource = nullptr;

	for (auto m : minerals)
	{
		if (m->worker_count() < best_count)
		{
			best_count = m->worker_count();
			best_dist = pos.getDistance(m->position_get());
			best_resource = m;
		}
		else if (m->worker_count() == best_count)
		{
			double distance = pos.getDistance(m->position_get());
			if (distance < best_dist)
			{
				best_dist = distance;
				best_resource = m;
			}
		}
	}

	w->resource_set(best_resource);
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
	case PylonRequest::CHECKMONEY:
	{
		if (GameInfo::instance_get()->bank_get()->request_mineral(100))
		{
			data->phase_set(PylonRequest::FINDWORKER);
		}
		break;
	}
	case PylonRequest::FINDWORKER:
	{
		data->timeout_set(100);
		for (auto w : workers_)
		{
			if (!w->has_orders_get())
			{
				w->has_orders_set(true);
				data->position_set(utils::find_valid_location_circle(hq_->unit_get()->getPosition(), 320, BWAPI::UnitTypes::Protoss_Pylon));
				data->phase_set(PylonRequest::MOVE_AND_BUILD);
				data->worker_set(w);
				break;
			}
		}
		break;
	}

	case PylonRequest::MOVE_AND_BUILD:
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
				data->phase_set(PylonRequest::RELEASE_WORKER);

			}
		}
		break;
	}

	case PylonRequest::RELEASE_WORKER:
	{
		data->phase_set(PylonRequest::CHECK_CREATION);
		break;
	}

	case PylonRequest::CHECK_CREATION:
	{
		if (r->is_created())
		{
			data->worker_get()->has_orders_set(false);
			data->phase_set(PylonRequest::CHECK_COMPLETION);
		}
		else if (data->timeout_get() == 0)
		{
			data->phase_set(PylonRequest::FINDWORKER);
		}
		break;
	}

	case PylonRequest::CHECK_COMPLETION:
	{
		if (r->is_completed())
		{
			data->phase_set(PylonRequest::END);
		}
		else if (r->is_dead())
		{
			std::cout << "Pylon got killed :(, retrying" << std::endl;
			data->phase_set(PylonRequest::FINDWORKER);
		}
		break;
	}

	case PylonRequest::END:
	{
		//std::cout << "Pylon request finished" << std::endl;
		on_request_ended(r);
		break;
	}

	}

	//create_pylon();
}
