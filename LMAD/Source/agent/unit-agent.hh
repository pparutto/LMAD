#ifndef UNIT_AGENT_HH_
# define UNIT_AGENT_HH_

# include "agent.hh"

class UnitAgent : virtual public Agent
{
public:
	UnitAgent(BWAPI::Unit unit);
	virtual ~UnitAgent();

public:

	BWAPI::Unit unit_get() const;

protected:

	virtual void protected_clear() override;

private:

	BWAPI::Unit unit_;
};

# include "unit-agent.hxx"

#endif