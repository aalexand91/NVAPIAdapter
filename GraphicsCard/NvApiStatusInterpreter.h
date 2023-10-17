#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace GraphicsCards
{
	namespace NvApiStatusInterpreter
	{
		/// <returns>
		/// A more detailed message about the current status of the NVAPI library.
		/// Returns a general message if the status is unhandled by this function.
		/// </returns>
		GRAPHICS_CARD_API const char* GetStatusMessage(NvAPI_Status status);
	}
}