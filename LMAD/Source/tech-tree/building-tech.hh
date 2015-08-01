#ifndef BUILDING_TECH_HH_
# define BUILDING_TECH_HH_

# include "tech.hh"

# include "research-tech.hh"

# include <set>

class UnitTech;

class BuildingTech : public Tech
{
public:

private:
	std::set<UnitTech*>	productable_units_;
	std::set<ResearchTech*> researchable_techs_;
	std::set<UnitTech*> unlocked_units_;
};

#endif