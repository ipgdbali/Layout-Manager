#pragma once

#include "SPoint.h"
#include "SSize.h"
#include "SRange.h"
#include <Windows.h>

namespace ipgdlib
{
	namespace geometry
	{

		template <typename T>
		struct SRect
		{
			T left;
			T top;
			T right;
			T bottom;


			SRect(const SRect<T>& r) :
				SRect(r.left, r.top, r.right, r.bottom)
			{
			}

			SRect<T>& operator = (const SRect& r)
			{
				this->left = r.left;
				this->top = r.top;
				this->right = r.right;
				this->bottom = r.bottom;
				return *this;
			}

			SRect(SRect<T>&& r) :
				SRect(std::move(r.left), std::move(r.top), std::move(r.right), std::move(r.bottom))
			{
			}

			SRect<T>& operator = (SRect&& r)
			{
				this->left = std::move(r.left);
				this->top = std::move(r.top);
				this->right = std::move(r.right);
				this->bottom = std::move(r.bottom);
				return *this;
			}

			SRect(const T& all) :
				left(all), top(all), right(all), bottom(all)
			{
			}

			SRect(const T& lefttop, const T& rightbottom) :
				left(lefttop), top(lefttop), right(rightbottom), bottom(rightbottom)
			{
			}

			SRect(const T& left, const T& top, const T& right, const T& bottom) :
				left(left), top(top), right(right), bottom(bottom)
			{
			}

			template <typename U>
			SRect(const SRect<U>& ref) :
				left(T(ref.left)), top(T(ref.top)), right(T(ref.right)), bottom(T(ref.bottom))
			{
			}

			SRect(const RECT& ref) :
				left(T(ref.left)), top(T(ref.top)), right(T(ref.right)), bottom(T(ref.bottom))
			{
			}

			bool operator == (const SRect<T>& r) const
			{
				return this->left == r.left && this->top == r.top && this->right == r.right && this->bottom == r.bottom;
			}

			operator RECT() const
			{
				RECT r = { (LONG)this->left,(LONG)this->top,(LONG)this->right,(LONG)this->bottom };
				return r;
			}

			bool isPointInside(const SPoint<T> &p) const
			{
				if (this->left <= p.x && p.x <= this->right && this->top <= p.y && p.y <= this->bottom)
					return true;
				else
					return false;
			}

			T centerHorz() const
			{
				return this->left + this->width() / 2;
			}

			T centerVert() const
			{
				return this->top + this->height() / 2;
			}

			SPoint<T> center() const
			{
				return { this->centerHorz(),this->centerVert() };
			}

			SRange<T> horz() const
			{
				return { this->left,this->right };
			}

			SRange<T> vert() const
			{
				return { this->top,this->bottom };
			}

			T width() const
			{
				return this->right - this->left + 1;
			}

			T height() const
			{
				return this->bottom - this->top + 1;
			}

			SSize<T> size() const
			{
				return { this->width(),this->height()};
			}

			SRect<T> padding(const SRect<T>& r) const
			{
				return { left + r.left,top + r.top,right - r.right,bottom - r.bottom };
			}

			SRect<T> horzRePosition(const SRange<T>& p) const
			{
				return { this->left + p.a,this->top,this->left + p.b,this->bottom };
			}

			SRect<T> vertRePosition(const SRange<T>& p) const
			{
				return { this->left,this->top + p.a,this->right,this->top + p.b };
			}

			SRect<T> rePosition(const SRect<T>& r) const
			{
				return { this->left + r.left,this->top + r.top,this->left + r.right,this->top + r.bottom };
			}

			SRect<T> makeHorz(const SRange<T>& horz) const
			{
				return { horz.a,this->top,horz.b,this->bottom };
			}

			SRect<T> makeVert(const SRange<T>& vert) const
			{
				return { this->left,vert.a,this->right,vert.b};
			}

			SRect<T> horzMoveAdd(const T& delta)
			{
				return { this->left + delta,this->top,this->right + delta,this->bottom };
			}

			SRect<T> horzMoveSub(const T& delta)
			{
				return { this->left - delta,this->top,this->right - delta,this->bottom };
			}

			SRect<T> vertMoveAdd(const T& delta)
			{
				return { this->left,this->top + delta,this->right,this->bottom + delta };
			}

			SRect<T> vertMoveSub(const T& delta)
			{
				return { this->left,this->top - delta,this->right,this->bottom - delta };
			}

			SRect<T> moveAdd(const SSize<T>& delta) const
			{
				return { this->left + delta.width,this->top + delta.height,this->right + delta.width,this->bottom + delta.height };
			}

			SRect<T> moveSub(const SSize<T>& delta) const
			{
				return { this->left - delta.width,this->top - delta.height,this->right - delta.width,this->bottom - delta.height };
			}

			SRect<T> makeLeft(const T& l) const
			{
				return { l,this->top,l + this->width() - 1,this->bottom };
			}

			SRect<T> makeTop(const T& t) const
			{
				return { this->left,t,this->right,t + this->height() - 1 };
			}

			SRect<T> makeRight(const T& r) const
			{
				return { r - (this->width() - 1),this->top,r,this->bottom };
			}

			SRect<T> makeBottom(const T& b) const
			{
				return { this->left,b - (this->height() - 1),this->right,bottom };
			}

			SRect<T> makeCenterHorz(const T& horz) const
			{
				T centerHorz = (horz - this->width() / 2);
				return { this->left + centerHorz,this->top,this->right + centerHorz,this->bottom };
			}

			SRect<T> makeCenterVert(const T& vert) const
			{
				T centerVert = (vert - this->height() / 2);
				return { this->left,this->top + centerVert ,this->right,this->bottom + centerVert };
			}

			SRect<T> makeCenter(const SPoint<T>& newCenter) const
			{
				std::pair<T, T> delta(newCenter.a - this->width() / 2, newCenter.b - this->height() / 2);
				return { this->left + delta.a,this->top + delta.b,this->right + delta.a,this->bottom + delta.b};
			}

			SRect<T> unionWith(const SRect<T>& r) const
			{
				return {
					(this->left < r.left) ? this->left : r.left,
					(this->top < r.top) ? this->top : r.top,
					(this->right < r.right) ? this->right : r.right ,
					(this->bottom < r.bottom) ? this->bottom : r.bottom
				};
			}
		};

		template <typename T>
		static std::ostream& operator << (std::ostream& os, const ipgdlib::geometry::SRect<T>& r)
		{
			os << '(' << r.left << ',' << r.top << ',' << r.right << ',' << r.bottom << ')';
			return os;
		}

		template <typename T>
		static std::wostream& operator << (std::wostream& os, const ipgdlib::geometry::SRect<T>& r)
		{
			os << '(' << r.left << ',' << r.top << ',' << r.right << ',' << r.bottom << ')';
			return os;
		}


	}
};

