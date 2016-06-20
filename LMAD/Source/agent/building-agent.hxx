inline const bool BuildingAgent::is_training() const
{
	int queue_size = unit_get()->getTrainingQueue().size();
	int time = unit_get()->getRemainingTrainTime();

	if (time == 0)
	{
		return queue_size > 0;
	}

	if (queue_size > 1 || (queue_size == 1 && time > 10))
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline const bool BuildingAgent::is_researching() const
{
	return unit_get()->isUpgrading();
}