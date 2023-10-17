#include <pch.h>

#include "NvApiStatusInterpreter.h"

namespace GraphicsCards 
{
	// TODO: Add more detailed message as more of project is implemented.

	const char* NvApiStatusInterpreter::GetStatusMessage(const NvAPI_Status status) 
	{
		switch (status) 
		{
		case (NvAPI_Status::NVAPI_API_NOT_INITIALIZED):
			return "API needs to be initialized before being used.";
		case (NvAPI_Status::NVAPI_LIBRARY_NOT_FOUND): 
			return "Support library for Nvidia graphics card failed to load.";
		case (NvAPI_Status::NVAPI_INVALID_ARGUMENT):
			return "Argument provided to API is invalid.";
		case (NvAPI_Status::NVAPI_NVIDIA_DEVICE_NOT_FOUND):
			return "Nvidia GPU not found. Verify compatible device connection.";
		default: 
			return "An error occurred with the Nvidia API. See stack trace for more info.";
		}
	}
}