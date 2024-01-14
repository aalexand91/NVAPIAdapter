#pragma once

#include "ApiExport.h"
#include <nvapi.h>

namespace NVAPIHooks
{
	/// <summary>Determines the specific error that occurred with the API.</summary>
	/// <param name="apiStatus">Status of the last executed API function.</param>
	/// <param name="message">Caches the API error message.</param>
	/// <returns>The status of the API upon determining the last API error.</returns>
	HOOKS_API NvAPI_Status GetErrorMessage(const NvAPI_Status apiStatus, char* message);

	/// <summary>Determines the full name of the Nvidia GPU.</summary>
	/// <param name="gpuHandle">API handler interfacing with the physical GPU.</param>
	/// <param name="buffer">Caches the GPU name as an ASCII string.</param>
	/// <returns>The status of the API upon determining the name of the GPU.</returns>
	HOOKS_API NvAPI_Status GetName(NvPhysicalGpuHandle gpuHandle, char* buffer);
}