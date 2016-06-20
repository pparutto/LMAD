#include "worker-agent.hh"

#include "../utils/game-info.hh"

#include "../utils/utils.hh"
#include "requests/request.hh"

WorkerAgent::WorkerAgent(BWAPI::Unit u)
	: UnitAgent(u)
	, has_orders_(false)
	, mineral_(0)
	, gas_(0)
	, resource_(nullptr)
	, is_harvesting_(false)
{
}

WorkerAgent::~WorkerAgent()
{
}

void
WorkerAgent::protected_on_frame()
{
	if (!has_orders_)
	{
		if (resource_)
		{
			if (unit_get()->isCarryingMinerals())
			{
				if (mineral_ == 0)
				{
					unsigned remaining_resources = resource_->unit_get()->getResources();
					mineral_ = last_remaining_resources_ - remaining_resources;
					resource_->is_being_gathered_set(false);
					unit_get()->returnCargo();
					is_harvesting_ = false;
				}

			}
			else if (unit_get()->isCarryingGas())
			{
				if (gas_ == 0)
				{
					unsigned remaining_resources = resource_->unit_get()->getResources();
					gas_ = last_remaining_resources_ - remaining_resources;
					resource_->is_being_gathered_set(false);
					is_harvesting_ = false;
					unit_get()->returnCargo();
				}
			}
			else
			{
				if (!is_harvesting_)
				{
					unit_get()->rightClick(resource_->unit_get());

//					if (!(resource_->is_being_gathered_get()))
					if (!(resource_->unit_get()->isBeingGathered()))
					{
						is_harvesting_ = true;
						harvest_frames_ = 0;
						resource_->is_being_gathered_set(true);
						unsigned remaining_resources = resource_->unit_get()->getResources();
						last_remaining_resources_ = remaining_resources;
					}
				}
				else 
				{
					if (!(resource_->unit_get()->isBeingGathered()))
					{
						if (resource_->unit_get()->getType() == BWAPI::UnitTypes::Protoss_Assimilator || harvest_frames_ >= 50)
						{
							resource_->is_being_gathered_set(false);
						}
						++harvest_frames_;
					}
				}

				if (mineral_)
				{
					GameInfo::instance_get()->bank_get()->add_mineral(8);
					mineral_ = 0;
				}
				else if (gas_)
				{
					GameInfo::instance_get()->bank_get()->add_gas(8);
					gas_ = 0;
				}
			}
		}
	}
}

void WorkerAgent::resource_set(Resource* resource)
{
	if (resource_)
	{
		if (is_harvesting_)
		{
			is_harvesting_ = false;
			resource_->is_being_gathered_set(false);
		}
		resource_->remove_worker(this);
	}
	resource_ = resource;
	if (resource_)
	{
		resource->add_worker(this);
		last_remaining_resources_ = resource->unit_get()->getResources();
	}
}

Resource* WorkerAgent::resource_get() const
{
	return resource_;
}

void WorkerAgent::protected_clear()
{
	UnitAgent::protected_clear();
}

void WorkerAgent::has_orders_set(const bool orders)
{
	if (!has_orders_ && orders)
	{
		if (is_harvesting_)
		{
			if (resource_)
			{
				resource_->is_being_gathered_set(false);
			}
			is_harvesting_ = false;
		}
	}
	has_orders_ = orders;
	if (!orders)
	{
		if (unit_get()->isCarryingGas() || unit_get()->isCarryingMinerals())
		{
			unit_get()->returnCargo();
		}
	}
}

VISIT_DEFINITIONS(WorkerAgent);