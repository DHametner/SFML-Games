#include "gmspch.hpp"
#include "Config.hpp"

namespace gms
{
	void Configurable::configure(const Config& config)
	{
		this->config.columns = config.columns;
		this->config.rows    = config.rows;
		this->config.border  = config.border;
	}
}