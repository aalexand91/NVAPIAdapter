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

	std::shared_ptr<IPhysicalGpu> PhysicalGpuProvider::GetGpuByIndex(const int index)
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
		for (const auto handle : physicalGpuHandles)
		{
			m_physicalGpuHandles.push_back(handle);
		}
		m_numberOfGpus = static_cast<int>(numberOfGpusDetected);
	}
}