#include "main-eco-agent.hh"

void MainEcoAgent::run()
{
	std::set<EcoAgent*>::iterator it = eco_agents_.begin();
	std::set<EcoAgent*>::iterator e = eco_agents_.end();

	while (it != e)
	{
		(*it)->run();
		++it;
	}
}