#include "worker-agent.hh"

#include "../utils/game-info.hh"

#include "utils.hh"

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
				if (!(resource_->is_being_gathered_get()))
				{
					is_harvesting_ = true;
					resource_->is_being_gathered_set(true);
					unsigned remaining_resources = resource_->unit_get()->getResources();
					last_remaining_resources_ = remaining_resources;
				}
			}

			if (mineral_)
			{
				GameInfo::instance_get()->bank_get()->add_mineral(mineral_);
				mineral_ = 0;
			}
			else if (gas_)
			{
				GameInfo::instance_get()->bank_get()->add_gas(gas_);
				gas_ = 0;
			}
		}
	}
}

void WorkerAgent::resource_set(Resource* resource)
{
	if (resource_)
	{
		resource_->remove_worker(this);
	}
	resource_ = resource;
	if (resource_)
	{
		resource->add_worker(this);
	}
	last_remaining_resources_ = resource->unit_get()->getResources();
}

Resource* WorkerAgent::resource_get() const
{
	return resource_;
}

void WorkerAgent::protected_clear()
{
	UnitAgent::protected_clear();
}
