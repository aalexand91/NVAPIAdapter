#pragma once

#include "ApiExport.h"
#include <memory>
#include "PhysicalGpu.h"
#include <vector>

namespace NVAPIHooks
{
	class PhysicalGpuProvider
	{
	public:
		PhysicalGpuProvider() = default;
		virtual ~PhysicalGpuProvider() = default;
		PhysicalGpuProvider(const PhysicalGpuProvider&) = delete;
		PhysicalGpuProvider(PhysicalGpuProvider&&) = delete;
		PhysicalGpuProvider& operator = (const PhysicalGpuProvider&) = delete;
		PhysicalGpuProvider& operator = (PhysicalGpuProvider&&) = delete;

		/// <summary>
		/// Initializes the API interacting with the physical GPUs. Must be called before invoking other API functions calls.
		/// </summary>
		HOOKS_API void Initialize();

		/// <summary>Unloads the API interacting with the physical GPUs.</summary>
		HOOKS_API void Unload();

		/// <returns>The number of GPUs detected by the API.</returns>
		HOOKS_API unsigned int GetNumberOfGpus();

	private:
		bool m_apiInitialized{ false };
		std::unique_ptr<NvPhysicalGpuHandle> m_physicalGpuHandles;
		unsigned long m_numberOfGpus{ 0ul };

		void GetNvPhysicalGpuHandles();
	};
}