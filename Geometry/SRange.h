#pragma once

namespace ipgdlib
{
	namespace geometry
	{

		template <typename T>
		struct SRange
		{
			T a;
			T b;

			SRange(T ab) :
				a(ab), b(ab)
			{

			}

			SRange(T a, T b)
				: a(a), b(b)
			{

			}

			T length() const
			{
				return b - a;
			}

		};

	}
}

