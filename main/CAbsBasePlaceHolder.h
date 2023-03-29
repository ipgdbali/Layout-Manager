#pragma once

#include "./../Geometry/SRect.h"
#include "../Util/CCustomData.h"


using namespace ipgdlib::util;

namespace ipgdlib
{
	namespace layout
	{

        template <typename T>
        class CAbsBasePlaceHolder :
            virtual public ICustomData
        {
        public:
            using Rect = ipgdlib::geometry::SRect<T>;
            using Point = ipgdlib::geometry::SPoint<T>;

            class CAbsBaseManager;

            CAbsBasePlaceHolder() :
                m_Rect({ 0 }), m_Parent(nullptr)
            {
            }

            virtual bool isManager() const = 0;

            bool isPointInside(const Point& p) const
            {
                return this->m_Rect.isPointInRect(p);
            }

            const Rect& getRect() const
            {
                return this->m_Rect;
            }

            void changeRect(Rect r)
            {
                this->onChangeRect(this->m_Rect, std::move(r));
            }

            bool hasParent() const
            {
                return this->m_Parent != nullptr;
            }

            CAbsBaseManager* const& getParent() const
            {
                return this->m_Parent;
            }

        protected:
            virtual void onChangeRect(Rect& r, Rect && nr)
            {
                r = std::move(nr);
            }

            void setParent(CAbsBaseManager* const parent)
            {
                this->m_Parent = parent;
            }

        private:
            Rect m_Rect;
            CAbsBaseManager* m_Parent;

        };

	}
}