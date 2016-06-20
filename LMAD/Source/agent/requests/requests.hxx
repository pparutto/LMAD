inline void BuildingRequestData::worker_set(WorkerAgent* worker)
{
	worker_ = worker;
	last_worker_position_ = worker_->unit_get()->getPosition();
	worker_timeout_ = 50;
}

inline WorkerAgent* BuildingRequestData::worker_get() const
{
	return worker_;
}

inline BWAPI::TilePosition BuildingRequestData::position_get() const
{
	return position_;
}

inline void BuildingRequestData::position_set(const BWAPI::TilePosition position)
{
	position_ = position;
}

inline void BuildingRequestData::building_created_set(const bool b)
{
	building_created_ = b;
}

inline void BuildingRequestData::building_completed_set(const bool b)
{
	building_completed_ = b;
}

inline void BuildingRequestData::is_dead_set(const bool b)
{
	is_dead_ = b;
}

inline const bool BuildingRequestData::building_created_get() const
{
	return building_created_;
}

inline const bool BuildingRequestData::building_completed_get() const
{
	return building_completed_;
}

inline const bool BuildingRequestData::is_dead_get() const
{
	return is_dead_;
}

inline const BWAPI::UnitType BuildingRequestData::building_type_get() const
{
	return building_type_;
}

inline void BuildingRequestData::building_type_set(BWAPI::UnitType building_type)
{
	building_type_ = building_type;
}

inline BuildingAgent* BuildingRequestData::result_get() const
{
	return result_;
}

inline void BuildingRequestData::result_set(BuildingAgent* agent)
{
	result_ = agent;
}

inline bool BuildingRequestData::is_worker_stuck() const
{
	return worker_timeout_ == 0;
}

inline void BuildingRequestData::worker_timeout_set(const unsigned value)
{
	worker_timeout_ = value;
}

inline void BuildingRequestData::move_timeout_increment()
{
	++move_timeout_;
}

inline const unsigned BuildingRequestData::move_timeout_get() const
{
	return move_timeout_;
}

inline const bool BuildingRequest::is_created() const
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	return data->building_created_get();
}

inline const bool BuildingRequest::is_completed() const
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	return data->building_completed_get();
}

inline const bool BuildingRequest::is_dead() const
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	return data->is_dead_get();
}

