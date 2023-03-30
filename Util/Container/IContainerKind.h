#pragma once
namespace ipgdlib
{
	namespace util
	{
		enum class eContainerKind { Static, Dynamic };

		struct IContainerKind
		{

			~IContainerKind() {};
			virtual eContainerKind getContainerKind() const = 0;

		};

	}
}
