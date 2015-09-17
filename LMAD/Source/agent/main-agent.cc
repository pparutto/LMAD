#include <iostream>
#include "main-agent.hh"

#include <set>

#include "../utils/game-info.hh"

#include "building-agent.hh"


GameInfo* GameInfo::instance_ = 0;

MainAgent::MainAgent()
	: game_started_(false)
	, eco_agent_(new MainEcoAgent())
	, army_agent_(new MainArmyAgent())
{
}

MainAgent::~MainAgent()
{
	delete eco_agent_;
	delete army_agent_;
	GameInfo::instance_clean();
}

void MainAgent::init()
{
	GameInfo::instance_get()->init();
	for (auto a : unit_agents_by_id_)
	{
		delete a.second;
	}

	unit_agents_by_id_.clear();

	game_started_ = true;
	eco_agent_->init();
	army_agent_->init();
	add_sub_agent(eco_agent_);
	add_sub_agent(army_agent_);
}

UnitAgent* MainAgent::get_agent_from_bwunit(const BWAPI::Unit& u) const
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
		else if (u->getType().isResourceDepot())
		{
			return new HQAgent(u);
		}
		else if (u->getType().isBuilding())
		{
			return new BuildingAgent(u);
		}
	}

#ifdef _DEBUG
	//throw("No agent found for this BW unit");
	std::cerr << "No agent found for this BW unit : Player Id : " << BWAPI::Broodwar->self()->getID()
		<< " Owner Id : " << u->getPlayer()->getID() << " Unit name : " << u->getType().getName() << std::endl;
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
			game_started_ = false;
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
			break;
		}

		case BWAPI::EventType::UnitHide:
		{
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

			on_unit_created(agent);
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
			else
			{
				on_unit_destroyed(agent);
			}

			break;
		}

		case BWAPI::EventType::UnitMorph:
		{
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
			if (u->getPlayer()->getID() == BWAPI::Broodwar->self()->getID())
			{
				if (u->getType().isWorker())
				{
					eco_agent_->add_worker(u);
					std::cout << "complete : " << u->getID() << " : " << u->getType().getName() << std::endl;
				}
				else if (!u->getType().isBuilding())
				{
					army_agent_->add_unit(u);
					std::cout << "complete : " << u->getID() << " : " << u->getType().getName() << std::endl;
				}
				else if (u->getType().isResourceDepot())
				{
					eco_agent_->add_HQ(u);
					std::cout << "complete : " << u->getID() << " : " << u->getType().getName() << std::endl;
				}
			}

			UnitAgent* agent = unit_agents_by_id_[u->getID()];
			if (unit_agents_by_id_.find(u->getID()) == unit_agents_by_id_.end())
			{
				std::cerr << "Completed error" << std::endl;
			}
			else
			{
				on_unit_completed(agent);
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
	GameInfo::instance_get()->debug();
}
