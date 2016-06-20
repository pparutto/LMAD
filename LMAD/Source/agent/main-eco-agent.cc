#include "main-eco-agent.hh"

#include "worker-agent.hh"

#include "requests/requests.hh"

MainEcoAgent::MainEcoAgent()
	: r_(nullptr)
	, rg_(nullptr)
	, rga_(nullptr)
	, rgc_(nullptr)
	, rg2_(nullptr)
	, rg3_(nullptr)
	, exp_(nullptr)
	, main_base_(nullptr)
{
}

void MainEcoAgent::protected_init()
{
}

void MainEcoAgent::protected_clear()
{
}

void MainEcoAgent::protected_on_frame()
{
	// FIXME : 2 sucks, it should be a dynamic value.

	BWAPI::Player self = BWAPI::Broodwar->self();

	int supply_used = self->supplyUsed();
	int supply_total = self->supplyTotal();

	bool need_extra_workers = false;
	for (auto b : bases_)
	{
		if (b->needs_workers() > 2)
		{
			need_extra_workers = true;
			break;
		}
	}

	for (auto b : bases_)
	{
		b->build_extra_workers_set(need_extra_workers);
	}

	if (supply_used <= 40)
	{
		if (BWAPI::Broodwar->self()->supplyTotal() - supply_used <= 4)
		{
			if (bases_.size())
			{
				if (!r_)
				{
					r_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Pylon);
					(*(bases_.begin()))->request(r_);
				}
			}
		}
		else if (r_)
		{
			r_ = nullptr;
		}
	}
	else
	{
		if (BWAPI::Broodwar->self()->supplyTotal() - supply_used <= 8)
		{
			if (bases_.size() && !r_)
			{
				for (auto b : bases_)
				{
					r_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Pylon);
					b->request(r_);
				}
			}
		}
		else if (r_)
		{
			r_ = nullptr;
		}
	}

	if (!exp_)
	{
		exp_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Nexus);
		(*(bases_.begin()))->request(exp_);
	}
	else
	{
		if ((exp_->data_get()->phase_get() == BuildingRequest::CHECK_COMPLETION) ||
			(exp_->data_get()->phase_get() == BuildingRequest::END))
		{
			if (supply_used >= 20)
			{
				for (auto b : bases_)
				{
					b->set_max_workers_gas(3);
				}
			}
			if (supply_used >= 22)
			{
				if (!rg_)
				{
					rg_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Gateway);
					(*(bases_.begin()))->request(rg_);
				}
				else
				{
					if (rg_->data_get()->phase_get() == BuildingRequest::END)
					{
						if (!rgc_)
						{
							rgc_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Cybernetics_Core);
							(*(bases_.begin()))->request(rgc_);
						}
						else if (rgc_->is_completed())
						{
							for (auto b : bases_)
							{
								if (b->gates_number_get() < 3)
								{
									rg3_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Gateway);
									b->request(rg3_);
								}
							}
/*							if (!rg2_)
							{
								rg2_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Gateway);
								rg3_ = new BuildingRequest(BWAPI::UnitTypes::Protoss_Gateway);
								(*(bases_.begin()))->request(rg2_);
								(*(bases_.begin()))->request(rg3_);
							}*/

						}
					}
				}
			}
		}
	}
}

void
MainEcoAgent::protected_on_unit_completed(WorkerAgent* a)
{
	if (bases_.size())
	{
		BaseAgent* producer;
		for (auto b : bases_)
		{
			if (b->nexus_position().getApproxDistance(a->unit_get()->getTilePosition()) < 5.f)
			{
				producer = b;
				break;
			}
		}

		if (producer->needs_workers())
		{
			producer->associate_worker(a);
		}
		else
		{
			for (auto b : bases_)
			{
				if (b->needs_workers())
				{
					b->associate_worker(a);
					break;
				}
			}
		}

	}
	else
	{
		add_sub_agent(a);
		waiting_workers_.insert(a);
	}
}

void
MainEcoAgent::protected_on_unit_completed(BuildingAgent* a)
{
	if (a->unit_get()->getType().isResourceDepot())
	{
		BaseAgent* base_agent = new BaseAgent(a);
		base_agent->set_max_workers_mineral(16);

		if (!bases_.size())
		{
			main_base_ = base_agent;
			for (auto w : waiting_workers_)
			{
				base_agent->associate_worker(w);
				remove_sub_agent(w);
			}
			waiting_workers_.clear();
		}

		add_sub_agent(base_agent);
		bases_.insert(base_agent);
	}
}
