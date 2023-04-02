#pragma once

#include "ISizeAutonomy.h"
#include "iface/IAffectedAxis.h"
#include "Container/CIndexedChild.h"
#include "Geometry/SSize.h"
#include "IAutonomyParent.h"
#include "CAbsAutonomyParent.h"

namespace ipgdlib
{
	namespace layout
	{

		template <typename T,eSizeAutonomy autonomy>
		class CAbsSizeAutonomy {};

		template <typename T>
		class CAbsSizeAutonomy<T, eSizeAutonomy::None> :
			virtual public ISizeAutonomy
		{
			~CAbsSizeAutonomy() override
			{
			}

			eSizeAutonomy getSizeAutonomy() const override
			{
				return eSizeAutonomy::None;
			}
		};

		template <typename T>
		class CAbsSizeAutonomy<T,eSizeAutonomy::Width> :
			virtual public CIndexedChild,
			virtual public ISizeAutonomy
		{
			public:

				eSizeAutonomy getSizeAutonomy() override
				{
					return eSizeAutonomy::Width;
				}

				virtual CAbsAutonomyParent<T, eAffectedAxis::Horizontal>* getAutonomyParent() const = 0;
				
				virtual T getWidth() const = 0;
				
				virtual bool setWidth(T width)
				{
					return this->getAutonomyParent()->onChildSizeChangedPermission(
						this->getChildIndex(),
						this->getWidth(),
						width
					);
				}
		};

		template <typename T>
		class CAbsSizeAutonomy<T, eSizeAutonomy::Height> :
			virtual public CIndexedChild,
			virtual public ISizeAutonomy
		{
		public:

			eSizeAutonomy getSizeAutonomy() override
			{
				return eSizeAutonomy::Height;
			}

			virtual IAutonomyParent<eAffectedAxis::Vertical>* getAutonomyParent() const = 0;

			virtual T getHeight() const = 0;
			virtual bool setHeight(T height)
			{
				return this->getAutonomyParent()->onChildSizeChangedPermission(
					this->getChildIndex(),
					this->getHeight(),
					height
				);
			}
		};

		template <typename T>
		class CAbsSizeAutonomy<T, eSizeAutonomy::Both> :
			virtual public CIndexedChild,
			public ISizeAutonomy
		{
		public:
			using Size = ipgdlib::geometry::SSize<T>;
			
			eSizeAutonomy getSizeAutonomy() override
			{
				return eSizeAutonomy::Both;
			}

			virtual IAutonomyParent<eAffectedAxis::Both>* getAutonomyParent() const = 0;

			virtual Size getSize() const = 0;
			virtual bool setSize(Size size)
			{
				return this->getAutonomyParent()->onChildSizeChangedPermission(
					this->getChildIndex(),
					this->getSize(),
					size
				);
			}
		};

	}
}

