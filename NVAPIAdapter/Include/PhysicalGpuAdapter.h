#pragma once

#include <PhysicalGpu.h>

namespace NVAPIAdapter
{
	/// <summary>Adapter for the native PhysicalGpu class that can be faked by unit tests.</summary>
	interface class IPhysicalGpuAdapter
	{
	public:
		/// <returns>The full name of the GPU.</returns>
		System::String^ GetName();

		/// <returns>The type of system the GPU is installed in.</returns>
		System::String^ GetSystemType();

		/// <returns>The type of GPU (as integrated, discrete, or unknown.</returns>
		System::String^ GetGpuType();
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

	private:
		NVAPIHooks::IPhysicalGpu* m_physicalGpu{ nullptr };
	};
}