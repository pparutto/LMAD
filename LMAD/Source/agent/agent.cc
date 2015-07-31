#include "agent.hh"

void Agent::run()
{
	std::set<Agent*>::iterator it = sub_agents_.begin();
	std::set<Agent*>::iterator e = sub_agents_.end();

	internal_run();

	while (it != e)
	{
		(*it)->run();
		++it;
	}
}