#include "pch.h"
#include "NVAPITunnel.h"

namespace Adapter
{
	NvAPI_Status NVAPITunnel::Initialize()
	{
		return NvAPI_Initialize();
	}

	NvAPI_Status NVAPITunnel::Unload()
	{
		return NvAPI_Unload();
	}

	NvAPI_Status NVAPITunnel::GetFullName(const NvPhysicalGpuHandle physicalHandler, char* name)
	{
		return NvAPI_GPU_GetFullName(physicalHandler, name);
	}

	NvAPI_Status NVAPITunnel::GetGpuType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_TYPE* gpuType)
	{
		return NvAPI_GPU_GetGPUType(physicalHandler, gpuType);
	}
}