#include "main-eco-agent.hh"

#include "worker-agent.hh"

#include "requests/requests.hh"

MainEcoAgent::MainEcoAgent()
	: r_(nullptr)
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
	if (BWAPI::Broodwar->self()->supplyTotal() - BWAPI::Broodwar->self()->supplyUsed() <= 2)
	{
		if (bases_.size())
		{
			if (!r_)
			{
				r_ = new PylonRequest();
				(*(bases_.begin()))->request(r_);
			}
		}
	}
	else if (r_)
	{
		r_ = nullptr;
	}
}

void
MainEcoAgent::add_worker(BWAPI::Unit u)
{
	WorkerAgent* wo = new WorkerAgent(u);

	eco_agents_.insert(wo);

	if (bases_.size())
	{
		(*(bases_.begin()))->associate_worker(wo);
	}
	else
	{
		add_sub_agent(wo);
		waiting_workers_.insert(wo);
	}
}

void
MainEcoAgent::add_HQ(BWAPI::Unit u)
{
	HQAgent* hq = new HQAgent(u);
	BaseAgent* base_agent = new BaseAgent(hq);

	if (!bases_.size())
	{
		for (auto w : waiting_workers_)
		{
			remove_sub_agent(w);
			base_agent->associate_worker(w);
		}
		waiting_workers_.clear();
	}

	add_sub_agent(base_agent);
	bases_.insert(base_agent);
}

void MainEcoAgent::protected_on_unit_created(UnitAgent* u)
{
}

void MainEcoAgent::protected_on_unit_completed(UnitAgent* u)
{
}

void MainEcoAgent::protected_on_unit_destroyed(UnitAgent* u)
{
}
