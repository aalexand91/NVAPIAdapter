#include <pch.h>

#include <NvidiaGraphicsCardFinder.h>
#include <string>

namespace GraphicsCards 
{
	std::vector<IGraphicsCard*> NvidiaGraphicsCardFinder::GetAllGraphicsCards() 
	{
		auto status = NvAPI_Initialize();
		if (status != NVAPI_OK) 
		{
			const std::string message = 
		}
	}
}