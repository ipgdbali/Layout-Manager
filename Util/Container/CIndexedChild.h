#pragma once

namespace ipgdlib
{
	namespace container
	{

		template <typename T>
		class CIndexedChild
		{

		public:

			class CIndexedChildMutable
			{
				public:
					CIndexedChildMutable(CIndexedChild<T> & ref) :
						m_IndexedChild(&ref)
					{
					}

					void setIndexedChild(CIndexedChild<T>& ref)
					{
						this->m_IndexedChild = &ref;
					}

					T getIndex() const
					{
						return this->m_IndexedChild->getIndex();
					}

					void setIndex(T index) consts
					{
						m_IndexedChild->setIndex(index);
					}

				private:
					CIndexedChild<T>* m_IndexedChild;
			};

			T getIndex() const
			{
				return this->m_Index;
			}
		

		protected:
			void setIndex(T index)
			{
				return this->m_Index = std::move(index);
			}

		private:
			T m_Index;
		};

	}
}