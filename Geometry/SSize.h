#pragma once

#include <ostream>

namespace ipgdlib
{
	namespace geometry
	{
		template <typename T>
		struct SPoint;

		template <typename T>
		struct SSize
		{
			T width;
			T height;

			SSize(const T& wh)
				: width(wh), height(wh)
			{
			}

			SSize(const T& w, const T& h)
				: width(w), height(h)
			{
			}

			bool operator == (const SSize<T>& sz) const
			{
				return this->width == sz.width && this->height == sz.height;
			}

			template <typename U = T>
			U hypotenuse() const
			{
				return sqrt(T(width) * T(width) + T(height) * T(height));
			}

			SPoint<T> endOf(const SPoint<T>& start) const
			{
				return { start.x + this->width - 1,start.y + this->height - 1 };
			}

			SPoint<T> startOf(const SPoint<T>& end) const
			{
				return { end.x - (this->width - 1),end.y - (this->width - 1) };
			}

			template <typename U = T>
			U sin()
			{
				return U(this->height) / this->hypotenuse<U>();
			}

			template <typename U = T>
			U cos()
			{
				return U(this->width) / this->hypotenuse<U>();
			}

			template <typename U = T>
			U tan()
			{
				return U(this->height) / U(this->width);
			}

			template <typename U = T>
			SSize<U> dot(const SSize<U>& b)
			{
				return { this->width * b.width + this->height + b.height };
			}

			template <typename U = T>
			U cosAngle(const SSize<U>& b)
			{
				return this->dot<U>(b) / (this->hypotenuse<U>() * b.hypotenuse<U>());
			}


		};

		template <typename T>
		static std::ostream& operator << (std::ostream& os, const SSize<T>& sz)
		{
			os << '(' << sz.width << ',' << sz.height << ')';
			return os;
		}

		template <typename T>
		static std::wostream& operator << (std::wostream& os, const SSize<T>& sz)
		{
			os << '(' << sz.width << ',' << sz.height << ')';
			return os;
		}

	}
}
