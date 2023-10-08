#pragma once

#include <IGraphicsCardFinder.h>
#include <memory>
#include <nvapi.h>

namespace GraphicsCards 
{
	/// <summary>
	/// Finds any physical Nvidia graphics card installed in the system.
	/// </summary>
	class NvidiaGraphicsCardFinder : public IGraphicsCardFinder
	{
	public:
		std::vector<IGraphicsCard*> GetAllGraphicsCards() override;
	};
}