#include "main-army-agent.hh"

void MainArmyAgent::run()
{
	std::set<ArmyAgent*>::iterator it = army_agents_.begin();
	std::set<ArmyAgent*>::iterator e = army_agents_.end();

	while (it != e)
	{
		(*it)->run();
		++it;
	}
}