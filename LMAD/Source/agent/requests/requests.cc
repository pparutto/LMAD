#include "requests.hh"

PylonRequestData::PylonRequestData()
	: building_created_(false)
	, building_completed_(false)
	, is_dead_(false)
{

}

PylonRequest::PylonRequest()
{
	data_ = new PylonRequestData();
}

void PylonRequest::visit(Agent* agent)
{
	agent->accept(this);
}

void PylonRequest::on_unit_created(UnitAgent* agent)
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->building_created_set(true);
	}
}

void PylonRequest::on_unit_completed(UnitAgent* agent)
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->building_completed_set(true);
	}
}

void PylonRequest::on_unit_destroyed(UnitAgent* agent)
{
	PylonRequestData* data = static_cast<PylonRequestData*>(data_);
	if (agent->unit_get()->getTilePosition() == data->position_get())
	{
		data->is_dead_set(true);
	}
}