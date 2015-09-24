#include "main-army-agent.hh"

#include <BWAPI/Game.h>
#include <BWAPI/RegionSet.h>
#include <BWAPI/Region.h>

#include <iostream>

MainArmyAgent::MainArmyAgent()
{

}

void MainArmyAgent::protected_init()
{

}

void MainArmyAgent::protected_clear()
{

}

void MainArmyAgent::protected_on_frame()
{
}

void MainArmyAgent::scout()
{

}

void MainArmyAgent::protected_on_unit_completed(ArmyAgent* a)
{
	add_sub_agent(a);
	army_agents_.insert(a);
}

