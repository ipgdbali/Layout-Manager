#pragma once

#include "CAbsManagerStatic.h"

namespace ipgdlib
{

	namespace layout
	{

		template <
			typename T,
			typename TCustomData = void
		>
		class CLMPadder :
			public CAbsManagerStatic<T,1,TCustomData, void>
		{
		public:
			using Rect = typename CAbsBasePlaceHolder<T>::Rect;
			using Point = typename CAbsBasePlaceHolder<T>::Point;

			template <
				typename _V = TCustomData,
				typename std::enable_if< 
					std::is_same<_V, void>::value, 
					bool 
				>::type = true
			>
			CLMPadder(
				Rect padding, 
				CAbsBasePlaceHolder<T>* const pPlaceHolder
			) :
				m_Padding(std::move(padding)),
				CAbsManagerStatic<T, 1,TCustomData,void>({ pPlaceHolder })
			{
			}

			template <
				typename _V = TCustomData,
				typename std::enable_if< !std::is_same<_V, void>::value, bool >::type = true
			>
			CLMPadder(
				_V customData,
				Rect padding, 
				CAbsBasePlaceHolder<T>* const pPlaceHolder
			) :
				CAbsManagerStatic<T, 1,TCustomData,void>(customData,{ pPlaceHolder }), 
				m_Padding(padding)
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


