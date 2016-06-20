#ifndef BASE_AGENT_HH_
# define BASE_AGENT_HH_

# include "hq-agent.hh"
# include "worker-agent.hh"
# include "agent.hh"
# include "building-agent.hh"

# include "requests/requests-fw.hh"

# include <BWAPI.h>

# include "../utils/game-info.hh"


class BaseAgent : public Agent
{
public:

	BaseAgent(BuildingAgent* hq);
	~BaseAgent();

	void associate_worker(WorkerAgent* w);


	void set_max_workers(const unsigned mineral, const unsigned gas);
	void set_max_workers_mineral(const unsigned nb);
	void set_max_workers_mineral();
	void set_max_workers_gas(const unsigned nb);
	void set_max_workers_gas();


	const unsigned needs_workers() const;

	BWAPI::TilePosition nexus_position() const;

	const unsigned gates_number_get() const;
	const unsigned cores_number_get() const;

	void build_extra_workers_set(const bool b);

	/**
		REQUESTS BEGIN
	**/
public:
	virtual void accept(BuildingRequest* r) override;

	/**
		REQUESTS END
	**/

protected:

	virtual void protected_on_frame() override;
	virtual void protected_on_unit_destroyed(WorkerAgent* w) override;

private:
	void find_best_resource(WorkerAgent* worker);
	void reallocate_workers();

private:
	BuildingAgent* hq_;
	std::set<WorkerAgent*> workers_;

	std::set<BuildingAgent*> pylons_;

	unsigned max_mineral_;
	unsigned max_gas_;

	unsigned gates_number_;
	unsigned cores_number_;

	MineralLine* mineral_line_;
	bool build_extra_workers_;
};

# include "base-agent.hxx"

#endif /// !BASE_AGENT_HH_