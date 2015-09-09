#include "game-info.hh"

#include <BWAPI/Client.h>
#include <BWAPI/Color.h>

#include <iostream>

MineralLine::MineralLine(const int& region_id)
	: region_id_(region_id)
{
	std::cout << "---------------------mineral line created----------------------" << std::endl;
}

void MineralLine::init_gas(const BWAPI::Unit resource)
{
	gas_.insert(std::make_pair(resource, 1500));
}

void MineralLine::init_mineral(const BWAPI::Unit resource)
{
	mineral_patches_.insert(std::make_pair(resource, 1500));
}

bool MineralLine::add_if_near_gas(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		gas_.insert(std::make_pair(resource, 1500));
		return true;
	}
	return false;
}

bool MineralLine::add_if_near_mineral(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		mineral_patches_.insert(std::make_pair(resource, 1500));
		return true;
	}
	return false;
}


const bool MineralLine::is_near(const BWAPI::Unit resource) const
{
	bool res = false;
	double distance = 0;

	for (auto m : mineral_patches_)
	{
		distance = resource->getPosition().getDistance(m.first->getPosition());
		//std::cout << "distance : " << distance << std::endl;
		if (distance < 250)
		{
			return true;
		}
	}

	for (auto g : gas_)
	{
		distance = resource->getPosition().getDistance(g.first->getPosition());
		//std::cout << "distance : " << distance << std::endl;
		if (distance < 250)
		{
			return true;
		}
	}

	return false;
}

BWAPI::Position MineralLine::center_get() const
{
	int x = 0;
	int y = 0;
	int total = mineral_patches_.size() + gas_.size();

	for (auto m : mineral_patches_)
	{
		x += m.first->getPosition().x;
		y += m.first->getPosition().y;
	}

	for (auto g : gas_)
	{
		x += g.first->getPosition().x;
		y += g.first->getPosition().y;
	}

	x /= total;
	y /= total;

	BWAPI::Position res(x, y);
	return res;
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

	BWAPI::Unitset minerals = BWAPI::Broodwar->getStaticMinerals();
	BWAPI::Unitset gas = BWAPI::Broodwar->getStaticGeysers();

	for (auto mineral : minerals)
	{
		bool added = false;
		for (auto line : mineral_lines_)
		{
			if (line->add_if_near_mineral(mineral))
			{
				added = true;
				break;
			}
		}
		if (!added)
		{
			MineralLine* line = new MineralLine(0);
			line->init_mineral(mineral);
			mineral_lines_.insert(line);
		}
		//std::cout << "mineral " << mineral->getPosition() << ":" << mineral->getRegion()->getID() << std::endl;
	}

	for (auto g : gas)
	{
		bool added = false;
		for (auto line : mineral_lines_)
		{
			if (line->add_if_near_gas(g))
			{
				added = true;
				break;
			}
		}
		if (!added)
		{
			MineralLine* line = new MineralLine(0);
			line->init_gas(g);
			mineral_lines_.insert(line);
		}
		//std::cout << "gas " << g->getPosition() << ":" << g->getRegion()->getID() << std::endl;
	}

	std::cout << "Info end Init" << std::endl;
}

void GameInfo::debug()
{
	for (auto m : mineral_lines_)
	{
		BWAPI::Broodwar->drawCircleMap(m->center_get(), 20, BWAPI::Colors::Red);
	}
}