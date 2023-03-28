#pragma once
#pragma warning(disable : 4250)

#include "CAbsManagerStatic.h"
#include "../Util/CSizeableAutoReCalculate.h"

namespace ipgdlib
{
    namespace layout
    {
        using namespace ipgdlib::util;
        enum class eSplitterKind {eFixedScaled,eScaledFixed};

        template <typename T>
        class CAbsSplitter :
            public CSizeableAutoReCalculate<T>
        {
            public:
                CAbsSplitter(T && sizeFixed,T && space) :
                    CSizeableAutoReCalculate<T>(std::move(sizeFixed)),m_Space(std::move(space))
                {
                }

                virtual eAffectedAxis getAffectedAxis() const = 0;
                virtual eSplitterKind getSplitterKind() const = 0;

                const T& getSpace() const
                {
                    return this->m_Space;
                }

                void setSpace(const T& space)
                {
                    this->m_Space = space;
                    this->autoReCalculate();
                }

            private:
                T m_Space;

        };

        template <typename T,eSplitterKind kind,typename TCustomData = void>
        class CLMSplitterHorz :
            public CAbsManagerStatic<T,2,TCustomData, void>,
            public CAbsSplitter<T>
        {

            public:
                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CLMSplitterHorz(
                    T sizeFixed, 
                    T space,
                    std::array<CAbsBasePlaceHolder<T>*,2> pPlaceHolder
                ) : 
                    CAbsSplitter<T>(std::move(sizeFixed),std::move(space)), 
                    CAbsManagerStatic<T,2,TCustomData, void>(std::move(pPlaceHolder))
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        !std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CLMSplitterHorz(
                    _TCustomData customData,
                    T sizeFixed, 
                    T space,
                    std::array<CAbsBasePlaceHolder<T>*, 2> pPlaceHolder
                ) :
                    CAbsSplitter<T>(std::move(sizeFixed), std::move(space)),
                    CAbsManagerStatic<T, 2, TCustomData, void>(std::move(customData),std::move(pPlaceHolder))
                {
                }

                eAffectedAxis getAffectedAxis() const override
                {
                    return eAffectedAxis::Horizontal;
                }

                eSplitterKind getSplitterKind() const override
                {
                    return kind;
                }


                void reCalculate() override
                {
                    switch (this->getSplitterKind())
                    {
                        case ipgdlib::layout::eSplitterKind::eFixedScaled:
                        {
                            this->getChildPlaceHolder(0)->changeRect(
                                this->getRect().horzRePosition({ 0,this->getSize() - 1 })
                            );

                            this->getChildPlaceHolder(1)->changeRect(
                                this->getRect().horzRePosition(
                                    { this->getSize() + this->getSpace(),this->getRect().width() - 1})
                            );

                        }break;


                        case ipgdlib::layout::eSplitterKind::eScaledFixed:
                        {
                            this->getChildPlaceHolder(0)->changeRect(
                                this->getRect().makeHorz({
                                    this->getRect().left,
                                    this->getRect().right - this->getSize() - this->getSpace() }));

                            this->getChildPlaceHolder(1)->changeRect(this->getRect().makeHorz(
                                {
                                    this->getRect().right - (this->getSize() - 1),this->getRect().right
                                }));

                        }break;
                    }
                }
        };

        template <typename T,eSplitterKind kind, typename TCustomData = void>
        class CLMSplitterVert :
            public CAbsManagerStatic<T,2,TCustomData,void>,
            public CAbsSplitter<T>
        {

            public:

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CLMSplitterVert(
                    T sizeFixed, 
                    T space,
                    std::array<CAbsBasePlaceHolder<T>*,2> pPlaceHolder
                ) : 
                    CAbsSplitter<T>(std::move(sizeFixed),std::move(space)), 
                    CAbsManagerStatic<T,2,void,TCustomData>(std::move(pPlaceHolder))
                {
                }

                template <
                    typename _TCustomData = TCustomData,
                    typename std::enable_if< 
                        !std::is_same<_TCustomData, void>::value, 
                        bool 
                    >::type = true
                >
                CLMSplitterVert(
                    _TCustomData customData,
                    T sizeFixed, 
                    T space,
                    std::array<CAbsBasePlaceHolder<T>*, 2> pPlaceHolder
                ) : 
                    CAbsSplitter<T>(std::move(sizeFixed), std::move(space)), 
                    CAbsManagerStatic<T, 2, TCustomData,void>(std::move(customData),std::move(pPlaceHolder))
                {
                }

                eAffectedAxis getAffectedAxis() const override
                {
                    return eAffectedAxis::Vertical;
                }

                eSplitterKind getSplitterKind() const override
                {
                    return kind;
                }

                void reCalculate() override
                {
                    switch (this->getSplitterKind())
                    {
                        case ipgdlib::layout::eSplitterKind::eFixedScaled:
                        {
                            this->getChildPlaceHolder(0)->changeRect(
                                this->getRect().vertRePosition({ 0,this->getSize() - 1 })
                            );

                            this->getChildPlaceHolder(1)->changeRect(
                                this->getRect().vertRePosition(
                                    { this->getSize() + this->getSpace(),this->getRect().height() - 1})
                            );

                        }break;


                        case ipgdlib::layout::eSplitterKind::eScaledFixed:
                        {

                            this->getChildPlaceHolder(0)->changeRect(
                                this->getRect().makeVert({
                                    this->getRect().top,
                                    this->getRect().bottom - this->getSize() - this->getSpace() }));

                            this->getChildPlaceHolder(1)->changeRect(this->getRect().makeVert(
                                {
                                    this->getRect().bottom - (this->getSize() - 1),this->getRect().bottom
                                }));

                        }break;
                    }
                }

        };

    }
}


