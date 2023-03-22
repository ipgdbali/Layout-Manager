#pragma once

template <typename T>
class CCustomData {
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

		const T &getCustomData() const
		{
			return this->m_CustomData;
		}

		virtual void setCustomData(const T& customData)
		{
			this->m_CustomData = customData;
		}

		virtual void setCustomData(T && customData)
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
class CCustomData<void> 
{
};
