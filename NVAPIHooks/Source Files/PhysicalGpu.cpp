// Copyright 2024 Anthony Alexander

#include <pch.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <PhysicalGpu.h>

namespace NVAPIHooks
{
	unsigned long PhysicalGpu::GetCoreCount()
	{
		unsigned long coreCount = 0ul;
		auto status = ApiTunnel::GetGpuCoreCount(m_physicalGpuHandle, &coreCount);
		if (status == NvAPI_Status::NVAPI_OK) return coreCount;
		throw ApiError("Failed to get GPU core count.", status);
	}
}