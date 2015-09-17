#include "request.hh"
#include "../agent.hh"

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

void Request::on_unit_created(UnitAgent* u)
{

}

void Request::on_unit_completed(UnitAgent* u)
{

}

void Request::on_unit_destroyed(UnitAgent* u)
{

}
