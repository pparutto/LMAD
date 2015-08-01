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
MainEcoAgent::add_worker(WorkerAgent* u)
{
	eco_agents_.insert(u);
	workers_.insert(u);
}

void
MainEcoAgent::add_HQ(HQAgent* u)
{
	HQs_.insert(u);
}

std::set<HQAgent*>&
MainEcoAgent::HQs()
{
	return HQs_;
}