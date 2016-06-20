inline void BaseAgent::set_max_workers(unsigned max_mineral, unsigned max_gas)
{
	set_max_workers_mineral(max_mineral);
	set_max_workers_gas(max_gas);
}

inline void BaseAgent::set_max_workers_mineral(const unsigned nb)
{
	max_mineral_ = nb;
}

inline void BaseAgent::set_max_workers_mineral()
{
	set_max_workers_mineral(mineral_line_->mineral_patches_get().size() * 2);
}

inline void BaseAgent::set_max_workers_gas()
{
	set_max_workers_gas(mineral_line_->gas_get().size() * 3);
}

inline const unsigned BaseAgent::needs_workers() const
{
	return max_gas_ + max_mineral_ - workers_.size();
}

inline BWAPI::TilePosition BaseAgent::nexus_position() const
{
	if (hq_)
	{
		return hq_->unit_get()->getTilePosition();
	}
	else if (mineral_line_)
	{
		return mineral_line_->get_nexus_position();
	}
	return BWAPI::TilePositions::Invalid;
}

inline const unsigned BaseAgent::gates_number_get() const
{
	return gates_number_;
}

inline const unsigned BaseAgent::cores_number_get() const
{
	return cores_number_;
}

inline void BaseAgent::build_extra_workers_set(const bool b)
{
	build_extra_workers_ = b;
}