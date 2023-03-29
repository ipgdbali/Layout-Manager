#pragma once
namespace ipgdlib
{
	namespace util
	{
		enum class eVectorKind { Static, Dynamic };

		struct IVectorBase
		{
			~IVectorBase() {};

			virtual eVectorKind getVectorKind() const = 0;
			virtual size_t getChildCount() const = 0;

		};

	}
}
