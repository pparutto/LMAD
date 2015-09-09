#ifndef UNIT_AGENT_HH_
# define UNIT_AGENT_HH_

# include "agent.hh"

class UnitAgent : virtual public Agent
{
public:
	UnitAgent(const BWAPI::Unit unit);

public:

	const BWAPI::Unit unit_get() const;

private:

	const BWAPI::Unit unit_;
};

# include "unit-agent.hxx"

#endif