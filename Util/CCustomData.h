#pragma once

#include "iface/ICustomData.h"

namespace ipgdlib
{
	namespace util
	{

		template <typename T>
		class CCustomData :
			virtual public ICustomData
		{
		public:
			CCustomData() = default;

			CCustomData(const T& customData)
				: m_CustomData(customData)
			{
			}

			CCustomData(T&& customData)
				: m_CustomData(std::move(customData))
			{
			}

			bool hasCustomData() const override
			{
				return true;
			}

			const T& getCustomData() const
			{
				return this->m_CustomData;
			}

			virtual void setCustomData(const T& customData)
			{
				this->m_CustomData = customData;
			}

			virtual void setCustomData(T&& customData)
			{
				this->m_CustomData = std::move(customData);
			}

		protected:
			T& getCustomDataRef()
			{
				return this->m_CustomData;
			}

		private:
			T m_CustomData;
		};

		template <>
		class CCustomData<void> :
			virtual public ICustomData
		{

		public:
			CCustomData()
			{
			}

			bool hasCustomData() const override
			{
				return false;
			}

		};

	}
}

