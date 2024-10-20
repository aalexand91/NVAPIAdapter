// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>
#include <IPhysicalGpu.h>
#include <nvapi.h>

namespace NVAPIHooks
{
	class PhysicalGpu : public IPhysicalGpu
	{
	public:
		/// <summary>Interfaces with the specific GPU with the given physical GPU handle.</summary>
		PhysicalGpu(NvPhysicalGpuHandle physicalGpuHandle) : m_physicalGpuHandle(physicalGpuHandle) {}

		/// <summary>Resets the physical GPU handle so that it cannot be used after destruction.</summary>
		virtual ~PhysicalGpu() { m_physicalGpuHandle = NVAPI_DEFAULT_HANDLE; }

		/// <returns>An instance unit tests can fake.</returns>
		HOOKS_API static IPhysicalGpu* CreateInstance(NvPhysicalGpuHandle phsyicalGpuHandle);

		HOOKS_API unsigned long GetCoreCount() override;

	private:
		NvPhysicalGpuHandle m_physicalGpuHandle{ NVAPI_DEFAULT_HANDLE };
	};
}
