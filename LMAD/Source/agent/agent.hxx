inline void Agent::parent_set(Agent* parent)
{
	if (parent_ != nullptr)
	{
		std::cerr << "Warning : an agent is getting a new parent, but the last one was not reseted to null" << std::endl;
	}
	else
	{
		parent_ = parent;
	}
}

inline Agent* Agent::parent_get() const
{
	return parent_;
}

inline void Agent::add_sub_agent(Agent* agent)
{
	sub_agents_.insert(agent);
}

inline void Agent::remove_sub_agent(Agent* agent)
{
	sub_agents_.erase(agent);
}