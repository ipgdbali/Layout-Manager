#pragma once

#include "CAbsManagerStatic.h"

namespace ipgdlib
{

	namespace layout
	{

		template <typename T,typename V = void>
		class CLMPadder :
			public CAbsManagerStatic<T,1,void,V>
		{
		public:
			using Rect = typename CPlaceHolder<T>::Rect;

			CLMPadder(const Rect& padding, CPlaceHolder<T>* pPlaceHolder = nullptr) :
				CAbsManagerStatic<T, 1,void, V>({ pPlaceHolder }), m_Padding(padding)
			{
			}

			eAffectedAxis getAffectedAxis() const override
			{
				return eAffectedAxis::Both;
			}


			void setPadding(const Rect& padding)
			{
				this->m_Padding = padding;
				this->autoReCalculate();
			}

			const Rect& getPadding() const
			{
				return this->m_Padding;
			}

			void reCalculate() override
			{
				this->getChildPlaceHolder(0)->changeRect(this->getRect().padding(m_Padding));
			}

		protected:
		private:
			Rect m_Padding;
		};


	}


};


