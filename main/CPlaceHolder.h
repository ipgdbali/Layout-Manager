#pragma once

#include "CAbsBasePlaceHolder.h"
#include "../Util/CAbsSizeAutonomy.h"

namespace ipgdlib
{
    namespace layout
    {

        template <
            typename T,
            eSizeAutonomy sizeAutonomy = eSizeAutonomy::None,
            typename TCustomData = void
        >
        class CPlaceHolder : 
            public CAbsBasePlaceHolder<T>,
            public CCustomData<TCustomData>,
            public CAbsSizeAutonomy<T,sizeAutonomy>
        {

            public:
                using Rect = CAbsBasePlaceHolder<T>::Rect;
                using Point = CAbsBasePlaceHolder<T>::Point;

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        std::is_same<_TCustomData, void>::value, 
                        bool
                    >::type = true
                >
                CPlaceHolder() :
                    CAbsBasePlaceHolder<T>(),
                    CCustomData<_TCustomData>()
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        !std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CPlaceHolder(_TCustomData customData) : 
                    CAbsBasePlaceHolder<T>(),
                    CCustomData<_TCustomData>(std::move(customData))
                {
                }

                bool isManager() const override final
                {
                    return false;
                }

        };

    };
};