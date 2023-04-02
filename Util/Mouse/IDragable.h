#pragma once

namespace ipgdlib
{
	namespace os
	{

		struct IDragable
		{
			virtual ~IDragable() {};
			virtual bool isDragable() const = 0;
		};

	}
}


