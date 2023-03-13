#pragma once

#include "CAbsManagerStatic.h"
#include "../Util/CSizeableAutoReCalculate.h"

namespace ipgdlib
{
    namespace layout
    {
        using namespace ipgdlib::util;
        enum class eSplitterKind {eFixedScaled,eScaledFixed};

        template <typename T,eSplitterKind kind>
        class CAbsSplitter :
            public CSizeableAutoReCalculate<T>
        {
            public:
                CAbsSplitter(const T& sizeFixed,const T& space) :
                    CSizeableAutoReCalculate<T>(sizeFixed),m_Space(space)
                {
                }

                constexpr eSplitterKind getSplitterKind() const
                {
                    return kind;
                }

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

        template <typename T,eSplitterKind kind>
        class CLMHorzSplitter :
            public CAbsManagerStatic<T,2>,
            public CAbsSplitter<T,kind>
        {

            public:
                CLMHorzSplitter(const T& sizeFixed, const T& space,
                    std::array<CPlaceHolder<T>*,2> pPlaceHolder)
                    : CAbsSplitter<T,kind>(sizeFixed,space), CAbsManagerStatic<T,2>(pPlaceHolder)
                {
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

        template <typename T,eSplitterKind kind>
        class CLMVertSplitter :
            public CAbsManagerStatic<T,2>,
            public CAbsSplitter<T,kind>
        {

            public:
                CLMVertSplitter(const T& sizeFixed, const T& space,
                    std::array<CPlaceHolder<T>*,2> pPlaceHolder)
                    : CAbsSplitter<T,kind>(sizeFixed,space), CAbsManagerStatic<T,2>(pPlaceHolder)
                {
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


