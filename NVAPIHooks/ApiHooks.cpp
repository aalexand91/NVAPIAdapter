#include "pch.h"

#include "ApiHooks.h"

namespace NVAPIHooks
{
	NvAPI_Status GetErrorMessage(const NvAPI_Status apiStatus, char* message)
	{
		return NvAPI_GetErrorMessage(apiStatus, message);
	}

	NvAPI_Status GetName(NvPhysicalGpuHandle gpuHandle, char* buffer)
	{
		return NvAPI_GPU_GetFullName(gpuHandle, buffer);
	}
}