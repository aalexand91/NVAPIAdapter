#include "pch.h"

#include "ApiError.h"
#include "ApiTunnel.h"
#include "PhysicalGpu.h"
#include "StatusInterpreter.h"

namespace NVAPIHooks
{
	std::string PhysicalGpu::GetName()
	{
		char name[ms_asciiStringBufferSize] = "\0";
		auto status = ApiTunnel::GetName(m_physicalGpuHandle, name);
		if (status == NvAPI_Status::NVAPI_OK) return name;
		throw ApiError("Failed to get GPU name.", status);
	}

	std::string PhysicalGpu::GetSystemType()
	{
		static const std::unordered_map<NV_SYSTEM_TYPE, std::string> map =
		{
			{NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_LAPTOP, "Laptop"},
			{NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_DESKTOP, "Desktop"}
		};

		NV_SYSTEM_TYPE systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_UNKNOWN;
		auto status = ApiTunnel::GetSystemType(m_physicalGpuHandle, &systemType);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to get GPU system type.", status);
		auto match = map.find(systemType);
		return match == map.end() ? "Unknown" : match->second;
	}
}