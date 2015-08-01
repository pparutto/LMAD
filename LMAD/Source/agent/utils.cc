#include "utils.hh"

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
}