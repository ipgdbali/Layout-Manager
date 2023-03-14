#pragma once

#include "CAbsManagerDynamic.h"

namespace ipgdlib
{
	namespace layout
	{

		template <typename T>
		class CLMDividerHorz :
			public CAbsManagerDynamic<T,size_t>
		{

			public:
				using child_type = CAbsManagerDynamic<T, size_t>::child_type;

				CLMDividerHorz(const T& spacing, std::vector< child_type > v)
					: m_Spacing(spacing), CAbsManagerDynamic<T, size_t>(v)
				{
				}

				eAffectedAxis getAffectedAxis() const override
				{
					return eAffectedAxis::Horizontal;
				}


				void reCalculate() override
				{
					size_t total_scale = 0;
					for (size_t li = 0; li < this->getChildCount(); li++)
						total_scale += this->getChildItem(li);
					
					double scaled_value = this->getRect().width();
					scaled_value -= ((this->getChildCount() - 1) * m_Spacing);
					scaled_value /= total_scale;
					double a = this->getRect().left;
					double b;

					for (size_t li = 0; li < this->getChildCount(); li++)
					{
						if (li == this->getChildCount() - 1)
							b = this->getRect().right;
						else
							b = a + (scaled_value * this->getChildItem(li)) - 1;

						this->getChildPlaceHolder(li)->changeRect({
								(T)a,
								this->getRect().top,
								(T)b,
								this->getRect().bottom
							}
						);
						a = b + 1 + m_Spacing;
					}
				}

			protected:

			private:
				T m_Spacing;

		};

		template <typename T>
		class CLMDividerVert :
			public CAbsManagerDynamic<T, size_t>
		{

		public:
			using child_type = CAbsManagerDynamic<T, size_t>::child_type;

			CLMDividerVert(const T& spacing, std::vector< child_type > v)
				: m_Spacing(spacing), CAbsManagerDynamic<T, size_t>(v)
			{
			}

			eAffectedAxis getAffectedAxis() const override
			{
				return eAffectedAxis::Vertical;
			}

			void reCalculate() override
			{
				size_t total_scale = 0;
				for (size_t li = 0; li < this->getChildCount(); li++)
					total_scale += this->getChildItem(li);

				double scaled_value = (double)this->getRect().height();
				scaled_value -= ((this->getChildCount() - 1) * m_Spacing);
				scaled_value /= total_scale;
				double a = (double)this->getRect().top;
				double b;

				for (size_t li = 0; li < this->getChildCount(); li++)
				{
					if (li == this->getChildCount() - 1)
						b = (double)this->getRect().bottom;
					else
						b = a + (scaled_value * this->getChildItem(li)) - 1;

					this->getChildPlaceHolder(li)->changeRect({
							this->getRect().left,
							(T)a,
							this->getRect().right,
							(T)b
						}
					);
					a = b + 1 + m_Spacing;
				}
			}

		protected:

		private:
			T m_Spacing;

		};


	}
}

