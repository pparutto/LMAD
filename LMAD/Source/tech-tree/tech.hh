#ifndef TECH_HH_
# define TECH_HH_

# include <set>

class Tech
{
public:

private:
	std::set<Tech*> lockers_;
};

#endif