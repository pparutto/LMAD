inline const unsigned RequestData::priority_get() const
{
	return priority_;
}

inline const unsigned RequestData::timeout_get() const
{
	return timeout_;
}

inline const unsigned RequestData::phase_get() const
{
	return phase_;
}

inline void RequestData::on_frame()
{
	--timeout_;
}

inline void RequestData::priority_set(const unsigned priority)
{
	priority_ = priority;
}

inline void RequestData::timeout_set(const unsigned timeout)
{
	timeout_ = timeout;
}

inline void RequestData::phase_set(const unsigned phase)
{
	phase_ = phase;
}