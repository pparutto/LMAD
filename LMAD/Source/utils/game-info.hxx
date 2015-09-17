inline const int& MineralLine::region_id_get() const
{
	return region_id_;
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