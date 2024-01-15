#include "pch.h"

#include "ApiError.h"
#include "ApiHooks.h"
#include "PhysicalGpu.h"
#include "StatusInterpreter.h"

namespace NVAPIHooks
{
	std::shared_ptr<IPhysicalGpu> PhysicalGpu::CreateInstance(NvPhysicalGpuHandle physicalGpuHandle)
	{
		return std::make_shared<PhysicalGpu>(physicalGpuHandle);
	}

	std::string PhysicalGpu::GetName()
	{
		char name[ms_asciiStringBufferSize] = "\0";
		auto status = NVAPIHooks::GetName(m_physicalGpuHandle, name);
		if (status == NvAPI_Status::NVAPI_OK)
		{
			return std::string(name);
		}
		throw ApiError("Failed to get GPU name.", status);
	}
}