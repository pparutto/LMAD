#ifndef UTILS_HH_
# define UTILS_HH_

#include <BWAPI.h>

namespace utils
{
	const BWAPI::Unit closest_unit(const BWAPI::Unitset units, const BWAPI::Unit u);
	BWAPI::TilePosition find_valid_location_circle(const BWAPI::Position c, unsigned r, const BWAPI::UnitType building);
}

#endif /// !UTILS_HH_