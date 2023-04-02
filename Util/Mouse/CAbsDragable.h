#pragma once

#include "CAbsDragableBase.h"

namespace ipgdlib
{
	namespace os
	{

		template <
			typename T,
			typename U
		>
		class CAbsDragable :
			public CAbsDragableBase<T, true>
		{

		public:

			CAbsDragable(bool def) :
				CAbsDragableBase<T, true>(def)
			{

			}

			virtual void setDrag(size_t index, ipgdlib::geometry::SSize<U> size) = 0;

		};

	}
}