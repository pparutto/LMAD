#include "base-agent.hh"

#include "requests/requests.hh"

#include "../utils/utils.hh"
#include "../utils/game-info.hh"

#include <BWAPI/Position.h>
#include <BWAPI.h>

BaseAgent::BaseAgent(BuildingAgent* hq)
	: hq_(hq)
	, gates_number_(0)
	, cores_number_(0)
	, build_extra_workers_(false)
{
	add_sub_agent(hq_);
	mineral_line_ = GameInfo::instance_get()->get_nearest_mineral_line(hq_->unit_get()->getPosition());
	mineral_line_->base_set(this);
}

BaseAgent::~BaseAgent()
{
}

void
BaseAgent::protected_on_frame()
{
/*	std::cout << "--------------------------------" << std::endl;

	for (auto m : mineral_line_->mineral_patches_get())
	{
		std::cout << "mineral distance : " << m->unit_get()->getTilePosition().getDistance(hq_->unit_get()->getTilePosition()) << std::endl;
	}

	for (auto g : mineral_line_->gas_get())
	{
		std::cout << "mineral distance : " << g->unit_get()->getTilePosition().getDistance(hq_->unit_get()->getTilePosition()) << std::endl;
	}
	*/

//	BWAPI::Broodwar->drawCircleMap(utils::tile_to_pos(hq_->unit_get()->getTilePosition()), 20, BWAPI::Colors::Black);

	if (workers_.size() < (max_mineral_ + max_gas_) || build_extra_workers_)
	{
		hq_->train_unit(BWAPI::UnitTypes::Protoss_Probe);
	}
	
	for (auto g : mineral_line_->gas_get())
	{
		for (auto w : workers_)
		{
			if (g->assimilator_get() && g->worker_count() < max_gas_)
			{
				if (!w->has_orders_get())
				{
					w->resource_set(g);
				}
			}
			else
			{
				break;
			}
		}
	}
}

void BaseAgent::protected_on_unit_destroyed(WorkerAgent* w)
{
	workers_.erase(w);
	remove_sub_agent(w);
}

void
BaseAgent::associate_worker(WorkerAgent* w)
{
	add_sub_agent(w);
	workers_.insert(w);
	find_best_resource(w);
}

void BaseAgent::find_best_resource(WorkerAgent* w)
{
	std::set<Resource*> minerals = mineral_line_->mineral_patches_get();

	BWAPI::Position pos = hq_->unit_get()->getPosition();

	unsigned int best_count = 10;
	double best_dist = DBL_MAX;
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

	if (best_resource == nullptr)
	{
		std::cerr << "no best resource" << std::endl;
	}
	w->resource_set(best_resource);
}

void BaseAgent::reallocate_workers()
{
	for (auto w : workers_)
	{
		Resource* r = w->resource_get();
		if (!w->has_orders_get() && !w->is_harvesting_get())
		{
			if (r && r->unit_get()->getType() != BWAPI::UnitTypes::Protoss_Assimilator &&
				r->worker_count() > 1)
			{
				w->resource_set(nullptr);
				find_best_resource(w);
			}
		}
	}
}

void BaseAgent::set_max_workers_gas(const unsigned nb)
{
	max_gas_ = nb;
	int nb_gas_needed = (nb + 2) / 3;
	int current_gas = 0;

	for (auto g : mineral_line_->gas_get())
	{
		if (g->assimilator_get() || g->has_assimilator_request_get())
		{
			++current_gas;
		}
	}

	if (current_gas < nb_gas_needed)
	{
		for (auto g : mineral_line_->gas_get())
		{
			if (!(g->assimilator_get()) && !(g->has_assimilator_request_get()))
			{
				BuildingRequest* r = new BuildingRequest(BWAPI::UnitTypes::Protoss_Assimilator);
				this->request(r);
				g->has_assimilator_request_set(true);
				++current_gas;
				if (current_gas == nb_gas_needed)
				{
					break;
				}
			}
		}
	}
}

/****************************************************************************
************************ PYLON REQUEST **************************************
*****************************************************************************/

