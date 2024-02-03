#include "pch.h"

#include "ApiError.h"
#include "ApiTunnel.h"
#include "PhysicalGpuProvider.h"

namespace NVAPIHooks
{
	PhysicalGpuProvider::~PhysicalGpuProvider()
	{
		if (m_numberOfGpus == ms_defaultNumberOfGpus) return;
		m_physicalGpuHandles.clear();
		m_numberOfGpus = ms_defaultNumberOfGpus;
	}

	int PhysicalGpuProvider::GetNumberOfGpus()
	{
		GetAllPhysicalGpuHandles();
		return m_numberOfGpus;
	}

	IPhysicalGpu* PhysicalGpuProvider::GetGpuByIndex(const int index)
	{
		GetAllPhysicalGpuHandles();
		return RealGetPhysicalGpu(m_physicalGpuHandles[index]);
	}

	void PhysicalGpuProvider::GetAllPhysicalGpuHandles()
	{
		if (m_numberOfGpus != ms_defaultNumberOfGpus) return;
		unsigned long numberOfGpusDetected = 0ul;
		NvPhysicalGpuHandle physicalGpuHandles[NVAPI_MAX_PHYSICAL_GPUS];
		auto status = ApiTunnel::GetPhysicalGpuHandles(physicalGpuHandles, &numberOfGpusDetected);
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Faild to detect physical GPUs.", status);
		m_numberOfGpus = static_cast<int>(numberOfGpusDetected);
		for (int handlerIndex = 0; handlerIndex < m_numberOfGpus; handlerIndex++)
		{
			m_physicalGpuHandles.push_back(physicalGpuHandles[handlerIndex]);
		}
	}
}