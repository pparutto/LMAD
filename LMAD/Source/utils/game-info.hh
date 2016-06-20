#ifndef GAME_INFO_HH_
# define GAME_INFO_HH_

# include <BWAPI/Position.h>
# include <BWAPI/Region.h>
# include <BWAPI/Game.h>
# include <BWAPI/Color.h>

# include <set>
# include <stack>
# include <map>
# include <utility>

# include "../agent/worker-agent.hh"

# define SUPPLY_COST (100.f / 8.f)

class BaseAgent;
class ArmyAgent;

class Bank
{
public:

	Bank(unsigned income_precision);
	~Bank();

	void on_frame();

	void init();
	void clear();
	void debug() const;

	void add_gas(const int value);
	void add_mineral(const int value);

	const int gas_get() const;
	const int mineral_get() const;

	const bool request_resources(const int mineral, const int gas);

	const float gas_income_get() const;
	const float mineral_income_get() const;

private:

	int mineral_;
	int gas_;

	unsigned* mineral_incomes_;
	unsigned total_mineral_;
	float mineral_income_;

	unsigned* gas_incomes_;
	unsigned total_gas_;
	float gas_income_;

	unsigned indice_;

	const unsigned income_precision_;
};

class Resource
{
public:
	Resource(BWAPI::Unit unit, BWAPI::Position position, BWAPI::TilePosition tile_position);

	BWAPI::Unit unit_get() const;
	BWAPI::Position position_get() const;
	BWAPI::TilePosition tile_position_get() const;

	void add_worker(WorkerAgent* worker);
	void remove_worker(WorkerAgent* worker);

	const unsigned worker_count() const;
	const std::set<WorkerAgent*> workers_get() const;

	const bool is_being_gathered_get() const;
	void is_being_gathered_set(const bool value);

	const BuildingAgent* assimilator_get() const;
	void assimilator_set(BuildingAgent* assimilator);

	const bool has_assimilator_request_get() const;
	void has_assimilator_request_set(const bool b);

private:

	BWAPI::Unit unit_;
	BWAPI::Position position_;
	BWAPI::TilePosition tile_position_;

	bool is_being_gathered_;
	std::set<WorkerAgent*> workers_;
	BuildingAgent* assimilator_;
	bool has_assimilator_request_;
};

class MineralLine
{
public:

	MineralLine(const int& region_id);
	~MineralLine();
	const int& region_id_get() const;

	void init_gas(const BWAPI::Unit resource);
	void init_mineral(const BWAPI::Unit resource);

	bool add_if_near_gas(const BWAPI::Unit resource);
	bool add_if_near_mineral(const BWAPI::Unit resource);

	BWAPI::Position center_get() const;

	const std::set<Resource*> mineral_patches_get() const;
	const std::set<Resource*> gas_get() const;

	BaseAgent* base_get() const;
	void base_set(BaseAgent* base);

	BWAPI::TilePosition get_nexus_position();

private:
	const bool is_near(const BWAPI::Unit resource) const;

private:

	std::set<Resource*> mineral_patches_;
	std::set<Resource*> gas_;

	BaseAgent* base_;

	int region_id_;
};

class Region
{
public:

	Region(BWAPI::Region data);

	const BWAPI::Region data_get() const;
	const int weight_get() const;

	const std::set<Region*> neighbors_get() const;

	void init();
	void debug();

	void debug_color_set(BWAPI::Color color);

private:

	BWAPI::Region data_;
	std::set<Region*> neighbors_;
	int weight_;

	BWAPI::Color debug_color_;
};

class PathFinding
{
public:

	void add_region_to_path(Region* region);

private:

	std::stack<Region*> path_;
	BWAPI::Position current_position_;
	BWAPI::Position position_to_reach_;
};

class Map
{
public:

	Map();

	void init();
	void clear();

	void debug();

	Region* get_region(const int id) const;
	Region* get_region(BWAPI::Position pos) const;

	PathFinding* get_path(BWAPI::Position pos1, BWAPI::Position pos2) const;
	PathFinding* get_path_with_weight(BWAPI::Position pos1, BWAPI::Position pos2) const;

private:

	PathFinding* dijkstra(BWAPI::Position pos1, BWAPI::Position pos2, const bool ignore_weight) const;

private:
	std::map<int, Region*> regions_;
};


class GameInfo
{
public:

	static GameInfo* instance_get();
	static void instance_clean();

	void init();
	void clear();

	void on_frame();
	void on_unit_show(BWAPI::Unit u);
	void on_unit_hide(BWAPI::Unit u);
	void on_unit_destroy(BWAPI::Unit u);

	const std::set<MineralLine*>& mineral_lines_get() const;

	void debug();

	Bank* bank_get() const;
	Map* map_get() const;

	MineralLine* get_nearest_mineral_line(BWAPI::Position position) const;

	MineralLine* get_nearest_mineral_line(MineralLine* line, bool with_gas = false);
	MineralLine* get_nearest_mineral_line(std::set<MineralLine*> line, bool with_gas = false);

	const bool opponent_position_found_get() const;
	void opponent_position_set(BWAPI::TilePosition pos);
	BWAPI::TilePosition opponent_position_get() const;
	std::set<BWAPI::TilePosition> spawn_positions_get() const;

	const std::set<BWAPI::Unit> show_units_get() const;
	const std::set<BWAPI::Unit> hide_units_get() const;

	std::set<BWAPI::Unit> units_in_sight(UnitAgent* u);
	std::set<BWAPI::Unit> units_in_sight(std::set<UnitAgent*> units);
	std::set<BWAPI::Unit> units_in_sight(std::set<ArmyAgent*> units);

	void add_position_to_debug(BWAPI::TilePosition pos, BWAPI::Color color = BWAPI::Colors::Red);
	void remove_position_to_debug(BWAPI::TilePosition pos);

	void add_building_request_position(BWAPI::TilePosition pos, BWAPI::UnitType type);
	void remove_building_request_position(BWAPI::TilePosition pos);

private:

	GameInfo();
	~GameInfo();

private:

	static GameInfo* instance_;

private:

	Bank* bank_;
	Map* map_;

	std::set<MineralLine*> mineral_lines_;
	std::set<BWAPI::TilePosition> spawn_positions_;

	BWAPI::TilePosition self_position_;
	BWAPI::TilePosition opponent_position_;
	bool opponent_position_found_;

	std::set<BWAPI::Unit> show_units_;
	std::set<BWAPI::Unit> hide_units_;

	std::map<BWAPI::TilePosition, BWAPI::Color> positions_to_debug_;
	std::map<BWAPI::TilePosition, BWAPI::UnitType> building_request_positions_;
};

# include "game-info.hxx"

#endif