inline void PylonRequestData::worker_set(WorkerAgent* worker)
{
	worker_ = worker;
}

inline WorkerAgent* PylonRequestData::worker_get() const
{
	return worker_;
}

inline BWAPI::TilePosition PylonRequestData::position_get() const
{
	return position_;
}

inline void PylonRequestData::position_set(const BWAPI::TilePosition position)
{
	position_ = position;
}

inline void PylonRequestData::building_created_set(const bool b)
{
	building_created_ = b;
}

inline void PylonRequestData::building_completed_set(const bool b)
{
	building_completed_ = b;
}

inline void PylonRequestData::is_dead_set(const bool b)
{
	is_dead_ = b;
}

inline const bool PylonRequestData::building_created_get() const
{
	return building_created_;
}

inline const bool PylonRequestData::building_completed_get() const
{
	return building_completed_;
}

inline const bool PylonRequestData::is_dead_get() const
{
	return is_dead_;
}

inline const bool PylonRequest::is_created() const
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	return data->building_created_get();
}

inline const bool PylonRequest::is_completed() const
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	return data->building_completed_get();
}

inline const bool PylonRequest::is_dead() const
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	return data->is_dead_get();
}
