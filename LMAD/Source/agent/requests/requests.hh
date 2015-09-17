#ifndef REQUESTS_HH_
# define REQUESTS_HH_

# include "request.hh"
# include "../base-agent.hh"

class PylonRequestData : public RequestData
{
public:

	PylonRequestData();

	void worker_set(WorkerAgent* worker);
	WorkerAgent* worker_get() const;

	BWAPI::TilePosition position_get() const;
	void position_set(const BWAPI::TilePosition position);

	const bool building_created_get() const;
	const bool building_completed_get() const;
	const bool is_dead_get() const;

	void building_created_set(const bool v);
	void building_completed_set(const bool v);
	void is_dead_set(const bool v);

private:

	WorkerAgent* worker_;
	BWAPI::TilePosition position_;
	bool building_created_;
	bool building_completed_;
	bool is_dead_;
};

class PylonRequest : public Request
{
public:

	PylonRequest();

	virtual void visit(Agent* agent) override;

	const bool is_created() const;
	const bool is_completed() const;
	const bool is_dead() const;

	virtual void on_unit_created(UnitAgent* agent) override;
	virtual void on_unit_completed(UnitAgent* agent) override;
	virtual void on_unit_destroyed(UnitAgent* agent) override;
};

# include "requests.hxx"

#endif