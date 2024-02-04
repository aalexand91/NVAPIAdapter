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

		NvAPI_Status GetGpuType(NvPhysicalGpuHandle gpuHandle, NV_GPU_TYPE* gpuType)
		{
			return NvAPI_GPU_GetGPUType(gpuHandle, gpuType);
		}

		NvAPI_Status GetPciIdentifiers(
			NvPhysicalGpuHandle gpuHandle,
			unsigned long* deviceId,
			unsigned long* subSystemId,
			unsigned long* revisionId,
			unsigned long* externalDeviceId)
		{
			return NvAPI_GPU_GetPCIIdentifiers(gpuHandle, deviceId, subSystemId, revisionId, externalDeviceId);
		}

		NvAPI_Status GetGpuBusId(NvPhysicalGpuHandle gpuHandle, unsigned long* busId)
		{
			return NvAPI_GPU_GetBusId(gpuHandle, busId);
		}

		NvAPI_Status GetVbiosVersion(NvPhysicalGpuHandle gpuHandle, char* biosVersion)
		{
			return NvAPI_GPU_GetVbiosVersionString(gpuHandle, biosVersion);
		}

		NvAPI_Status GetPhysicalFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* size)
		{
			return NvAPI_GPU_GetPhysicalFrameBufferSize(gpuHandle, size);
		}
		
		NvAPI_Status GetVirtualFrameBufferSize(NvPhysicalGpuHandle gpuHandle, unsigned long* size)
		{
			return NvAPI_GPU_GetVirtualFrameBufferSize(gpuHandle, size);
		}
	}
}