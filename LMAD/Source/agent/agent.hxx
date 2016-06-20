inline void Agent::add_parent(Agent* parent)
{
	parents_.insert(parent);
}

inline void Agent::remove_parent(Agent* parent)
{
	parents_.erase(parent);
}

inline std::set<Agent*> Agent::parents_get() const
{
	return parents_;
}

inline void Agent::add_sub_agent(Agent* agent)
{
	sub_agents_.insert(agent);
	agent->add_parent(this);
}

inline void Agent::remove_sub_agent(Agent* agent)
{
	sub_agents_.erase(agent);
	agent->remove_parent(this);
}

inline void Agent::can_suicid_set(const bool value)
{
	can_suicid_ = value;
}