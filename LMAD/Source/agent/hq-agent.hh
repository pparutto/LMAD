#ifndef HQ_AGENT_HH_
# define HQ_AGENT_HH_

# include "unit-agent.hh"

class HQAgent : public UnitAgent
{
public:
	HQAgent(const BWAPI::Unit u);

	bool train_worker() const;

	const bool is_training() const;

protected:

	virtual void protected_on_frame() override;

private:
};

# include "hq-agent.hxx"

#endif /// !GATE_AGENT_HH_