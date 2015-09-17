#ifndef ECO_AGENT_HH_
# define ECO_AGENT_HH_

# include "agent.hh"

class EcoAgent : virtual public Agent
{
public:

protected:
	virtual void protected_on_frame() override;
};

#endif