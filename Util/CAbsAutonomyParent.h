#pragma once

#include "IAutonomyParent.h"
#include "iface/IAffectedAxis.h"
#include "Geometry/SSize.h"

namespace ipgdlib
{
	namespace layout
	{
		using namespace ipgdlib::util;

		template <typename T,eAffectedAxis axis>
		class CAbsAutonomyParent {
		};

		template <typename T>
		class CAbsAutonomyParent<T,eAffectedAxis::Horizontal>:
			virtual public IAutonomyParent 
		{
		public:
			eAffectedAxis getAutonomyParentAffectedAxis() const override
			{
				return eAffectedAxis::Horizontal;
			}

			virtual bool onChildSizeChangedPermission(size_t index, const T& oldWidth, const T& newWidth) = 0;

		};

		template <typename T>
		class CAbsAutonomyParent<T, eAffectedAxis::Vertical> :
			virtual public IAutonomyParent
		{
		public:
			eAffectedAxis getAutonomyParentAffectedAxis() const override
			{
				return eAffectedAxis::Vertical;
			}

			virtual bool onChildSizeChangedPermission(size_t index, const T& oldHeight, const T& newHeight) = 0;

		};

		template <typename T>
		class CAbsAutonomyParent<T, eAffectedAxis::Both> :
			virtual public IAutonomyParent
		{
		public:
			eAffectedAxis getAutonomyParentAffectedAxis() const override
			{
				return eAffectedAxis::Both;
			}

			virtual bool onChildSizeChangedPermission(
				size_t index, 
				const ipgdlib::geometry::SSize<T>& oldHeight, 
				const ipgdlib::geometry::SSize<T>& newHeight
			) = 0;

		};

	}
}


