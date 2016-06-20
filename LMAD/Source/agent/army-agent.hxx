inline void ArmyAgent::mode_set(const unsigned mode)
{
	mode_ = mode;
	has_finished_order_ = false;
}

inline void ArmyAgent::first_pos_set(BWAPI::Position pos)
{
	first_pos_ = pos;
}

inline void ArmyAgent::second_pos_set(BWAPI::Position pos)
{
	second_pos_ = pos;
}

inline const unsigned ArmyAgent::mode_get() const
{
	return mode_;
}

inline const bool ArmyAgent::has_finished_order_get() const
{
	return has_finished_order_;
}

inline void ArmyAgent::target_set(BWAPI::Unit target)
{
	target_ = target;
}

inline BWAPI::Unit ArmyAgent::target_get() const
{
	return target_;
}
