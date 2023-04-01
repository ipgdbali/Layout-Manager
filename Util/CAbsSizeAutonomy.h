#pragma once

#include "ISizeAutonomy.h"
#include "iface/IAffectedAxis.h"
#include "Container/CIndexedChild.h"
#include "Geometry/SSize.h"

namespace ipgdlib
{
	namespace layout
	{

		using namespace ipgdlib::container;

		template <typename T,eSizeAutonomy autonomy>
		class CAbsSizeAutonomy {
			eSizeAutonomy getSizeAutonomy() override
			{
				return eSizeAutonomy::None;
			}
		};

		template <typename T>
		class CAbsSizeAutonomy<T,eSizeAutonomy::Width> :
			virtual public CIndexedChild,
			public ISizeAutonomy
		{
			public:

				eSizeAutonomy getSizeAutonomy() override
				{
					return eSizeAutonomy::Width;
				}

				virtual IAutonomyParent<eAffectedAxis::Horizontal>* getAutonomyParent() const = 0;

				virtual T getWidth() const = 0;
				
				virtual bool setWidth(T width)
				{
					return this->getAutonomyParent()->onChildSizeChanged(
						this->getIndex(),
						this->getWidth(),
						width
					);
				}
		};

		template <typename T>
		class CAbsSizeAutonomy<T, eSizeAutonomy::Height> :
			public CIndexedChild,
			public ISizeAutonomy
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
				return this->getAutonomyParent()->onChildSizeChanged(
					this->getChildIndex(),
					this->getHeight(),
					height
				);
			}
		};

		template <typename T>
		class CAbsSizeAutonomy<T, eSizeAutonomy::Both> :
			public CIndexedChild,
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
				return this->getAutonomyParent()->onChildSizeChanged(
					this->getChildIndex(),
					this->getSize(),
					size
				);
			}
		};

	}
}

