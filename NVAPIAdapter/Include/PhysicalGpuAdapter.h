#pragma once

#include "PciIdentifier.h"
#include <PhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Adapter for the native PhysicalGpu class that can be faked by unit tests.</summary>
	interface class IPhysicalGpuAdapter
	{
	public:
		System::String^ GetName();
		System::String^ GetSystemType();
		System::String^ GetGpuType();
		PciIdentifier^ GetPciIdentifiers();
		unsigned long GetBusId();
		System::String^ GetVideoBiosVersion();
		unsigned long GetPhysicalFrameBufferSizeInKb();
		unsigned long GetVirtualFrameBufferSizeInKb();
	};

	ref class RealPhysicalGpu : IPhysicalGpuAdapter
	{
	public:
		static IPhysicalGpuAdapter^ CreateInstance(NVAPIHooks::IPhysicalGpu* physicalGpu) { return gcnew RealPhysicalGpu(physicalGpu); }
		RealPhysicalGpu(NVAPIHooks::IPhysicalGpu* physicalGpu) : m_physicalGpu(physicalGpu) {}
		~RealPhysicalGpu();

		virtual System::String^ GetName();
		virtual System::String^ GetSystemType();
		virtual System::String^ GetGpuType();
		virtual PciIdentifier^ GetPciIdentifiers();
		virtual unsigned long GetBusId();
		virtual System::String^ GetVideoBiosVersion();
		virtual unsigned long GetPhysicalFrameBufferSizeInKb();
		virtual unsigned long GetVirtualFrameBufferSizeInKb();

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu{ nullptr };
	};
}