#ifndef GAME_INFO_HH_
# define GAME_INFO_HH_

# include <BWAPI/Position.h>
# include <BWAPI/Region.h>

# include <set>
# include <utility>

class MineralLine
{
public:

	MineralLine(const int& region_id,
							std::set<std::pair<BWAPI::Position, int> > mineral_patches, 
							std::pair<BWAPI::Position, int> gas);

	const int& region_id_get() const;

private:

	std::set<std::pair<BWAPI::Position, int> > mineral_patches_;
	std::pair<BWAPI::Position, int> gas_;

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

private:

	GameInfo();

private:

	static GameInfo* instance_;

private:

	std::set<Region*> regions_;

};

# include "game-info.hxx"

#endif