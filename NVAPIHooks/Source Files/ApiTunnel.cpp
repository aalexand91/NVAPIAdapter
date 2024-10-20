// Copyright 2024 Anthony Alexander

#include <pch.h>
#include <ApiTunnel.h>

namespace NVAPIHooks
{
	namespace ApiTunnel
	{
		NvAPI_Status InitializeApi()
		{
			return NvAPI_Initialize();
		}

		NvAPI_Status GetApiErrorMessage(const NvAPI_Status currentStatus, char* message)
		{
			return NvAPI_GetErrorMessage(currentStatus, message);
		}

		NvAPI_Status UnloadApi()
		{
			return NvAPI_Unload();
		}

		NvAPI_Status GetGpuCoreCount(NvPhysicalGpuHandle gpuHandle, unsigned long* coreCount)
		{
			return NvAPI_GPU_GetGpuCoreCount(gpuHandle, coreCount);
		}
	}
}