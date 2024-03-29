#pragma once

#include "iface/ISizeable.h"

namespace ipgdlib
{

	namespace util
	{

		template <typename T>
		class CSizeable :
			virtual public ISizeable<const T&>
		{

		public:
			CSizeable(const T& size) :
				m_Size(size)
			{
			}

			CSizeable(T && size) :
				m_Size(std::move(size))
			{
			}

			const T& getSize() const override
			{
				return this->m_Size;
			}

			void setSize(const T& size) override
			{
				this->m_Size = size;
			}

		private:
			T m_Size;

		};

	}

}


