#include "pch.h"

#include <PhysicalGpuProviderAdapter.h>

namespace NVAPIAdapter
{
	RealPhysicalGpuProvider::~RealPhysicalGpuProvider()
	{
		delete m_physicalGpuProvider;
		m_physicalGpuProvider = nullptr;
	}

	int RealPhysicalGpuProvider::GetNumberOfGpus()
	{
		return m_physicalGpuProvider->GetNumberOfGpus();
	}

	IPhysicalGpuAdapter^ RealPhysicalGpuProvider::GetGpuByIndex(const int index)
	{
		auto physicalGpu = m_physicalGpuProvider->GetGpuByIndex(index);
		return gcnew RealPhysicalGpu(physicalGpu);
	}
}