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

		NvAPI_Status GetPhysicalGpuHandles(NvPhysicalGpuHandle* gpuHandles, unsigned long* totalGpuCount)
		{
			return NvAPI_EnumPhysicalGPUs(gpuHandles, totalGpuCount);
		}

		NvAPI_Status GetFullName(NvPhysicalGpuHandle gpuHandle, char* name)
		{
			return NvAPI_GPU_GetFullName(gpuHandle, name);
		}

		NvAPI_Status GetBusType(NvPhysicalGpuHandle gpuHandle, NV_GPU_BUS_TYPE* busType)
		{
			return NvAPI_GPU_GetBusType(gpuHandle, busType);
		}
	}
}