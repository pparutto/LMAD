#ifndef BUILDING_TECH_HH_
# define BUILDING_TECH_HH_

# include "tech.hh"

# include "research-tech.hh"
# include "unit-tech.hh"

# include <set>

class BuildingTech : public Tech
{
public:

private:
	std::set<UnitTech*>	productable_units_;
	std::set<ResearchTech*> researchable_techs_;
};

#endif