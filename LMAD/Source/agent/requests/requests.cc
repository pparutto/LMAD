#include "requests.hh"

BuildingRequestData::BuildingRequestData()
	: building_created_(false)
	, building_completed_(false)
	, is_dead_(false)
	, worker_timeout_(50)
	, move_timeout_(0)
{

}

void BuildingRequestData::check_worker_position()
{
	BWAPI::Position pos = worker_->unit_get()->getPosition();
	if (pos == last_worker_position_ && worker_timeout_)
	{
		--worker_timeout_;
	}
	else
	{
		worker_timeout_ = 10;
		last_worker_position_ = pos;
	}
}

BuildingRequest::BuildingRequest(BWAPI::UnitType building_type)
{
	BuildingRequestData* data = new BuildingRequestData();
	data->building_type_set(building_type);
	data_ = data;
}

void BuildingRequest::visit(Agent* agent)
{
	agent->accept(this);
}

void BuildingRequest::on_unit_created(BuildingAgent* agent)
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);

	std::cout << "building created at position : " << agent->unit_get()->getTilePosition() << std::endl;
	BWAPI::TilePosition pos1 = data->position_get();
	BWAPI::TilePosition pos2 = agent->unit_get()->getTilePosition();

	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->result_set(agent);
		data->building_created_set(true);
	}
}

void BuildingRequest::on_unit_completed(BuildingAgent* agent)
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->building_completed_set(true);
	}
}

void BuildingRequest::on_unit_destroyed(BuildingAgent* agent)
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	if (data->result_get() == agent)
	{
		data->is_dead_set(true);
	}
}

void BuildingRequest::on_unit_morphing(BuildingAgent* agent)
{
	BuildingRequestData* data = static_cast<BuildingRequestData*>(data_);
	BWAPI::TilePosition pos1 = data->position_get();
	BWAPI::TilePosition pos2 = agent->unit_get()->getTilePosition();
	std::cout << "unit morphed at position : " << agent->unit_get()->getTilePosition() << std::endl;
	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->building_created_set(true);
	}
}