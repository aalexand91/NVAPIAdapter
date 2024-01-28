#include "pch.h"

#include "ApiTunnel.h"

namespace NVAPIHooks
{
	namespace ApiTunnel
	{
		NvAPI_Status GetErrorMessage(const NvAPI_Status apiStatus, char* message)
		{
			return NvAPI_GetErrorMessage(apiStatus, message);
		}

		NvAPI_Status GetName(NvPhysicalGpuHandle gpuHandle, char* buffer)
		{
			return NvAPI_GPU_GetFullName(gpuHandle, buffer);
		}

		NvAPI_Status InitializeApi()
		{
			return NvAPI_Initialize();
		}

		NvAPI_Status UnloadApi()
		{
			return NvAPI_Unload();
		}

		NvAPI_Status GetPhysicalGpuHandles(NvPhysicalGpuHandle* physicalGpuHandles, unsigned long* numberOfGpus)
		{
			return NvAPI_EnumPhysicalGPUs(physicalGpuHandles, numberOfGpus);
		}

		NvAPI_Status GetSystemType(NvPhysicalGpuHandle gpuHandle, NV_SYSTEM_TYPE* systemType)
		{
			return NvAPI_GPU_GetSystemType(gpuHandle, systemType);
		}
	}
}