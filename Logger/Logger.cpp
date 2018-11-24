#include "Logger.h"

#include <algorithm>

namespace cl
{

	bool Logger::add_output(std::ostream &output)
	{
		auto found = std::find(_outputs.begin(), _outputs.end(), &output);
		if (found != _outputs.end())
		{
			//output already exist
			return false;
		}
		else
		{
			_outputs.push_back(&output);
			return true;
		}
	}

	bool Logger::remove_output(std::ostream &output)
	{
		auto found = std::find(_outputs.begin(), _outputs.end(), &output);
		if (found != _outputs.end())
		{
			_outputs.erase(found);
			return true;
		}
		else
		{
			//output isn't in _outputs
			return false;
		}
	}

	void Logger::set_loglevel(const LogLevel& loglevel)
	{
		_current_level = loglevel;
	}

	LogLevel Logger::get_loglevel() const
	{
		return _current_level;
	}

} // namespace cl