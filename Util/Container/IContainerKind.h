#pragma once
namespace ipgdlib
{
	namespace container
	{
		enum class eContainerKind { Static, Dynamic };

		struct IContainerKind
		{

			~IContainerKind() {};
			virtual eContainerKind getContainerKind() const = 0;

		};

	}
}
