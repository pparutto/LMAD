#ifndef TECH_TREE_HH_
# define TECH_TREE_HH_

# include "tech.hh"

# include <set>

class BuildingTech;
class UnitTech;
class ResearchTech;
class SpellTech;

class TechTree
{
public:

private:

	std::set<UnitTech*> units_;
	std::set<BuildingTech*> buildings_;
	std::set<ResearchTech*> researchs_;
	std::set<SpellTech*> spells_;

};

#endif
