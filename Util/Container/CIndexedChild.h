#pragma once

namespace ipgdlib
{
	namespace util
	{

		namespace container
		{

			class CIndexedChild
			{

			public:

				class CIndexedChildMutator
				{
					protected:
						void setChildIndex(CIndexedChild & child,size_t childIndex) const
						{
							child.m_ChildIndex = childIndex;
						}
				};

				CIndexedChild() :
					m_ChildIndex(0)
				{
				}

				size_t getChildIndex() const
				{
					return this->m_ChildIndex;
				}

			private:
				size_t m_ChildIndex;

			};

		}

	}
}