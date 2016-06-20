#ifndef UTILS_HH_
# define UTILS_HH_

# include <BWAPI.h>
# include <BWAPI/Position.h>
# include "../agent/building-agent.hh"
# include "../agent/worker-agent.hh"

namespace utils
{
	const BWAPI::Unit closest_unit(const BWAPI::Unitset units, const BWAPI::Unit u);
	BWAPI::TilePosition find_valid_location_circle(const BWAPI::Position c, unsigned r, const BWAPI::UnitType building, WorkerAgent* w = nullptr);

	BWAPI::TilePosition find_valid_position_near_pylon(const BWAPI::UnitType building, std::set<BuildingAgent*> pylons, WorkerAgent* w = nullptr);

	BWAPI::TilePosition pos_to_tile(BWAPI::Position pos);
	BWAPI::Position tile_to_pos(BWAPI::TilePosition pos);

	bool can_build_here(BWAPI::TilePosition pos, BWAPI::UnitType building, WorkerAgent* worker = nullptr, bool check_explored = false);

	int fly_distance(BWAPI::Position pos1, BWAPI::Position pos2);
}

#endif /// !UTILS_HH_