#ifndef WORKER_AGENT_HH_
# define WORKER_AGENT_HH_

# include "eco-agent.hh"
# include "unit-agent.hh"

# include <BWAPI.h>

class WorkerAgent : public EcoAgent, public UnitAgent
{
public:
	WorkerAgent(const BWAPI::Unit& u);

	void has_orders_set(const bool order);
	const bool has_orders_get() const;

protected:

	virtual void protected_on_frame() override;

protected:
	bool is_collecting_;
	bool has_orders_;

};

# include "worker-agent.hxx"

#endif /// !WORKER_AGENT_HH_