#include <iostream>
#include "main-agent.hh"

#include <set>

#include "../utils/game-info.hh"

#include "building-agent.hh"


GameInfo* GameInfo::instance_ = 0;

MainAgent::MainAgent()
	: eco_agent_(nullptr)
	, army_agent_(nullptr)
{
	can_suicid_set(false);
}

MainAgent::~MainAgent()
{
	delete eco_agent_;
	delete army_agent_;
	GameInfo::instance_clean();
}

void MainAgent::protected_init()
{
	GameInfo::instance_get()->init();

	eco_agent_ = new MainEcoAgent();
	eco_agent_->init();
	add_sub_agent(eco_agent_);

	army_agent_ = new MainArmyAgent();
	army_agent_->init();
	add_sub_agent(army_agent_);

	game_started_ = true;
}

void MainAgent::protected_clear()
{
	game_started_ = false;

	unit_agents_by_id_.clear();

	if (eco_agent_)
	{
		remove_sub_agent(eco_agent_);
		eco_agent_ = nullptr;
	}

	if (army_agent_)
	{
		remove_sub_agent(army_agent_);
		army_agent_ = nullptr;
	}

	GameInfo::instance_get()->clear();
}

UnitAgent* MainAgent::get_agent_from_bwunit(BWAPI::Unit u) const
{
	if (u->getPlayer()->getID() == BWAPI::Broodwar->self()->getID())
	{
		if (u->getType().isWorker())
		{
			return new WorkerAgent(u);
		}
		else if (!u->getType().isBuilding())
		{
			return new ArmyAgent(u);
		}
		else if (u->getType().isBuilding())
		{
			return new BuildingAgent(u);
		}
	}

#ifdef _DEBUG
	//throw("No agent found for this BW unit");
	//std::cerr << "No agent found for this BW unit : Player Id : " << BWAPI::Broodwar->self()->getID()
	//	<< " Owner Id : " << u->getPlayer()->getID() << " Unit name : " << u->getType().getName() << std::endl;
#endif

	return nullptr;
}

void MainAgent::handle_events()
{
	for (auto &e : BWAPI::Broodwar->getEvents())
	{
		switch (e.getType())
		{
		case BWAPI::EventType::MatchStart:
		{
			init();
			break;
		}

		case BWAPI::EventType::MatchEnd:
		{
			clear();
			break;
		}

		case BWAPI::EventType::MatchFrame:
		{
			if (game_started_)
			{
				on_frame();
			}
			break;
		}

		case BWAPI::EventType::SendText:
		{
			break;
		}

		case BWAPI::EventType::ReceiveText:
		{
			break;
		}

		case BWAPI::EventType::PlayerLeft:
		{
			break;
		}

		case BWAPI::EventType::NukeDetect:
		{
			break;
		}

		case BWAPI::EventType::UnitDiscover:
		{
			break;
		}

		case BWAPI::EventType::UnitEvade:
		{
			break;
		}

		case BWAPI::EventType::UnitShow:
		{
			BWAPI::Unit u = e.getUnit();
			on_unit_show(u);
			break;
		}

		case BWAPI::EventType::UnitHide:
		{
			BWAPI::Unit u = e.getUnit();
			on_unit_hide(u);
			break;
		}

		case BWAPI::EventType::UnitCreate:
		{
			BWAPI::Unit u = e.getUnit();
			if (u->getPlayer()->getID() == BWAPI::Broodwar->self()->getID())
			{
				std::cout << "create : " << u->getID() << " : " << u->getType().getName() << std::endl;
			}
			UnitAgent* agent = get_agent_from_bwunit(u);
			unit_agents_by_id_[u->getID()] = agent;

			if (agent)
			{
				agent->visit_agent_on_unit_created(this);
			}
			break;
		}

		case BWAPI::EventType::UnitDestroy:
		{
			BWAPI::Unit u = e.getUnit();
			std::cout << "destroy : " << u->getID() << " : " << u->getType().getName() << std::endl;

			UnitAgent* agent = unit_agents_by_id_[u->getID()];
			if (unit_agents_by_id_.find(u->getID()) == unit_agents_by_id_.end())
			{
				std::cerr << "Detroy error" << std::endl;
			}
			else if (agent)
			{
				agent->visit_agent_on_unit_destroyed(this);
			}

			break;
		}

		case BWAPI::EventType::UnitMorph:
		{
			BWAPI::Unit u = e.getUnit();

			UnitAgent* agent = unit_agents_by_id_[u->getID()];
			if (!agent)
			{
				agent = get_agent_from_bwunit(u);
				unit_agents_by_id_[u->getID()] = agent;
			}

			if (agent)
			{
				agent->visit_agent_on_unit_morphing(this);
			}

			std::cout << "Unit Morph" << std::endl;
			break;
		}

		case BWAPI::EventType::UnitRenegade:
		{
			break;
		}

		case BWAPI::EventType::SaveGame:
		{
			break;
		}

		case BWAPI::EventType::MenuFrame:
		{
			break;
		}

		case BWAPI::EventType::UnitComplete:
		{
			BWAPI::Unit u = e.getUnit();

			UnitAgent* agent = unit_agents_by_id_[u->getID()];
			if (unit_agents_by_id_.find(u->getID()) == unit_agents_by_id_.end())
			{
				std::cerr << "Completed error" << std::endl;
			}
			else
			{
				if (agent)
				{
					agent->visit_agent_on_unit_completed(this);
				}
				else
				{
					std::cerr << "Crash vs terran ? " << u->getType().getName() << std::endl;
				}
			}

			break;
		}


		}
	}

}

void MainAgent::run()
{
	while (BWAPI::Broodwar->isInGame())
	{
		handle_events();

		BWAPI::BWAPIClient.update();
	}
}

void MainAgent::protected_on_frame()
{
	GameInfo::instance_get()->on_frame();
	GameInfo::instance_get()->debug();
}

void MainAgent::protected_on_unit_show(BWAPI::Unit u)
{
	GameInfo::instance_get()->on_unit_show(u);
}

void MainAgent::protected_on_unit_hide(BWAPI::Unit u)
{
	GameInfo::instance_get()->on_unit_hide(u);
}
