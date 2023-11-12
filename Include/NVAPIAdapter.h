#pragma once

#include <Export.h>
#include <nvapi.h>
#include <PciIdentifier.h>

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

		/// <summary>Initializes the NVAPI library.</summary>
		ADAPTER_API void Initialize();

		/// <summary>Unloads the NVAPI library. Typically called when the API is no longer being used.</summary>
		ADAPTER_API void Unload();

		/// <returns>The full name of the graphics card.</returns>
		/// <example>Quadro FX 1400.</example>
		ADAPTER_API std::string GetName();

		/// <returns>The type of GPU installed (integrated, discrete, or unknown).</returns>
		ADAPTER_API std::string GetGpuType();

		/// <returns>The PCI identifiers of the GPU.</returns>
		ADAPTER_API PciIdentifier GetPciIdentifiers();

		/// <returns>The GPU bus type.</returns>
		ADAPTER_API std::string GetBusType();

		/// <returns>The GPU bus ID.</returns>
		ADAPTER_API unsigned long GetBusId();

		/// <returns>
		/// The VBIOS version of the graphics card in the form of xx.xx.xx.xx.yy 
		/// where xx numbers represent the BIOS revision and yy is the original manufacturer's revision.
		/// </returns>
		ADAPTER_API std::string GetVbiosVersion();

		/// <returns>The GPU physical frame buffer size (excluding any allocated to RAM) in KB.</returns>
		ADAPTER_API unsigned long GetPhysicalFrameBufferSizeInKb();

		/// <returns>The total frame buffer size of both the physical and virtual memory allocated in KB.</returns>
		ADAPTER_API unsigned long GetVirtualFrameBufferSizeInKb();

	private:
		/// <summary>
		/// The distinct GPU handler from the NVAPI library that handles interfacing with the specific graphics card.
		/// </summary>
		NvPhysicalGpuHandle m_physicalHandler;

		bool m_apiInitialized{ false };

		/// <summary>Maximum number of characters in an ASCII string.</summary>
		static const unsigned ms_asciiBufferSize{ 256u };

		void AssertApiInitialized();

		/// <returns>The string equivalent of the reported GPU bus type.</returns>
		std::string GetGpuBusType(NV_GPU_BUS_TYPE busType);

		/// <returns>
		/// Both the physical and virtual frame buffer size in KB if includeVirtualSize is true. 
		/// Returns only the physical frame buffer size if includeVirtualSize is false.
		/// </returns>
		unsigned long GetFrameBufferSize(const bool includeVirtualSize);
	};
}
