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
			{NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_DESKTOP, "Desktop"},
		};

		NV_SYSTEM_TYPE systemType = NV_SYSTEM_TYPE::NV_SYSTEM_TYPE_UNKNOWN;
		auto status = ApiTunnel::GetSystemType(m_physicalGpuHandle, &systemType);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to get GPU system type.", status);
		auto match = map.find(systemType);
		return match == map.end() ? "Unknown" : match->second;
	}

	std::string PhysicalGpu::GetGpuType()
	{
		static const std::unordered_map<NV_GPU_TYPE, std::string> map =
		{
			{NV_GPU_TYPE::NV_SYSTEM_TYPE_IGPU, "Integrated"},
			{NV_GPU_TYPE::NV_SYSTEM_TYPE_DGPU, "Discrete"},
		};

		NV_GPU_TYPE gpuType = NV_SYSTEM_TYPE_GPU_UNKNOWN;
		auto status = ApiTunnel::GetGpuType(m_physicalGpuHandle, &gpuType);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Gailed to get GPU type.", status);
		auto match = map.find(gpuType);
		return match == map.end() ? "Unknown" : match->second;
	}
}