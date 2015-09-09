#include <iostream>
#include "main-agent.hh"

#include <BWAPI.h>
#include <BWAPI/Client.h>
#include <set>

#include "../utils/game-info.hh"

GameInfo* GameInfo::instance_ = 0;

MainAgent::MainAgent()
	: eco_agent_(new MainEcoAgent())
	, army_agent_(new MainArmyAgent())
{
	GameInfo::instance_get()->init();
}

MainAgent::~MainAgent()
{
	delete eco_agent_;
	delete army_agent_;
}

void MainAgent::init()
{
	eco_agent_->init();
	army_agent_->init();
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
			break;
		}

		case BWAPI::EventType::MatchFrame:
		{
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
			break;
		}

		case BWAPI::EventType::UnitDestroy:
		{
			BWAPI::Unit u = e.getUnit();
			std::cout << "destroy : " << u->getID() << " : " << u->getType().getName() << std::endl;
			break;
		}

		case BWAPI::EventType::UnitMorph:
		{
			std::cout << "pouet" << std::endl;
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
			break;
		}


		}
	}

}

void MainAgent::protected_run()
{
	while (BWAPI::Broodwar->isInGame())
	{
		GameInfo::instance_get()->debug();
		eco_agent_->run();
		army_agent_->run();

		handle_events();

		BWAPI::BWAPIClient.update();
	}
	GameInfo::instance_clean();
}