#pragma once

#include "CAbsBasePlaceHolder.h"

namespace ipgdlib
{
    namespace layout
    {

        template <typename T,typename TItem=void>
        class CPlaceHolder : 
            public CAbsBasePlaceHolder<T>,
            public CCustomData<TItem>
        {

            public:
                using Rect = CAbsBasePlaceHolder<T>::Rect;
                using Point = CAbsBasePlaceHolder<T>::Point;

                template <
                    typename _TItem = TItem,
                    typename std::enable_if< std::is_same<_TItem, void>::value, bool >::type = true
                >
                CPlaceHolder() :
                    CAbsBasePlaceHolder<T>(),CCustomData()
                {
                }

                template <
                    typename _TItem = TItem,
                    typename std::enable_if< !std::is_same<_TItem, void>::value, bool >::type = true
                >
                CPlaceHolder(const _TItem& customData)
                    : CAbsBasePlaceHolder<T>(),CCustomData<_TItem>(customData)
                {
                }

                template <
                    typename _TItem = TItem,
                    typename std::enable_if< !std::is_same<_TItem, void>::value, bool >::type = true
                >
                CPlaceHolder(_TItem && customData)
                    : CAbsBasePlaceHolder<T>(), CCustomData<_TItem>(std::move(customData))
                {
                }

                bool isManager() const override final
                {
                    return false;
                }


        };



    };
};