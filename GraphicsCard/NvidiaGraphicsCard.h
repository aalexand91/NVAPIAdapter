#pragma once

#include <IGraphicsCard.h>

namespace GraphicsCards
{
	// TODO: Implement.
	class NvidiaGraphicsCard : public IGraphicsCard
	{
	public:
		char* GetFullName() override { return ""; }
	};
}
