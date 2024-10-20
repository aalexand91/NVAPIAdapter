// Copyright 2024 Anthony Alexander

#include <pch.h>

#include <ApiError.h>
#include <ApiTunnel.h>
#include <GeneralApi.h>
#include <PhysicalGpu.h>

namespace NVAPIHooks
{
	namespace GeneralApi
	{
		void Initialize()
		{
			auto status = ApiTunnel::InitializeApi();
			if (status == NvAPI_Status::NVAPI_OK) return;
			throw ApiError("Failed to initialize NVAPI library.", status);
		}

		void Unload()
		{
			auto status = ApiTunnel::UnloadApi();
			if (status == NvAPI_Status::NVAPI_OK) return;
			throw ApiError("Failed to unload NVAPI library.", status);
		}

		std::vector<std::unique_ptr<IPhysicalGpu>> GetAllPhysicalGpus()
		{
			NvPhysicalGpuHandle detectedHandles[NVAPI_MAX_PHYSICAL_GPUS];
			unsigned long totalGpuCount = 0ul;
			auto status = ApiTunnel::GetPhysicalGpuHandles(detectedHandles, &totalGpuCount);
			if (status != NvAPI_Status::NVAPI_OK)
			{
				throw ApiError("Failed to detect physical GPUs.", status);
			}

			std::vector<std::unique_ptr<IPhysicalGpu>> physicalGpus;
			for (unsigned long handleNumber = 0ul; handleNumber < totalGpuCount; handleNumber++)
			{
				physicalGpus.push_back(std::make_unique<PhysicalGpu>(detectedHandles[handleNumber]));
			}
			return physicalGpus;
		}
	}
}