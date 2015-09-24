#ifndef WORKER_AGENT_HH_
# define WORKER_AGENT_HH_

# include "eco-agent.hh"
# include "unit-agent.hh"

# include <BWAPI.h>

class Resource;

class WorkerAgent : public EcoAgent, public UnitAgent
{
public:
	WorkerAgent(BWAPI::Unit u);
	virtual ~WorkerAgent();

	void has_orders_set(const bool order);
	const bool has_orders_get() const;

	void resource_set(Resource* resource);
	Resource* resource_get() const;

	VISIT_DECLARATIONS;

protected:

	virtual void protected_on_frame() override;
	virtual void protected_clear() override;

protected:
	bool has_orders_;
	unsigned mineral_;
	unsigned gas_;
	Resource* resource_;

	unsigned last_remaining_resources_;
	bool is_harvesting_;

};

# include "worker-agent.hxx"

#endif /// !WORKER_AGENT_HH_