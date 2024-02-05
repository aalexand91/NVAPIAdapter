#pragma once

#include "GpuSystemType.h"
#include "GpuType.h"
#include "PciIdentifier.h"
#include "PhysicalGpuAdapter.h"

namespace NVAPIAdapter
{
	/// <summary>Interfaces with the Nvidia GPU.</summary>
	public interface class INvidiaGpu 
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();

		/// <returns>The type of system the GPU is installed in.</returns>
		GpuSystemType GetSystemType();

		/// <returns>The type of GPU (as integrated, discrete, or unknown).</returns>
		GpuType GetGpuType();

		/// <returns>The PCI identifiers associated with the GPU.</returns>
		PciIdentifier^ GetPciIdentifiers();

		/// <returns>The bus ID associated with the GPU.</returns>
		unsigned long GetBusId();

		/// <returns>
		/// The video BIOS version in the form of xx.xx.xx.xx.yy where 
		/// xx.xx.xx.xx is the major.minor.maintenance.build number and yy is the manufacturer's version number.
		/// </returns>
		System::String^ GetVideoBiosVersion();

		/// <returns>The physical framebuffer size in KB. Excludes any RAM dedicated to the GPU.</returns>
		unsigned long GetPhysicalFrameBufferSizeInKb();

		/// <returns>The virtual framebuffer size in KB. Includes both physical and any RAM dedicated to the GPU.</returns>
		unsigned long GetVirtualFrameBufferSizeInKb();

		/// <returns>The number of cores defined for the GPU. Returns zero if no cores are defined for the GPU architecture.</returns>
		unsigned long GetCoreCount();
	};

	ref class NvidiaGpu sealed : INvidiaGpu
	{
	public:
		static INvidiaGpu^ CreateInstance(IPhysicalGpuAdapter^ physicalGpu) { return gcnew NvidiaGpu(physicalGpu); }

		virtual System::String^ GetName();
		virtual GpuSystemType GetSystemType();
		virtual GpuType GetGpuType();
		virtual PciIdentifier^ GetPciIdentifiers();
		virtual unsigned long GetBusId();
		virtual System::String^ GetVideoBiosVersion();
		virtual unsigned long GetPhysicalFrameBufferSizeInKb();
		virtual unsigned long GetVirtualFrameBufferSizeInKb();
		virtual unsigned long GetCoreCount();

	internal:
		NvidiaGpu(IPhysicalGpuAdapter^ physicalGpu) : m_physicalGpu(physicalGpu) {}

	private:
		IPhysicalGpuAdapter^ m_physicalGpu;
	};
}