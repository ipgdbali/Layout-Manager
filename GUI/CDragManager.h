#pragma once

#include "../Geometry/SPoint.h"

namespace ipgdlib
{
	namespace os
	{

		using namespace ipgdlib::geometry;

		template <typename T,typename U>
		class CDragManager
		{
			public:
				CDragManager() :
					m_IsDragging(false),m_StartPoint(0),m_pObj(nullptr)
				{
				}

				U* getObj()
				{
					return this->m_pObj;
				}

				bool isDragging() const
				{
					return this->m_IsDragging;
				}

				bool startDrag(const SPoint<T>& p,U* pObj)
				{
					this->m_IsDragging = this->onDragStart(p, pObj);
					return this->m_IsDragging;
				}

				void endDrag(const SPoint<T>& p)
				{
					if (this->m_IsDragging)
					{
						this->onDragEnd(this->m_StartPoint, p);
						this->m_IsDragging = false;
						this->m_pObj = nullptr;
					}
				}

			protected:

				virtual bool onDragStart(const SPoint<T>& s, U* pObj)
				{
					this->m_StartPoint = s;
					this->m_pObj = pObj;
					return true;
				}

				virtual void onDragEnd(const SPoint<T>& s, const SPoint<T>& p) = 0;

			private:
				bool m_IsDragging;
				SPoint<T>	m_StartPoint;
				U* m_pObj;
		};
	}

}
