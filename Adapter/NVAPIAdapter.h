#pragma once

#include "Export.h"
#include <nvapi.h>

namespace AdapterUnitTest 
{
	class NVAPIAdapterTester;
}

namespace Adapter
{
	class NVAPIAdapter
	{
		friend class AdapterUnitTest::NVAPIAdapterTester;

	public:
		NVAPIAdapter(NvPhysicalGpuHandle physicalHander) : m_physicalHandler(physicalHander) {}
		~NVAPIAdapter() = default;

		NVAPIAdapter(const NVAPIAdapter&) = delete;
		NVAPIAdapter(NVAPIAdapter&&) = delete;
		NVAPIAdapter& operator = (const NVAPIAdapter&) = delete;
		NVAPIAdapter& operator = (NVAPIAdapter&&) = delete;

		/// <summary>Initializes the Nvidia graphics card API library.</summary>
		ADAPTER_API void Initialize();

		/// <returns>The full name of the graphics card.</returns>
		/// <example>Quadro FX 1400.</example>
		ADAPTER_API std::string GetName();

		/// <returns>The type of GPU installed (integrated, discrete, or unknown).</returns>
		ADAPTER_API std::string GetGpuType();

	private:

		/// <summary>
		/// The distinct GPU handler from the NVAPI library that handles interfacing with the specific graphics card.
		/// </summary>
		NvPhysicalGpuHandle m_physicalHandler;

		bool m_apiInitialized{ false };

		void AssertApiInitialized();
	};
}
