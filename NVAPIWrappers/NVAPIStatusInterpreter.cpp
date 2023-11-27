#include "pch.h"

#include "NVAPIStatusInterpreter.h"
#include "NVAPITunnel.h"

namespace NVAPIWrappers
{
	const std::string NVAPIStatusInterpreter::GetStatusMessage(const NvAPI_Status status) 
	{
		char message[256] = "";
		const NvAPI_Status getMessageStatus = NVAPITunnel::GetStatusErrorMessage(status, message);
		const auto failedToGetStatusMessage = "Failed to get API status message for status code " + std::to_string(static_cast<int>(status)) + ".";
		return getMessageStatus == NVAPI_OK ? message: failedToGetStatusMessage;
	}
}