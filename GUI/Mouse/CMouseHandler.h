#pragma once

#include "../Util/Geometry/SPoint.h"

namespace ipgdlib
{
	namespace os
	{

		using namespace ipgdlib::geometry;

		template <
			typename T,
			typename TDragItem
		>
		class CMouseHandler
		{
			public:
				CMouseHandler(SPoint<T> pos,TDragItem item) :
					m_IsLButtonDown(false),
					m_LButtonDownPosition(std::move(pos)),
					m_DragItem(std::move(item))
				{
				}

				bool isLButtonDown() const
				{
					return this->m_IsLButtonDown;
				}

				const SPoint<T> &getLButtonDownPosition() const
				{
					return this->m_LButtonDownPosition;
				}

				const TDragItem &getDragItem() const
				{
					return this->m_DragItem;
				}

				virtual void onLButtonDown(SPoint<T> pos)
				{
					m_IsLButtonDown = true;
					m_LButtonDownPosition = std::move(pos);
				}

				virtual void onMouseMove(SPoint<T> pos) = 0;

				virtual void onLButtonUp(SPoint<T> pos)
				{
					m_IsLButtonDown = false;
				}

			protected:
				void setDragItem(TDragItem item)
				{
					this->m_DragItem = std::move(item);
				}

				TDragItem &getDragItemRef()
				{
					return this->m_DragItem;
				}

			private:
				bool m_IsLButtonDown;
				SPoint<T> m_LButtonDownPosition;
				TDragItem m_DragItem;
		};

	}

}

