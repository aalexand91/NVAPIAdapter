#include "pch.h"

#include "ApiHooks.h"
#include "StatusInterpreter.h"

namespace NVAPIHooks
{
	std::string StatusInterpreter::GetErrorMessage(NvAPI_Status apiStatus)
	{
		char message[256] = "\0";
		auto status = NVAPIHooks::GetErrorMessage(apiStatus, message);
		return status == NvAPI_Status::NVAPI_OK
			? std::string(message)
			: "ERROR: Failed to get API error message for status of " + std::to_string(static_cast<unsigned>(apiStatus));
	}
}