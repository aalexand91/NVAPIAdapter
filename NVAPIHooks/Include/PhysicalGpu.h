#pragma once

#include "ApiExport.h"
#include "PciIdentifiers.h"

#include <memory>
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		// Forward declarated so that unit tests can access private members.
		class PhysicalGpuTester;
	}

	/// <summary>Provides an API to a physical GPU installed on the system.</summary>
	class IPhysicalGpu
	{
		friend UnitTest::PhysicalGpuTester;

	public:
		IPhysicalGpu() = default;
		virtual ~IPhysicalGpu() = default;
		IPhysicalGpu(const IPhysicalGpu&) = delete;
		IPhysicalGpu(IPhysicalGpu&&) = delete;
		IPhysicalGpu& operator = (const IPhysicalGpu&) = delete;
		IPhysicalGpu& operator = (IPhysicalGpu&&) = delete;

		/// <returns>The full name of the GPU.</returns>
		virtual std::string GetName() = 0;

		/// <returns>The type of system the GPU is installed in.</returns>
		virtual std::string GetSystemType() = 0;

		/// <returns>The type of GPU (integrated, discrete, or unknown).</returns>
		virtual std::string GetGpuType() = 0;

		/// <returns>The PCI identifiers associated with the GPU.</returns>
		virtual PciIdentifiers GetPciIdentifiers() = 0;

		/// <returns>The bus ID associated with the GPU.</returns>
		virtual unsigned long GetGpuBusId() = 0;

		/// <returns>
		/// The video BIOS version in the form of xx.xx.xx.xx.yy where 
		/// xx.xx.xx.xx is the major.minor.maintenance.build number and yy is the manufacturer's version number.
		/// </returns>
		virtual std::string GetVbiosVersion() = 0;

		/// <returns>The physical framebuffer size in KB, excluding any RAM dedicated to the GPU.</returns>
		virtual unsigned long GetPhysicalFrameBufferSize() = 0;

		/// <returns>The virtual framebuffer size in KB. Includes the physical framebuffer size and any RAM dedicated to the GPU.</returns>
		virtual unsigned long GetVirtualFrameBufferSize() = 0;
	};

	class PhysicalGpu : public IPhysicalGpu
	{
	public:
		PhysicalGpu(NvPhysicalGpuHandle physicalGpuHandle) : m_physicalGpuHandle(physicalGpuHandle) {}
		virtual ~PhysicalGpu() = default;
		PhysicalGpu(const PhysicalGpu&) = delete;
		PhysicalGpu(PhysicalGpu&&) = delete;
		PhysicalGpu& operator = (const PhysicalGpu&) = delete;
		PhysicalGpu& operator = (PhysicalGpu&&) = delete;

		HOOKS_API std::string GetName() override;
		HOOKS_API std::string GetSystemType() override;
		HOOKS_API std::string GetGpuType() override;
		HOOKS_API PciIdentifiers GetPciIdentifiers() override;
		HOOKS_API unsigned long GetGpuBusId() override;
		HOOKS_API std::string GetVbiosVersion() override;
		HOOKS_API unsigned long GetPhysicalFrameBufferSize() override;
		HOOKS_API unsigned long GetVirtualFrameBufferSize() override;

	private:
		static const unsigned ms_asciiStringBufferSize{ 256u };

		NvPhysicalGpuHandle m_physicalGpuHandle{ nullptr };
	};
}
