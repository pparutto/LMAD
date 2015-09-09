#include "main-army-agent.hh"

#include <BWAPI/Game.h>
#include <BWAPI/RegionSet.h>
#include <BWAPI/Region.h>

#include <iostream>

MainArmyAgent::MainArmyAgent()
{

}

void MainArmyAgent::init()
{

}

void MainArmyAgent::protected_run()
{
	std::set<ArmyAgent*>::iterator it = army_agents_.begin();
	std::set<ArmyAgent*>::iterator e = army_agents_.end();

	while (it != e)
	{
		(*it)->run();
		++it;
	}
}

void MainArmyAgent::scout()
{

}

void MainArmyAgent::add_unit(const BWAPI::Unit& u)
{
	ArmyAgent* a = new ArmyAgent(u);
	army_agents_.insert(a);
}