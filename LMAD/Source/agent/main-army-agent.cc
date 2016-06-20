#include "main-army-agent.hh"

#include <BWAPI/Game.h>
#include <BWAPI/RegionSet.h>
#include <BWAPI/Region.h>

#include "../utils/game-info.hh"
#include "../utils/utils.hh"

#include <iostream>

MainArmyAgent::MainArmyAgent()
	: core_(nullptr)
	, has_dragoon_range_started_(false)
	, has_dragoon_range_finished_(false)
{

}

void MainArmyAgent::protected_init()
{
	GameInfo* game_info = GameInfo::instance_get();

	possible_spawns_ = game_info->spawn_positions_get();
}

void MainArmyAgent::protected_clear()
{

}

void MainArmyAgent::protected_on_frame()
{
	GameInfo* game_info = GameInfo::instance_get();

	if (!(game_info->opponent_position_found_get()))
	{
		for (auto g : gates_)
		{
			g->train_unit(BWAPI::UnitTypes::Protoss_Zealot);
		}
	}
	else if (core_)
	{
		if (!has_dragoon_range_started_)
		{
			if (core_->research(BWAPI::UpgradeTypes::Singularity_Charge))
			{
				has_dragoon_range_started_ = true;
			}
		}
		else
		{
			if (!core_->is_researching())
			{
				has_dragoon_range_finished_ = true;
			}
		}
		for (auto g : gates_)
		{
			g->train_unit(BWAPI::UnitTypes::Protoss_Dragoon);
		}
	}

	if (!(game_info->opponent_position_found_get()))
	{
		if (possible_spawns_.size() == 1)
		{
			game_info->opponent_position_set(*(possible_spawns_.begin()));
		}
		else
		{
			scout();
		}
	}
	else
	{
		if (!has_dragoon_range_finished_)
		{
			for (auto a : army_agents_)
			{
				if (a->has_finished_order_get())
				{
					a->first_pos_set((*(gates_.begin()))->unit_get()->getPosition());
					a->mode_set(ArmyAgent::DEFEND);
				}
			}
		}
		else
		{
			if (army_agents_.size() < 10)
			{
				for (auto a : army_agents_)
				{
					a->first_pos_set((*(gates_.begin()))->unit_get()->getPosition());
					a->mode_set(ArmyAgent::DEFEND);
				}
			}
			else
			{
				std::set<BWAPI::Unit> units = game_info->units_in_sight(army_agents_);
				std::set<BWAPI::Unit> targets_;

				for (auto a : army_agents_)
				{
					a->first_pos_set(utils::tile_to_pos(game_info->opponent_position_get()));
					a->target_set(nullptr);

					for (auto t : targets_)
					{
						if (a->can_see_unit(t))
						{
							a->target_set(t);
							break;
						}
					}

					if (a->target_get())
					{
						break;
					}

					for (auto u : units)
					{
						if (BWAPI::Broodwar->enemy() != u->getPlayer())
						{
							continue;
						}
						if (a->is_in_range(u))
						{
							a->target_set(u);
							targets_.insert(u);
							break;
						}
					}

					a->mode_set(ArmyAgent::ATTACK);
				}
			}
		}
	}

}

void MainArmyAgent::scout()
{
	std::set<BWAPI::TilePosition>::iterator it = possible_spawns_.begin();
	for (auto a : army_agents_)
	{
		if (a->mode_get() == ArmyAgent::SCOUT)
		{
			++it;
			if (it == possible_spawns_.end())
			{
				break;
			}
		}
	}

	if (it != possible_spawns_.end())
	{
		for (auto a : army_agents_)
		{
			if (a->mode_get() == ArmyAgent::NONE)
			{
				a->mode_set(ArmyAgent::SCOUT);
				a->first_pos_set(utils::tile_to_pos(*it));
			}
		}
	}
}

void MainArmyAgent::protected_on_unit_completed(ArmyAgent* a)
{
	add_sub_agent(a);
	army_agents_.insert(a);
}

void MainArmyAgent::protected_on_unit_completed(BuildingAgent* u)
{
	if (u->unit_get()->getType() == BWAPI::UnitTypes::Protoss_Gateway)
	{
		add_sub_agent(u);
		gates_.insert(u);
	}
	else if (u->unit_get()->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
	{
		core_ = u;
	}
}

void MainArmyAgent::protected_on_unit_destroyed(BuildingAgent* a)
{
	if (a->unit_get()->getType() == BWAPI::UnitTypes::Protoss_Gateway)
	{
		remove_sub_agent(a);
		gates_.erase(a);
	}
	else if (a->unit_get()->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
	{
		core_ = nullptr;
	}
}

void MainArmyAgent::protected_on_unit_show(BWAPI::Unit u)
{
	if (BWAPI::Broodwar->self() != u->getPlayer())
	{
		if (u->getType().isResourceDepot())
		{
			std::cout << "found hq at pos : " << u->getPosition() << std::endl;
			for (auto s : possible_spawns_)
			{
				if (u->getTilePosition() == s)
				{
					GameInfo::instance_get()->opponent_position_set(s);
					break;
				}
			}
		}
	}
}