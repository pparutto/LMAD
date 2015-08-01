#include "main-eco-agent.hh"

#include "worker-agent.hh"

void
MainEcoAgent::run()
{
	for (EcoAgent* e: eco_agents_)
		e->run();

	for (HQAgent* e : HQs_)
		e->run();
}

void
MainEcoAgent::add_worker(const BWAPI::Unit u)
{
	WorkerAgent* wu = new WorkerAgent(u);
	eco_agents_.insert(wu);
	workers_.insert(wu);
}

void
MainEcoAgent::add_HQ(const BWAPI::Unit u)
{
	HQAgent* wu = new HQAgent(u);
	//eco_agents_.insert(wu);
	HQs_.insert(wu);
}