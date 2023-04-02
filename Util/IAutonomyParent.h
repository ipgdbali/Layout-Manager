#pragma once

#include "iface/IAffectedAxis.h"

namespace ipgdlib
{
	namespace layout
	{
		using namespace ipgdlib::util;

		struct IAutonomyParent
		{
			virtual ~IAutonomyParent() {};
			virtual eAffectedAxis getAutonomyParentAffectedAxis() const = 0;
		};

	}
}

