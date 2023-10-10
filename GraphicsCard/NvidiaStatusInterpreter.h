#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace GraphicsCards
{
	namespace NvidiaStatusInterpreter 
	{
		/// <returns>
		/// A more detailed message about the status of the Nvidia GPU API.
		/// Returns a general message if the status is unhandled by this function.
		/// </returns>
		GRAPHICS_CARD_API std::string GetStatusMessage(NvAPI_Status status);
	}
}