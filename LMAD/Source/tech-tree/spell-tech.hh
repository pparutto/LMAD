#ifndef SPELL_TECH_HH_
# define SPELL_TECH_HH_

# include "tech.hh"
# include "research-tech.hh"

class UnitTech;

class SpellTech : public Tech
{
public:

private:

	UnitTech* caster_;
	ResearchTech* research_;

};

#endif