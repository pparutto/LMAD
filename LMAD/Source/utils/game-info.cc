#include "game-info.hh"

#include <BWAPI/Client.h>
#include <BWAPI/Color.h>

#include <iostream>

#include "../agent/base-agent.hh"
#include "../agent/army-agent.hh"

#include "utils.hh"

#define DISTANCE_TO_RESOURCES 5.f

/**
	BANK
**/

Bank::Bank(unsigned income_precision)
	: income_precision_(income_precision)
{
	mineral_incomes_ = new unsigned[income_precision_];
	gas_incomes_ = new unsigned[income_precision_];
}

void Bank::init()
{
	mineral_ = BWAPI::Broodwar->self()->minerals();
	gas_ = BWAPI::Broodwar->self()->gas();
	mineral_income_ = 0;
	gas_income_ = 0;
	total_mineral_ = 0;
	total_gas_ = 0;

	for (unsigned i = 0; i < income_precision_; ++i)
	{
		mineral_incomes_[i] = 0;
		gas_incomes_[i] = 0;
	}

	indice_ = 0;

}

void Bank::clear()
{

}

Bank::~Bank()
{
	delete[] mineral_incomes_;
	delete[] gas_incomes_;
}

void Bank::on_frame()
{
	total_mineral_ += mineral_incomes_[indice_];
	total_gas_ += gas_incomes_[indice_];

	mineral_income_ = (float) total_mineral_ / (float) income_precision_;
	gas_income_ = (float) total_gas_ / (float) income_precision_;

	++indice_;
	if (indice_ == income_precision_)
	{
		indice_ = 0;
	}

	total_mineral_ -= mineral_incomes_[indice_];
	total_gas_ -= gas_incomes_[indice_];
	mineral_incomes_[indice_] = 0;
	gas_incomes_[indice_] = 0;

}

void Bank::debug() const
{
	BWAPI::Broodwar->drawTextScreen(25, 25, "Minerals : %i", mineral_);
	BWAPI::Broodwar->drawTextScreen(25, 50, "Gas : %i", gas_);

	BWAPI::Broodwar->drawTextScreen(25, 75, "Minerals income : %f", mineral_income_);
	BWAPI::Broodwar->drawTextScreen(25, 100, "Gas income : %f", gas_income_);
}

void Bank::add_gas(const int value)
{
	gas_ += value;
	gas_incomes_[indice_] += value;
}

void Bank::add_mineral(const int value)
{
	mineral_ += value;
	mineral_incomes_[indice_] += value;
}

const bool Bank::request_resources(const int mineral, const int gas)
{
	if (mineral_ >= mineral && gas_ >= gas)
	{
		mineral_ -= mineral;
		gas_ -= gas;
		return true;
	}
	return false;
}


/**
	RESOURCE
**/

Resource::Resource(BWAPI::Unit unit, BWAPI::Position position, BWAPI::TilePosition tile_position)
	: unit_(unit)
	, position_(position)
	, tile_position_(tile_position)
	, is_being_gathered_(false)
	, assimilator_(nullptr)
	, has_assimilator_request_(false)
{

}

/**
	MINERAL LINE
**/

MineralLine::MineralLine(const int& region_id)
	: region_id_(region_id)
	, base_(nullptr)
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
	Resource* res = new Resource(resource, resource->getPosition(), resource->getTilePosition());
	gas_.insert(res);
}

void MineralLine::init_mineral(const BWAPI::Unit resource)
{
	Resource* res = new Resource(resource, resource->getPosition(), resource->getTilePosition());
	mineral_patches_.insert(res);
}

bool MineralLine::add_if_near_gas(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		Resource* res = new Resource(resource, resource->getPosition(), resource->getTilePosition());
		gas_.insert(res);
		return true;
	}
	return false;
}

