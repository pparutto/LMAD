inline void WorkerAgent::has_orders_set(const bool orders)
{
	has_orders_ = orders;
	if (orders)
	{
		is_harvesting_ = false;
	}
	else
	{
		if (unit_get()->isCarryingGas() || unit_get()->isCarryingMinerals())
		{
			unit_get()->returnCargo();
		}
	}
}

inline const bool WorkerAgent::has_orders_get() const
{
	return has_orders_;
}
