#ifndef GAME_INFO_HH_
# define GAME_INFO_HH_

# include <BWAPI/Position.h>
# include <BWAPI/Region.h>
# include <BWAPI/Game.h>

# include <set>
# include <utility>

class MineralLine
{
public:

	MineralLine(const int& region_id);
	const int& region_id_get() const;

	void init_gas(const BWAPI::Unit resource);
	void init_mineral(const BWAPI::Unit resource);

	bool add_if_near_gas(const BWAPI::Unit resource);
	bool add_if_near_mineral(const BWAPI::Unit resource);

	BWAPI::Position center_get() const;

private:
	const bool is_near(const BWAPI::Unit resource) const;

private:

	std::set<std::pair<BWAPI::Unit, int> > mineral_patches_;
	std::set<std::pair<BWAPI::Unit, int> > gas_;

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
	const std::set<MineralLine*>& mineral_lines_get() const;

	void debug();

private:

	GameInfo();

private:

	static GameInfo* instance_;

private:

	std::set<Region*> regions_;
	std::set<MineralLine*> mineral_lines_;

};

# include "game-info.hxx"

#endif