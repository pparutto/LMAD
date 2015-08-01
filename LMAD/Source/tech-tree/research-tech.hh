#ifndef RESEARCH_TECH_
# define RESEARCH_TECH_

# include "tech.hh"
# include "spell-tech.hh"

class ResearchTech : public Tech
{
public:

private:
	SpellTech* unlocked_spell_;
};

#endif