void BaseAgent::accept(BuildingRequest* r)
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(r->data_get());
	BWAPI::UnitType building_type = data->building_type_get();

	switch (data->phase_get())
	{
	case BuildingRequest::INIT:
	{
		if (building_type == BWAPI::UnitTypes::Protoss_Gateway)
		{
			++gates_number_;
		}
		else if (building_type == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
		{
			++cores_number_;
		}
		data->phase_set(BuildingRequest::CHECKMONEY);
		break;
	}
	case BuildingRequest::CHECKMONEY:
	{
		if (GameInfo::instance_get()->bank_get()->request_resources(data->building_type_get().mineralPrice(), data->building_type_get().gasPrice()))
		{
			data->phase_set(BuildingRequest::FINDWORKER);
		}
		break;
	}
	case BuildingRequest::FINDWORKER:
	{
		data->timeout_set(100);

		BWAPI::TilePosition pos;

		if (building_type.requiresPsi())
		{
			pos = utils::find_valid_position_near_pylon(building_type, pylons_);
		}
		else
		{
			if (building_type == BWAPI::UnitTypes::Protoss_Pylon)
			{
				pos = utils::find_valid_location_circle(hq_->unit_get()->getPosition(), 320, building_type);
			}
			else if (building_type == BWAPI::UnitTypes::Protoss_Assimilator)
			{
				for (auto r : mineral_line_->gas_get())
				{
					if (r->assimilator_get() == nullptr)
					{
						pos = r->tile_position_get();
						break;
					}
				}
			}
			else if (building_type == BWAPI::UnitTypes::Protoss_Nexus)
			{
				MineralLine* line = GameInfo::instance_get()->get_nearest_mineral_line(mineral_line_, true);
				if (!line)
				{
					//handle request error
				}
				else
				{
					pos = line->get_nexus_position();
				}
			}
		}

		if (pos != BWAPI::TilePositions::Invalid)
		{
			WorkerAgent* best_worker = nullptr;
			double best_distance = DBL_MAX;
			GameInfo::instance_get()->remove_building_request_position(data->position_get());
			GameInfo::instance_get()->add_building_request_position(pos, building_type);

			for (auto w : workers_)
			{
				if (!w->has_orders_get())
				{
					double distance = w->unit_get()->getPosition().getApproxDistance(utils::tile_to_pos(pos));
					if (distance < best_distance)
					{
						best_distance = distance;
						best_worker = w;
					}
				}
			}
			if (best_worker)
			{
				double speed = best_worker->unit_get()->getType().topSpeed();
				double distance = best_worker->unit_get()->getPosition().getApproxDistance(utils::tile_to_pos(pos));
				double nb_frame = distance / speed;
				data->position_set(pos);
				data->timeout_set((unsigned int)nb_frame + 100);
				data->phase_set(BuildingRequest::MOVE_AND_BUILD);
				data->worker_set(best_worker);
				best_worker->has_orders_set(true);
				best_worker->resource_set(nullptr);

				if (building_type == BWAPI::UnitTypes::Protoss_Nexus)
				{
					GameInfo::instance_get()->map_get()->get_path(utils::tile_to_pos(data->position_get()), best_worker->unit_get()->getPosition());
				}

			}
		}
		else
		{
			std::cerr << "invalid position" << std::endl;
		}
		break;
	}

	case BuildingRequest::MOVE_AND_BUILD:
	{
		BWAPI::Position current = data->worker_get()->unit_get()->getPosition();

		int x1 = data->position_get().x * BWAPI::TILEPOSITION_SCALE;
		int x2 = data->position_get().x * BWAPI::TILEPOSITION_SCALE + BWAPI::TILEPOSITION_SCALE;
		int y1 = data->position_get().y * BWAPI::TILEPOSITION_SCALE;
		int y2 = data->position_get().y * BWAPI::TILEPOSITION_SCALE + BWAPI::TILEPOSITION_SCALE;

		BWAPI::Position obj = BWAPI::Position((x1 + x2) / 2,
																					(y1 + y2) / 2);

		BWAPI::Broodwar->drawCircleMap(obj, 50, BWAPI::Colors::Green);
		BWAPI::Broodwar->drawCircleMap(current, 20, BWAPI::Colors::Red);

		if (data->timeout_get() == 0 && data->move_timeout_get() < 2)
		{
			data->move_timeout_increment();
			data->worker_get()->has_orders_set(false);
			find_best_resource(data->worker_get());
			data->phase_set(BuildingRequest::FINDWORKER);
		}
		else if (data->worker_get()->move(obj))
		{
			data->check_worker_position();
			if (data->is_worker_stuck())
			{
				std::cout << "try to build : " << data->building_type_get().getName() << " at position : " << data->position_get() << std::endl;
				if (data->worker_get()->unit_get()->build(data->building_type_get(), data->position_get()))
				{
					data->timeout_set(100);
					data->phase_set(BuildingRequest::RELEASE_WORKER);
				}
			}
		}
		else
		{
			std::cout << "try to build : " << data->building_type_get().getName() << " at position : " << data->position_get() << std::endl;
			if (data->worker_get()->unit_get()->build(data->building_type_get(), data->position_get()))
			{
				data->timeout_set(100);
				data->phase_set(BuildingRequest::RELEASE_WORKER);
			}
		}
		break;
	}

	case BuildingRequest::RELEASE_WORKER:
	{
		data->phase_set(BuildingRequest::CHECK_CREATION);
		break;
	}

	case BuildingRequest::CHECK_CREATION:
	{
		if (r->is_created())
		{
			data->worker_get()->has_orders_set(false);
			find_best_resource(data->worker_get());
			data->phase_set(BuildingRequest::CHECK_COMPLETION);
		}
		else if (data->timeout_get() == 0)
		{
			data->worker_get()->has_orders_set(false);
			find_best_resource(data->worker_get());
			data->phase_set(BuildingRequest::FINDWORKER);
		}
		break;
	}

	case BuildingRequest::CHECK_COMPLETION:
	{
		if (r->is_completed())
		{
			if (data->building_type_get() == BWAPI::UnitTypes::Protoss_Pylon)
			{
				if (data->result_get())
				{
					pylons_.insert(data->result_get());
				}
				else
				{
					std::cerr << "NULL BUILDING" << std::endl;
				}
			}
			data->phase_set(BuildingRequest::END);
		}
		else if (r->is_dead())
		{
			std::cout << "Pylon got killed :(, retrying" << std::endl;
			data->phase_set(BuildingRequest::FINDWORKER);
		}
		break;
	}

	case BuildingRequest::END:
	{
		if (data->building_type_get() == BWAPI::UnitTypes::Protoss_Assimilator)
		{
			for (auto g : mineral_line_->gas_get())
			{
				if (g->tile_position_get() == data->position_get())
				{
					g->assimilator_set(data->result_get());
				}
			}
		}
		break;
	}

	}

}
