#ifndef UNIT_AGENT_HH_
# define UNIT_AGENT_HH_

# include <BWAPI/unit.h>

class UnitAgent
{
public:
	UnitAgent(const BWAPI::Unit u);

	const BWAPI::Unit unit() const;

protected:
	const BWAPI::Unit unit_;
};

#endif /// !HQ_AGENT_HH_