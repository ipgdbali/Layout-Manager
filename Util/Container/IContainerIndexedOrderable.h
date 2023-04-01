#pragma once

#include "IContainerIndexed.h"

namespace ipgdlib
{
    namespace container
    {

        template <typename TChildType,bool isIndexable = false>
        class IContainerIndexedOrderable :
            public IContainerIndexed<TChildType>
        {

            public:
                virtual void swap(size_t indexA, size_t indexB) = 0;
                virtual void rotate(size_t from, size_t to) = 0;
        
        };

    }
}


