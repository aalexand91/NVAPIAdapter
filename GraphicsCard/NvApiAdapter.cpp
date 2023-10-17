#include "pch.h"
#include "NvApiAdapter.h"

namespace GraphicsCards
{
	NvAPI_Status NvApiAdapter::Initialize()
	{
		return NvAPI_Initialize();
	}

	NvAPI_Status NvApiAdapter::Unload()
	{
		return NvAPI_Unload();
	}

	NvAPI_Status NvApiAdapter::GetFullName(const NvPhysicalGpuHandle physicalHandler, char* name)
	{
		return NvAPI_GPU_GetFullName(physicalHandler, name);
	}

	NvAPI_Status NvApiAdapter::GetGpuType(const NvPhysicalGpuHandle physicalHandler, NV_GPU_TYPE* gpuType)
	{
		return NvAPI_GPU_GetGPUType(physicalHandler, gpuType);
	}
}