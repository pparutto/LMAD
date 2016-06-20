#include "request.hh"
#include "../agent.hh"

#define CC_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, EVENT_TYPE) \
	void Request::on_unit_##EVENT_TYPE(UNIT_TYPE* u) \
	{\
		\
	}

#define CC_REQUEST_UNIT_EVENT(UNIT_TYPE) \
	CC_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, created) \
	CC_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, completed) \
	CC_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, destroyed) \
	CC_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, morphing)

#ifdef _DEBUG
Request::Request()
	: data_(nullptr)
{

}
#endif

void Request::on_frame()
{
#ifdef _DEBUG
	if (!data_)
	{
		throw("The request didnt set its data");
	}
	else
#endif
	data_->on_frame();
}


void Request::clear()
{
	delete data_;
}

void Request::protected_clear()
{

}

void Request::on_unit_show(BWAPI::Unit u)
{
}

void Request::on_unit_hide(BWAPI::Unit u)
{
}

void Request::on_enemy_destroy(BWAPI::Unit u)
{
}

CC_REQUEST_UNIT_EVENT(UnitAgent);
CC_REQUEST_UNIT_EVENT(BuildingAgent);
CC_REQUEST_UNIT_EVENT(WorkerAgent);
CC_REQUEST_UNIT_EVENT(ArmyAgent);
