#pragma once
namespace ipgdlib
{
	namespace layout
	{

		enum class eSizeAutonomy { None, Width, Height , Both };

		class ISizeAutonomy
		{
			virtual ~ISizeAutonomy() {}
			virtual eSizeAutonomy getSizeAutonomy() const = 0;
		};

	}
}

