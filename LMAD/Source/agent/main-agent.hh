#ifndef MAIN_AGENT_HH_
# define MAIN_AGENT_HH_

# include "agent.hh"

# include "main-eco-agent.hh"

class MainAgent : public Agent
{
public:

	virtual void run() override;

private:

	MainEcoAgent* eco_agent_;
};

# include "main-agent.hxx"

#endif