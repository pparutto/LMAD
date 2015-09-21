#ifndef GAME_INFO_HH_
# define GAME_INFO_HH_

# include <BWAPI/Position.h>
# include <BWAPI/Region.h>
# include <BWAPI/Game.h>

# include <set>
# include <map>
# include <utility>

# include "../agent/worker-agent.hh"

class Bank
{
public:

	Bank(unsigned income_precision);
	~Bank();

	void on_frame();

	void add_gas(const int value);
	void add_mineral(const int value);

	const int gas_get() const;
	const int mineral_get() const;

	const bool request_mineral(const int value);
	const bool request_gas(const int value);

	const unsigned gas_income_get() const;
	const unsigned mineral_income_get() const;

private:

	int mineral_;
	int gas_;

	unsigned* mineral_incomes_;
	unsigned mineral_income_;

	unsigned* gas_incomes_;
	unsigned gas_income_;

	unsigned indice_;

	const unsigned income_precision_;
};

class Resource
{
public:
	Resource(BWAPI::Unit unit, BWAPI::Position position);

	BWAPI::Unit unit_get() const;
	BWAPI::Position position_get() const;

	void add_worker(WorkerAgent* worker);
	void remove_worker(WorkerAgent* worker);

	const unsigned worker_count() const;
	const std::set<WorkerAgent*> workers_get() const;

	const bool is_being_gathered_get() const;
	void is_being_gathered_set(const bool value);

private:

	BWAPI::Unit unit_;
	BWAPI::Position position_;
	bool is_being_gathered_;
	std::set<WorkerAgent*> workers_;

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

private:
	const bool is_near(const BWAPI::Unit resource) const;

private:

	std::set<Resource*> mineral_patches_;
	std::set<Resource*> gas_;

	int region_id_;
};

class Region
{
public:

	Region(BWAPI::Region region);

	const BWAPI::Region region_get() const;

private:
	BWAPI::Region region_;
};

class GameInfo
{
public:

	static GameInfo* instance_get();
	static void instance_clean();

	void init();
	void clear();

	void on_frame();

	const std::set<MineralLine*>& mineral_lines_get() const;

	void debug();

	Bank* bank_get() const;

	MineralLine* get_nearest_mineral_line(BWAPI::Position position) const;

private:

	GameInfo();
	~GameInfo();

private:

	static GameInfo* instance_;

private:

	Bank* bank_;
	std::set<Region*> regions_;
	std::set<MineralLine*> mineral_lines_;

};

# include "game-info.hxx"

#endif