bool MineralLine::add_if_near_mineral(const BWAPI::Unit resource)
{
	if (is_near(resource))
	{
		Resource* res = new Resource(resource, resource->getPosition(), resource->getTilePosition());
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
	int xmin = 0;
	int ymin = 0;

	int x;
	int y;

	for (auto m : mineral_patches_)
	{
		xmin += m->position_get().x;
		ymin += m->position_get().y;
	}

	if (gas_.size())
	{
		int xgas = 0;
		int ygas = 0;

		for (auto g : gas_)
		{
			xgas += g->position_get().x;
			ygas += g->position_get().y;
		}

		xgas /= gas_.size();
		ygas /= gas_.size();

		if (mineral_patches_.size())
		{
			xmin /= mineral_patches_.size();
			ymin /= mineral_patches_.size();

			x = (xmin + xgas) / 2;
			y = (ymin + ygas) / 2;
		}
		else
		{
			x = xgas;
			y = ygas;
		}
	}
	else
	{
		xmin /= mineral_patches_.size();
		ymin /= mineral_patches_.size();
		x = xmin;
		y = ymin;
	}

	BWAPI::Position res(x, y);

	return res;
}

BWAPI::TilePosition MineralLine::get_nexus_position()
{
	BWAPI::TilePosition res = BWAPI::TilePositions::Invalid;
	BWAPI::TilePosition center = utils::pos_to_tile(center_get());

	double best_max_distance = DBL_MAX;

	int height = BWAPI::UnitTypes::Protoss_Nexus.tileHeight();
	int width = BWAPI::UnitTypes::Protoss_Nexus.tileWidth();

	for (int i = -10; i <= 10; ++i)
	{
		for (int j = -10; j <= 10; ++j)
		{
			BWAPI::TilePosition pos_to_check;
			pos_to_check.x = center.x + i;
			pos_to_check.y = center.y + j;

			BWAPI::Position pos1 = utils::tile_to_pos(pos_to_check);

			BWAPI::TilePosition tmp;
			tmp.x = pos_to_check.x + width;
			tmp.y = pos_to_check.y + height;
			BWAPI::Position pos2 = utils::tile_to_pos(tmp);

			BWAPI::Position middle;
			middle.x = (pos1.x + pos2.x) / 2;
			middle.y = (pos1.y + pos2.y) / 2;

			double max_distance = 0;

			for (auto m : mineral_patches_)
			{
				double distance = m->position_get().getDistance(middle);
				if (distance > max_distance)
				{
					max_distance = distance;
				}
			}

			for (auto g : gas_)
			{
				double distance = g->position_get().getDistance(middle);
				if (distance > max_distance)
				{
					max_distance = distance;
				}
			}

			if (max_distance < best_max_distance)
			{
				if (utils::can_build_here(pos_to_check, BWAPI::UnitTypes::Protoss_Nexus))
				{
					best_max_distance = max_distance;
					res = pos_to_check;
				}
			}
		}
	}

	return res;
}

/**
	REGION
**/

Region::Region(BWAPI::Region data)
	: data_(data)
	, debug_color_(BWAPI::Colors::Blue)
	, weight_(0)
{

}

void Region::debug()
{
	BWAPI::Broodwar->drawBoxMap(data_->getBoundsLeft(), data_->getBoundsTop(), data_->getBoundsRight(), data_->getBoundsBottom(), debug_color_);
}

void Region::init()
{
	for (auto r : data_->getNeighbors())
	{
		Region* neighbor = GameInfo::instance_get()->map_get()->get_region(r->getID());
		if (neighbor)
		{
			neighbors_.insert(neighbor);
		}
		else
		{
			std::cerr << "Region error" << std::endl;
		}
	}
}
/**
	PATHFINDING
**/

void PathFinding::add_region_to_path(Region* r)
{
	path_.push(r);
	r->debug_color_set(BWAPI::Colors::Red);
}

/**
	MAP
**/

Map::Map()
{

}

void Map::init()
{
	BWAPI::Regionset regions = BWAPI::Broodwar->getAllRegions();
	for (auto r : regions)
	{
		Region* region = new Region(r);
		regions_[r->getID()] = region;
	}

	for (auto r : regions_)
	{
		r.second->init();
	}

}

void Map::clear()
{
	regions_.clear();
}

void Map::debug()
{
	for (auto r : regions_)
	{
		r.second->debug();
	}
}

Region* Map::get_region(const int id) const
{
	std::map<int, Region*>::const_iterator it;
	it = regions_.find(id);
	if (it == regions_.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

Region* Map::get_region(BWAPI::Position pos) const
{
	BWAPI::Region region = BWAPI::Broodwar->getRegionAt(pos);

	if (BWAPI::Broodwar->getLastError() == BWAPI::Errors::Invalid_Parameter)
	{
		return nullptr;
	}

	return get_region(region->getID());
}

PathFinding* Map::get_path(BWAPI::Position pos1, BWAPI::Position pos2) const
{
	return dijkstra(pos1, pos2, true);
}

PathFinding* Map::get_path_with_weight(BWAPI::Position pos1, BWAPI::Position pos2) const
{
	return dijkstra(pos1, pos2, false);
}

PathFinding* Map::dijkstra(BWAPI::Position pos1, BWAPI::Position pos2, const bool ignore_weight) const
{
	struct GraphNode
	{
		Region* region;
		GraphNode* best_prev_node;
		int score;
	};

	std::map<int, GraphNode*> visited_nodes;
	std::queue<GraphNode*> nodes_to_visit;

	Region* begin = get_region(pos1);
	Region* end = get_region(pos2);

	GraphNode* begin_node = new GraphNode();
	begin_node->region = begin;
	begin_node->score = 0;

	GraphNode* end_node = nullptr;

	nodes_to_visit.push(begin_node);

	std::set<Region*> end_neighbors;
	for (auto r : end->neighbors_get())
	{
		end_neighbors.insert(r);
	}

	while (nodes_to_visit.size() && end_neighbors.size())
	{
		GraphNode* current_node = nodes_to_visit.front();
		nodes_to_visit.pop();

		visited_nodes[current_node->region->data_get()->getID()] = current_node;
		end_neighbors.erase(current_node->region);

		for (auto r : current_node->region->neighbors_get())
		{
			if (!r->data_get()->isAccessible())
			{
				continue;
			}
			std::map<int, GraphNode*>::iterator it = visited_nodes.find(r->data_get()->getID());
			GraphNode* neighbor;

			if (it == visited_nodes.end())
			{
				GraphNode* tmp = new GraphNode();
				tmp->region = r;
				tmp->score = INT_MAX;
				neighbor = tmp;
				if (r != end)
				{
					nodes_to_visit.push(neighbor);
				}
				else
				{
					end_node = neighbor;
				}
			}
			else
			{
				neighbor = it->second;
			}

			int score = current_node->score + utils::fly_distance(current_node->region->data_get()->getCenter(), neighbor->region->data_get()->getCenter());
			if (!ignore_weight)
			{
				score += current_node->region->weight_get();
			}

			if (score < neighbor->score)
			{
				neighbor->score = score;
				neighbor->best_prev_node = current_node;
			}
		}
	}

	PathFinding* res = new PathFinding();
	if (end_node)
	{
		GraphNode* node = end_node;
		Region* prev = nullptr;
		do
		{
			res->add_region_to_path(node->region);
			node = node->best_prev_node;
			prev = node->region;			
		} 
		while (prev != begin);
	}

	for (auto r : visited_nodes)
	{
		delete r.second;
	}

	return res;
}


/**
	GAMEINFO
**/

GameInfo::GameInfo()
  : bank_(new Bank(256))
	, map_(new Map())
	, opponent_position_found_(false)
{
}

GameInfo::~GameInfo()
{
	for (auto l : mineral_lines_)
	{
		delete l;
	}
	delete bank_;
	delete map_;
}

void GameInfo::on_frame()
{
	bank_->on_frame();
}

void GameInfo::init()
{
	std::cout << "Info Init" << std::endl;

	bank_->init();
	map_->init();


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

	BWAPI::TilePosition::list positions = BWAPI::Broodwar->getStartLocations();
	self_position_ = BWAPI::Broodwar->self()->getStartLocation();

	for (auto p : positions)
	{
		if (p != self_position_)
		{
			spawn_positions_.insert(p);
		}
	}

	std::cout << "Info end Init" << std::endl;
}

void GameInfo::clear()
{
	bank_->clear();
	map_->clear();

	for (auto l : mineral_lines_)
	{
		delete l;
	}

	mineral_lines_.clear();
	spawn_positions_.clear();
	opponent_position_found_ = false;
	self_position_ = BWAPI::TilePositions::None;
	show_units_.clear();
	hide_units_.clear();
}

void GameInfo::debug()
{
	for (auto m : mineral_lines_)
	{
		BWAPI::Broodwar->drawCircleMap(m->center_get(), 20, BWAPI::Colors::Red);
	}

	for (auto p : positions_to_debug_)
	{
		BWAPI::Broodwar->drawCircleMap(utils::tile_to_pos(p.first), 20, p.second);
	}

	bank_->debug();
	map_->debug();
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

void GameInfo::on_unit_show(BWAPI::Unit u)
{
	if (hide_units_.find(u) != hide_units_.end())
	{
		hide_units_.erase(u);
	}
	show_units_.insert(u);
}

void GameInfo::on_unit_hide(BWAPI::Unit u)
{
	show_units_.erase(u);
	hide_units_.insert(u);
}

void GameInfo::on_unit_destroy(BWAPI::Unit u)
{
	show_units_.erase(u);
}

std::set<BWAPI::Unit> GameInfo::units_in_sight(UnitAgent* agent)
{
	std::set<BWAPI::Unit> res;
	for (auto u : show_units_)
	{
		if (u->getPosition().getDistance(agent->unit_get()->getPosition()) <= agent->unit_get()->getType().sightRange())
		{
			res.insert(u);
		}
	}
	return res;
}

std::set<BWAPI::Unit> GameInfo::units_in_sight(std::set<UnitAgent*> units)
{
	std::set<BWAPI::Unit> res;
	for (auto agent : units)
	{
		std::set<BWAPI::Unit> tmp = units_in_sight(agent);
		for (auto unit : tmp)
		{
			res.insert(unit);
		}
	}
	return res;
}

std::set<BWAPI::Unit> GameInfo::units_in_sight(std::set<ArmyAgent*> units)
{
	std::set<BWAPI::Unit> res;
	for (auto agent : units)
	{
		std::set<BWAPI::Unit> tmp = units_in_sight(agent);
		for (auto unit : tmp)
		{
			res.insert(unit);
		}
	}
	return res;
}

MineralLine* GameInfo::get_nearest_mineral_line(MineralLine* line, bool with_gas)
{
	MineralLine* res = nullptr;
	double best_dist = DBL_MAX;

	for (auto m : mineral_lines_)
	{
		double dist = m->center_get().getDistance(line->center_get());
		if (dist != 0 && m->base_get() == nullptr && m->gas_get().size() > 0)
		{
			if (dist < best_dist)
			{
				best_dist = dist;
				res = m;
			}
		}
	}
	return res;
}

MineralLine* GameInfo::get_nearest_mineral_line(std::set<MineralLine*> line, bool with_gas)
{
	MineralLine* res = nullptr;
	double best_dist = DBL_MAX;

	for (auto m : mineral_lines_)
	{
		double dist = 0;
		for (auto l : line)
		{
			dist += m->center_get().getDistance(l->center_get());
		}

		dist /= (double) line.size();

		if (dist != 0 && m->base_get() == nullptr && m->gas_get().size() > 0)
		{
			if (dist < best_dist)
			{
				best_dist = dist;
				res = m;
			}
		}
	}
	return res;
}
