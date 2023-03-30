#pragma once
namespace ipgdlib
{
	namespace util
	{
		enum class eCollectionKind { Static, Dynamic };

		struct ICollectionKind
		{
			~ICollectionKind() {};

			virtual eCollectionKind getCollectionKind() const = 0;

		};

	}
}
