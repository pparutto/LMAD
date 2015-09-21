#include "game-info.hh"

#include <BWAPI/Client.h>
#include <BWAPI/Color.h>

#include <iostream>


/**
	BANK
**/

Bank::Bank(unsigned income_precision)
	: mineral_(50)
	, gas_(0)
	, income_precision_(income_precision)
	, mineral_income_(0)
	, gas_income_(0)
{
	mineral_incomes_ = new unsigned[income_precision_];
	for (unsigned i = 0; i < income_precision_; ++i)
	{
		mineral_incomes_[i] = 0;
	}

	gas_incomes_ = new unsigned[income_precision_];
	for (unsigned i = 0; i < income_precision_; ++i)
	{
		gas_incomes_[i] = 0;
	}

	indice_ = 0;
}


Bank::~Bank()
{
	delete[] mineral_incomes_;
	delete[] gas_incomes_;
}

void Bank::on_frame()
{
	BWAPI::Broodwar->drawTextScreen(25, 25, "Minerals : %i", mineral_);
	BWAPI::Broodwar->drawTextScreen(25, 50, "Gas : %i", gas_);
}

void Bank::add_gas(const int value)
{
	gas_ += value;
}

void Bank::add_mineral(const int value)
{
	mineral_ += value;
}

const bool Bank::request_mineral(const int value)
{
	if (mineral_ >= value)
	{
		mineral_ -= value;
		return true;
	}
	return false;
}

const bool Bank::request_gas(const int value)
{
	if (gas_ >= value)
	{
		gas_ -= value;
		return true;
	}
	return false;
}

/**
	RESOURCE
**/

Resource::Resource(BWAPI::Unit unit, BWAPI::Position position)
	: unit_(unit)
	, position_(position)
	, is_being_gathered_(false)
{

}

/**
	MINERAL LINE
**/

MineralLine::MineralLine(const int& region_id)
	: region_id_(region_id)
{
	std::cout << "---------------------mineral line created----------------------" << std::endl;
}

MineralLine::~MineralLine()
{
	for (auto m : mineral_patches_)
	{
		delete m;
	}

	for (auto g : gas_)
	{
		delete g;
	}
}

void MineralLine::init_gas(const BWAPI::Unit resource)
{
	Resource* res = new Resource(resource, resource->getPosition());
	gas_.insert(res);
}

void MineralLine::init_mineral(const BWAPI::Unit resource)
{
	Resource* res = new Resource(resource, resource->getPosition());
	mineral_patches_.insert(res);
}

bool MineralLine::add_if_near_gas(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		Resource* res = new Resource(resource, resource->getPosition());
		gas_.insert(res);
		return true;
	}
	return false;
}

bool MineralLine::add_if_near_mineral(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		Resource* res = new Resource(resource, resource->getPosition());
		mineral_patches_.insert(res);
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
		distance = resource->getPosition().getDistance(m->position_get());
		//std::cout << "distance : " << distance << std::endl;
		if (distance < 250)
		{
			return true;
		}
	}

	for (auto g : gas_)
	{
		distance = resource->getPosition().getDistance(g->position_get());
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
		x += m->position_get().x;
		y += m->position_get().y;
	}

	for (auto g : gas_)
	{
		x += g->position_get().x;
		y += g->position_get().y;
	}

	x /= total;
	y /= total;

	BWAPI::Position res(x, y);
	return res;
}

/**
	REGION
**/

Region::Region(BWAPI::Region region)
	: region_(region)
{

}

/**
	GAMEINFO
**/

GameInfo::GameInfo()
  : bank_(nullptr)
{
}

GameInfo::~GameInfo()
{
	for (auto l : mineral_lines_)
	{
		delete l;
	}
	delete bank_;
}

void GameInfo::on_frame()
{
	bank_->on_frame();
}

void GameInfo::init()
{
	std::cout << "Info Init" << std::endl;

	bank_ = new Bank(256);
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

void GameInfo::clear()
{
	if (bank_)
	{
		delete bank_;
		bank_ = nullptr;
	}

	for (auto l : mineral_lines_)
	{
		delete l;
	}

	mineral_lines_.clear();
}

void GameInfo::debug()
{
	for (auto m : mineral_lines_)
	{
		BWAPI::Broodwar->drawCircleMap(m->center_get(), 20, BWAPI::Colors::Red);
	}
}

MineralLine* GameInfo::get_nearest_mineral_line(BWAPI::Position position) const
{
	MineralLine* best_result = nullptr;
	double best_score = DBL_MAX;

	for (auto m : mineral_lines_)
	{
		double distance = m->center_get().getDistance(position);
		if (distance < best_score)
		{
			best_score = distance;
			best_result = m;
		}
	}

	return best_result;
}
