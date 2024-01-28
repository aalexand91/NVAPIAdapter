#pragma once

#include <PhysicalGpuAdapter.h>
#include <PhysicalGpuProvider.h>

namespace NVAPIAdapter
{
	/// <summary>
	/// Test adapter for the native PhysicalGpuProvider class that can be mocked by unit tests.
	/// </summary>
	interface class IPhysicalGpuProviderAdapter
	{
	public:
		int GetNumberOfGpus();
		IPhysicalGpuAdapter^ GetGpuByIndex(const int index);
	};

	ref class RealPhysicalGpuProvider : IPhysicalGpuProviderAdapter
	{
	public:

		/// <returns>A new, real IPhysicalGpuProviderAdapter instance that unit tests can mock.</returns>
		static IPhysicalGpuProviderAdapter^ CreateInstance() { return gcnew RealPhysicalGpuProvider(); }

		RealPhysicalGpuProvider() { m_physicalGpuProvider = new NVAPIHooks::PhysicalGpuProvider(); }
		~RealPhysicalGpuProvider();

		virtual int GetNumberOfGpus();
		virtual IPhysicalGpuAdapter^ GetGpuByIndex(const int index);

	private:
		NVAPIHooks::IPhysicalGpuProvider* m_physicalGpuProvider;
	};
}