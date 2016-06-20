#include "building-agent.hh"

#include "requests/request.hh"

BuildingAgent::BuildingAgent(BWAPI::Unit u)
	: UnitAgent(u)
	, has_money_(false)
{

}

void BuildingAgent::protected_on_frame()
{

}

bool BuildingAgent::train_unit(BWAPI::UnitType u)
{
	if (is_training())
	{
		return false;
	}
	if (!has_money_)
	{
		has_money_ = GameInfo::instance_get()->bank_get()->request_resources(u.mineralPrice(), u.gasPrice());
	}
	if (has_money_)
	{
		unit_get()->train(u);
		if (is_training())
		{
			has_money_ = false;
			return true;
		}
	}

	return false;
}

bool BuildingAgent::research(BWAPI::UpgradeType t)
{
	if (is_researching())
	{
		return false;
	}
	if (!has_money_)
	{
		has_money_ = GameInfo::instance_get()->bank_get()->request_resources(t.mineralPrice(), t.gasPrice());
	}
	if (has_money_)
	{
		unit_get()->upgrade(t);
		if (is_researching())
		{
			has_money_ = false;
			return true;
		}
	}

	return false;
}

VISIT_DEFINITIONS(BuildingAgent);