#ifndef UTILS_HH_
# define UTILS_HH_

#include <BWAPI.h>

namespace utils
{
	const BWAPI::Unit closest_unit(const BWAPI::Unitset units, const BWAPI::Unit u);
	
}

#endif /// !UTILS_HH_