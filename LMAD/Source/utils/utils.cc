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

	BWAPI::TilePosition find_valid_location_circle(const BWAPI::Position c, unsigned r, const BWAPI::UnitType building, WorkerAgent* w)
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
			BWAPI::Unit worker = nullptr;

			if (can_build_here(res, building, w, true))
				done = true;

			++i;
		}

		return res;
	}

	BWAPI::TilePosition find_valid_position_near_pylon(const BWAPI::UnitType building, std::set<BuildingAgent*> pylons, WorkerAgent* w)
	{
		for (auto p : pylons)
		{
			BWAPI::TilePosition pos = p->unit_get()->getTilePosition();
			for (int i = -6; i <= 6; ++i)
			{
				for (int j = -6; j <= 6; ++j)
				{
					BWAPI::TilePosition temp_pos = BWAPI::TilePosition(pos.x + i, pos.y + j);
					if (can_build_here(temp_pos, building, w, true))
					{
						return temp_pos;
					}
				}
			}
		}
		return BWAPI::TilePositions::Invalid;
	}

	BWAPI::TilePosition pos_to_tile(BWAPI::Position pos)
	{
		BWAPI::TilePosition res;
		res.x = pos.x / BWAPI::TILEPOSITION_SCALE;
		res.y = pos.y / BWAPI::TILEPOSITION_SCALE;
		return res;
	}

	BWAPI::Position tile_to_pos(BWAPI::TilePosition pos)
	{
		BWAPI::Position res;
		res.x = pos.x * BWAPI::TILEPOSITION_SCALE;
		res.y = pos.y * BWAPI::TILEPOSITION_SCALE;
		return res;
	}

	bool can_build_here(BWAPI::TilePosition pos, BWAPI::UnitType t, WorkerAgent* w, bool check_explored)
	{
		BWAPI::Unit worker = nullptr;
		if (w)
		{
			worker = w->unit_get();
		}
		return BWAPI::Broodwar->canBuildHere(pos, t, worker, check_explored);
	}

	int fly_distance(BWAPI::Position pos1, BWAPI::Position pos2)
	{
		int x = (pos1.x - pos2.x) * (pos1.x - pos2.x);
		int y = (pos1.y - pos2.y) * (pos1.y - pos2.y);

		return (int) sqrt(x + y);
	}

}