#pragma once
namespace ipgdlib
{
	namespace util
	{
		enum class eVectorKind {Static,Dynamic};

		template <typename TChildType>
		class IVector
		{
			public:
				~IVector() {};

				virtual eVectorKind getVectorKind() const = 0;

				virtual size_t getChildCount() const = 0;
				virtual const TChildType& getChild(size_t index) const = 0;

			protected:
				virtual TChildType& getChildRef() = 0;
		};

	}
}
