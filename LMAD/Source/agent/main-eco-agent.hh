#ifndef MAIN_ECO_AGENT_
# define MAIN_ECO_AGENT_

# include <set>

# include "agent.hh"
# include "eco-agent.hh"

class MainEcoAgent : public Agent
{
public:

	virtual void run() override;

private:

	std::set<EcoAgent*> eco_agents_;
};

# include "main-eco-agent.hxx"

#endif