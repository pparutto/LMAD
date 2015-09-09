#include "main-eco-agent.hh"

#include "worker-agent.hh"

MainEcoAgent::MainEcoAgent()
{
}

void MainEcoAgent::init()
{
	for (auto e : bases_)
	{
		delete e;
	}
	bases_.clear();

	for (auto w : waiting_workers_)
	{
		delete w;
	}

	waiting_workers_.clear();
}

void
MainEcoAgent::protected_run()
{
	for (EcoAgent* e: eco_agents_)
		e->run();

	for (BaseAgent* b : bases_)
	{
		b->run();
	}
}

void
MainEcoAgent::add_worker(const BWAPI::Unit& u)
{
	WorkerAgent* wo = new WorkerAgent(u);

	eco_agents_.insert(wo);

	if (bases_.size())
	{
		(*(bases_.begin()))->associate_worker(wo);
	}
	else
	{
		waiting_workers_.insert(wo);
	}
}

void
MainEcoAgent::add_HQ(const BWAPI::Unit& u)
{
	HQAgent* hq = new HQAgent(u);
	BaseAgent* base_agent = new BaseAgent(hq);

	if (!bases_.size())
	{
		for (auto w : waiting_workers_)
		{
			base_agent->associate_worker(w);
		}
		waiting_workers_.clear();
	}

	bases_.insert(base_agent);
}
