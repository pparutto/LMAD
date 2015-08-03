#include "utils.hh"

#define _USE_MATH_DEFINES
#include <math.h>

#include <random>


namespace utils
{
	const BWAPI::Unit
		closest_unit(const BWAPI::Unitset units, const BWAPI::Unit u)
	{
		BWAPI::Unit res = nullptr;
		int res_dist = -1;
		int cur_dist = -1;

		for (auto &uu : units)
		{
			cur_dist = u->getDistance(uu);
			if (!res || cur_dist < res_dist)
			{
				res = uu;
				res_dist = cur_dist;
			}
		}

		return res;
	}

	BWAPI::TilePosition find_valid_location_circle(const BWAPI::Position c, unsigned r, const BWAPI::UnitType building)
	{
		unsigned max_iter = 50;
		bool done = false;
		
		std::default_random_engine generator;
		std::uniform_real_distribution<double> dr(1, r);
		std::uniform_real_distribution<double> dtheta(0, 2 * M_PI);

		BWAPI::TilePosition res;
		unsigned i = 0;
		while (!done && i < max_iter)
		{
			double cur_r = dr(generator);
			double cur_theta = dtheta(generator);

			res = static_cast<BWAPI::TilePosition>(BWAPI::Position(static_cast<int>(round(c.x + cur_r * cos(cur_theta))),
																														 static_cast<int>(round(c.y + cur_r * sin(cur_theta)))));

			if (BWAPI::Broodwar->canBuildHere(res, building, nullptr, true))
				done = true;

			++i;
		}

		return res;
	}
}