#include "main-agent.hh"

void MainAgent::run()
{
	eco_agent_->run();
	army_agent_->run();
}