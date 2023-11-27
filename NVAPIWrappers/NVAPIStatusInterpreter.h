#pragma once

#include "Export.h"
#include <nvapi.h>
#include <string>

namespace NVAPIWrappers
{
	namespace NVAPIStatusInterpreter
	{
		/// <returns>
		/// A more detailed message about the current status of the NVAPI library.
		/// Returns a general message if the status is unhandled by this function.
		/// </returns>
		ADAPTER_API const std::string GetStatusMessage(NvAPI_Status status);
	}
}