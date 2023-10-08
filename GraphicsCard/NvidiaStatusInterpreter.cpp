#include <pch.h>

#include <NvidiaStatusInterpreter.h>

namespace GraphicsCards 
{
	std::string NvidiaStatusInterpreter::GetStatusMessage(const NvAPI_Status status) 
	{
		switch (status) 
		{
			case (NvAPI_Status::NVAPI_LIBRARY_NOT_FOUND): 
				return "Support library for Nvidia graphics card failed to load.";
			default: 
				return "An error occurred with the Nvidia API library. See stack trace for more info.";
		}
	}
}