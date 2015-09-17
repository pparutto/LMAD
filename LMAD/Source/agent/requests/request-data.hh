#ifndef REQUEST_DATA_HH_
# define REQUEST_DATA_HH_

class RequestData
{
public:
	RequestData();

	const unsigned priority_get() const;
	const unsigned timeout_get() const;
	const unsigned phase_get() const;

	void on_frame();

	void priority_set(const unsigned priority);
	void timeout_set(const unsigned timeout);
	void phase_set(const unsigned phase);


private:

	unsigned priority_;
	unsigned timeout_;
	unsigned phase_;
};

# include "request-data.hxx"

#endif