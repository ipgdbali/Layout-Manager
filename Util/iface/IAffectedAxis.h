#pragma once
namespace ipgdlib
{
	namespace util
	{
		enum class eAffectedAxis { Horizontal, Vertical, Both };

		class IAffectedAxis
		{

		public:
			virtual ~IAffectedAxis() {};
			virtual eAffectedAxis getAffectedAxis() const = 0;
		
		};

	}
}

