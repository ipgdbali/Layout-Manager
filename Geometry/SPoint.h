#pragma once

#include <ostream>

namespace ipgdlib
{
	namespace geometry
	{
		template <typename T>
		struct SSize;

		template <typename T>
		struct SPoint
		{
			T x;
			T y;

			SPoint(T xy) :
				x(xy), y(xy)
			{
			}


			SPoint(T x, T y) :
				x(x), y(y)
			{
			}

			bool operator == (const SPoint<T>& p) const
			{
				return this->x == p.x && this->y == p.y;
			}

			SSize<T> operator - (const SPoint<T>& p) const
			{
				return { this->x - p.x + 1,this->y - p.y + 1 };
			}

			SPoint<T> operator + (const SSize<T>& sz) const
			{
				return { this->x + sz.width - 1,this->y + sz.height - 1 };
			}

			template <typename U = T>
			SPoint<U> operator / (const U& div)
			{
				return { this->x / div,this->y / div };
			}


			template <typename U = T>
			U hypotenuse() const
			{
				return sqrt(T(x) * T(x) + T(y) * T(y));
			}

			template <typename U = T>
			U sin()
			{
				return U(this->y) / this->hypotenuse<U>();
			}

			template <typename U = T>
			U cos()
			{
				return U(this->x) / this->hypotenuse<U>();
			}

			template <typename U = T>
			U tan()
			{
				return U(this->y) / U(this->x);
			}

			template <typename U = T>
			SPoint<U> dot(const SPoint<U>& b)
			{
				return { this->x * b.x + this->y + b.y };
			}

			template <typename U = T>
			U cosAngle(const SPoint<U>& b)
			{
				return this->dot<U>(b) / (this->hypotenuse<U>() * b.hypotenuse<U>());
			}

		};

		template <typename T>
		static std::ostream& operator << (std::ostream& os, const SPoint<T>& p)
		{
			os << '(' << p.x << ',' << p.y << ')';
			return os;
		}

		template <typename T>
		static std::wostream& operator << (std::wostream& os, const SPoint<T>& p)
		{
			os << '(' << p.x << ',' << p.y << ')';
			return os;
		}

	}
}
