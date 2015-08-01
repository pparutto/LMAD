#ifndef UNIT_TECH_HH_
# define UNIT_TECH_HH_

# include "tech.hh"
# include "building-tech.hh"
# include "spell-tech.hh"

# include <set>

class UnitTech : public Tech
{
public:

private:

	BuildingTech* producer_;
	BuildingTech* locker_;
	std::set<SpellTech*> spells_;
};

#endif