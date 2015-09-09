#ifndef MAIN_AGENT_HH_
# define MAIN_AGENT_HH_

# include "agent.hh"

# include "main-eco-agent.hh"
# include "main-army-agent.hh"

class MainAgent : public Agent
{
public:

	MainAgent();
	~MainAgent();

	void init();

protected:

	virtual void protected_run() override;

private:
	void handle_events();

private:

	MainEcoAgent* eco_agent_;
	MainArmyAgent* army_agent_;

};

# include "main-agent.hxx"

#endif