inline const int Bank::gas_get() const
{
	return gas_;
}

inline const int Bank::mineral_get() const
{
	return mineral_;
}

inline const unsigned Bank::gas_income_get() const
{
	return gas_income_;
}

inline const unsigned Bank::mineral_income_get() const
{
	return mineral_income_;
}

inline BWAPI::Unit Resource::unit_get() const
{
	return unit_;
}

inline BWAPI::Position Resource::position_get() const
{
	return position_;
}

inline void Resource::add_worker(WorkerAgent* worker)
{
	workers_.insert(worker);
}

inline void Resource::remove_worker(WorkerAgent* worker)
{
	std::set<WorkerAgent*>::iterator it = workers_.find(worker);
	if (it != workers_.end())
	{
		workers_.erase(it);
	}
}

inline const bool Resource::is_being_gathered_get() const
{
	return is_being_gathered_;
}

inline void Resource::is_being_gathered_set(const bool value)
{
	is_being_gathered_ = (value);
}

inline const std::set<WorkerAgent*> Resource::workers_get() const
{
	return workers_;
}

inline const unsigned Resource::worker_count() const
{
	return workers_.size();
}

inline const int& MineralLine::region_id_get() const
{
	return region_id_;
}

inline const std::set<Resource*> MineralLine::mineral_patches_get() const
{
	return mineral_patches_;
}

inline const std::set<Resource*> MineralLine::gas_get() const
{
	return gas_;
}

inline const BWAPI::Region Region::region_get() const
{
	return region_;
}

inline GameInfo* GameInfo::instance_get()
{
	if (!instance_)
	{
		instance_ = new GameInfo();
	}
	return instance_;
}

inline void GameInfo::instance_clean()
{
	delete instance_;
	instance_ = nullptr;
}

inline const std::set<MineralLine*>& GameInfo::mineral_lines_get() const
{
	return mineral_lines_;
}

inline Bank* GameInfo::bank_get() const
{
	return bank_;
}