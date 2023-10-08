#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace GraphicsCards
{
	namespace NvidiaStatusInterpreter 
	{
		GRAPHICS_CARD_API std::string GetStatusMessage(NvAPI_Status status);
	}
}