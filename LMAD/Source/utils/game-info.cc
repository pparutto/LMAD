#include "game-info.hh"

#include <BWAPI/Client.h>
#include <BWAPI/Color.h>

#include <iostream>

MineralLine::MineralLine(const int& region_id,
	std::set<std::pair<BWAPI::Position, int> > mineral_patches,
	std::pair<BWAPI::Position, int> gas)
	: region_id_(region_id)
	, mineral_patches_(mineral_patches)
	, gas_(gas)
{

}

Region::Region(BWAPI::Region region)
	: region_(region)
{

}

GameInfo::GameInfo()
{

}

void GameInfo::init()
{
	std::cout << "Info Init" << std::endl;
	BWAPI::Regionset regions = BWAPI::Broodwar->getAllRegions();
	for (auto r : regions)
	{
		//Region* region = new Region(r);
		//regions_.insert(region);
		BWAPI::Broodwar->drawBoxMap(r->getBoundsLeft(), r->getBoundsTop(), r->getBoundsRight(), r->getBoundsBottom(), BWAPI::Colors::Blue);
	}

	std::cout << regions.size() << std::endl;

	BWAPI::Unitset minerals = BWAPI::Broodwar->getMinerals();
	BWAPI::Unitset gas = BWAPI::Broodwar->getGeysers();

	for (auto mineral : minerals)
	{
		std::cout << "mineral " << mineral->getPosition() << ":" << mineral->getRegion()->getID() << std::endl;
	}

	for (auto g : gas)
	{
		std::cout << "gas " << g->getPosition() << ":" << g->getRegion()->getID() << std::endl;
	}

	std::cout << "Info end Init" << std::endl;
}