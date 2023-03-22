#pragma once

#include "CAbsManagerStatic.h"

namespace ipgdlib
{
	namespace layout
	{

		enum class eAlignHorz { Left, Middle, Right, Stretch };
		enum class eAlignVert { Top, Middle, Bottom, Stretch };

		template <typename T,typename V = void>
		class CLMAlignerHorz :
			public CAbsManagerStatic<T,1,void,V>
		{

		public:
			CLMAlignerHorz(eAlignHorz horzAlign, const T& width, CPlaceHolder<T>* pPlaceHolder) :
				CAbsManagerStatic<T, 1,void,V>({ pPlaceHolder }), m_HAlign(horzAlign), m_Width(width)
			{
			}

			eAffectedAxis getAffectedAxis() const override
			{
				return eAffectedAxis::Horizontal;
			}

			void setHAlign(eAlignHorz align)
			{
				this->m_HAlign = align;
				this->autoReCalculate();
			}

			eAlignHorz getHAlign() const
			{
				return this->m_HAlign;
			}

			void setWidth(const T& width)
			{
				this->m_Width = width;
				this->autoReCalculate();
			}

			const T& getWidth() const
			{
				return this->m_Width;
			}

			void setAlignAndWidth(eAlignHorz align, const T& width)
			{
				this->m_HAlign = align;
				this->m_Width = width;
				this->autoReCalculate();
			}


			void reCalculate() override
			{

				switch (m_HAlign)
				{
				case eAlignHorz::Left:
				{
					this->getChildPlaceHolder(0)->changeRect(
						{
							this->getRect().left,
							this->getRect().top,
							this->getRect().left + this->m_Width - 1,
							this->getRect().bottom,

						});
				}break;

				case eAlignHorz::Middle:
				{
					T start = this->getRect().left + (this->getRect().width() - this->m_Width) / 2 - 1;
					this->getChildPlaceHolder(0)->changeRect(
						{
							start,
							this->getRect().top,
							start + this->m_Width - 1,
							this->getRect().bottom,

						});
				}break;

				case eAlignHorz::Right:
				{
					this->getChildPlaceHolder(0)->changeRect(
						{
							this->getRect().right - (this->m_Width - 1),
							this->getRect().top,
							this->getRect().right,
							this->getRect().bottom,

						});
				}break;

				case eAlignHorz::Stretch:
				{
					this->getChildPlaceHolder(0)->changeRect(this->getRect());
				}break;

				}

			}

		private:
			eAlignHorz m_HAlign;
			T m_Width;
		};


		template <typename T,typename V = void>
		class CLMAlignerVert :
			public CAbsManagerStatic<T,1,void,V>
		{

		public:
			CLMAlignerVert(eAlignVert vertAlign, const T& height, CPlaceHolder<T>* pPlaceHolder) :
				CAbsManagerStatic<T, 1,void,V>({ pPlaceHolder }), m_VAlign(vertAlign), m_Height(height)
			{
			}

			eAffectedAxis getAffectedAxis() const override
			{
				return eAffectedAxis::Vertical;
			}

			void setVAlign(eAlignVert align)
			{
				this->m_VAlign = align;
				this->autoReCalculate();
			}

			eAlignVert getVAlign() const
			{
				return this->m_VAlign;
			}

			void setHeight(const T& height)
			{
				this->m_Height = height;
				this->autoReCalculate();
			}

			const T& getHeight() const
			{
				return this->m_Height;
			}

			void setAlignAndHeight(eAlignVert align, const T& height)
			{
				this->m_VAlign = align;
				this->m_Height = height;
				this->autoReCalculate();
			}

			void reCalculate() override
			{

				switch (m_VAlign)
				{

				case eAlignVert::Top:
				{
					this->getChildPlaceHolder(0)->changeRect(
						{
							this->getRect().left,
							this->getRect().top,
							this->getRect().right,
							this->getRect().top + (this->m_Height - 1)
						});
				}break;

				case eAlignVert::Middle:
				{
					T start = this->getRect().top + (this->getRect().height() - this->m_Height) / 2 - 1;
					this->getChildPlaceHolder(0)->changeRect(
						{
							this->getRect().left,
							start,
							this->getRect().right,
							start + (this->m_Height - 1)
						});

				}break;

				case eAlignVert::Bottom:
				{
					this->getChildPlaceHolder(0)->changeRect(
						{
							this->getRect().left,
							this->getRect().bottom - (this->m_Height - 1),
							this->getRect().right,
							this->getRect().bottom
						});
				}break;

				case eAlignVert::Stretch:
				{

				}break;

				}

			}

		private:
			eAlignVert m_VAlign;
			T m_Height;

		};


	}
};