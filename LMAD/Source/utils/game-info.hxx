inline const int Bank::gas_get() const
{
	return gas_;
}

inline const int Bank::mineral_get() const
{
	return mineral_;
}

inline const float Bank::gas_income_get() const
{
	return gas_income_;
}

inline const float Bank::mineral_income_get() const
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

inline BWAPI::TilePosition Resource::tile_position_get() const
{
	return tile_position_;
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

inline const BuildingAgent* Resource::assimilator_get() const
{
	return assimilator_;
}

inline void Resource::assimilator_set(BuildingAgent* assimilator)
{
	assimilator_ = assimilator;
}

inline const bool Resource::has_assimilator_request_get() const
{
	return has_assimilator_request_;
}

inline void Resource::has_assimilator_request_set(const bool b)
{
	has_assimilator_request_ = b;
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

inline BaseAgent* MineralLine::base_get() const
{
	return base_;
}

inline void MineralLine::base_set(BaseAgent* base)
{
	base_ = base;
}

inline const BWAPI::Region Region::data_get() const
{
	return data_;
}

inline const int Region::weight_get() const
{
	return weight_;
}

inline const std::set<Region*> Region::neighbors_get() const
{
	return neighbors_;
}

inline void Region::debug_color_set(BWAPI::Color color)
{
	debug_color_ = color;
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

inline Map* GameInfo::map_get() const
{
	return map_;
}

inline const bool GameInfo::opponent_position_found_get() const
{
	return opponent_position_found_;
}
inline BWAPI::TilePosition GameInfo::opponent_position_get() const
{
	return opponent_position_;
}

inline void GameInfo::opponent_position_set(BWAPI::TilePosition pos)
{
	opponent_position_ = pos;
	opponent_position_found_ = true;
}

inline std::set<BWAPI::TilePosition> GameInfo::spawn_positions_get() const
{
	return spawn_positions_;
}

const inline std::set<BWAPI::Unit> GameInfo::show_units_get() const
{
	return show_units_;
}

const inline std::set<BWAPI::Unit> GameInfo::hide_units_get() const
{
	return hide_units_;
}

inline void GameInfo::add_position_to_debug(BWAPI::TilePosition pos, BWAPI::Color color)
{
	positions_to_debug_[pos] = color;
}

inline void GameInfo::remove_position_to_debug(BWAPI::TilePosition pos)
{
	positions_to_debug_.erase(pos);
}

inline void GameInfo::add_building_request_position(BWAPI::TilePosition pos, BWAPI::UnitType type)
{
	building_request_positions_[pos] = type;
}

inline void GameInfo::remove_building_request_position(BWAPI::TilePosition pos)
{
	building_request_positions_.erase(pos);
}