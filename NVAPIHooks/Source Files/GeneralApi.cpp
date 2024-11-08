// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

		std::vector<IPhysicalGpu*> GetAllPhysicalGpus()
		{
			NvPhysicalGpuHandle detectedHandles[NVAPI_MAX_PHYSICAL_GPUS];
			unsigned long totalGpuCount = 0ul;
			auto status = ApiTunnel::GetPhysicalGpuHandles(detectedHandles, &totalGpuCount);
			if (status != NvAPI_Status::NVAPI_OK)
			{
				throw ApiError("Failed to detect physical GPUs.", status);
			}

			std::vector<IPhysicalGpu*> physicalGpus;
			for (unsigned long handleNumber = 0ul; handleNumber < totalGpuCount; handleNumber++)
			{
				auto physicalGpu = new PhysicalGpu(detectedHandles[handleNumber]);
				physicalGpus.push_back(physicalGpu);
			}
			return physicalGpus;
		}
	}
}