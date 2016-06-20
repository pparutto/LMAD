#ifndef REQUESTS_HH_
# define REQUESTS_HH_

# include "request.hh"
# include "../base-agent.hh"

/****************************************************************************
************************ PYLON REQUEST **************************************
*****************************************************************************/

class BuildingRequestData : public RequestData
{
public:

	BuildingRequestData();

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

	const BWAPI::UnitType building_type_get() const;
	void building_type_set(BWAPI::UnitType building_type);

	BuildingAgent* result_get() const;
	void result_set(BuildingAgent* agent);

	bool is_worker_stuck() const;
	void check_worker_position();
	void worker_timeout_set(const unsigned value);

	void move_timeout_increment();
	const unsigned move_timeout_get() const;

private:

	WorkerAgent* worker_;
	BWAPI::TilePosition position_;
	BWAPI::UnitType building_type_;
	bool building_created_;
	bool building_completed_;
	bool is_dead_;
	BuildingAgent* result_;
	unsigned move_timeout_;

	BWAPI::Position last_worker_position_;
	unsigned int worker_timeout_;
};

class BuildingRequest : public Request
{
public:

	BuildingRequest(BWAPI::UnitType building_type);

	virtual void visit(Agent* agent) override;

	const bool is_created() const;
	const bool is_completed() const;
	const bool is_dead() const;

	virtual void on_unit_created(BuildingAgent* agent) override;
	virtual void on_unit_completed(BuildingAgent* agent) override;
	virtual void on_unit_destroyed(BuildingAgent* agent) override;
	virtual void on_unit_morphing(BuildingAgent* agent) override;


	enum Phase
	{
		INIT = 0,
		CHECKMONEY,
		FINDWORKER,
		MOVE_AND_BUILD,
		RELEASE_WORKER,
		CHECK_CREATION,
		CHECK_COMPLETION,
		END
	};
};


# include "requests.hxx"

#endif