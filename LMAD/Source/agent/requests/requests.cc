#include "requests.hh"

void PylonRequest::visit(Agent* agent, unsigned priority)
{
	agent->accept(this, priority);
}