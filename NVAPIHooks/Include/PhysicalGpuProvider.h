#pragma once

#include "ApiExport.h"
#include "PhysicalGpu.h"
#include <nvapi.h>
#include <vector>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		class PhysicalGpuProviderTester;
	}

	class IPhysicalGpuProvider
	{
	public:
		IPhysicalGpuProvider() = default;
		virtual ~IPhysicalGpuProvider() = default;
		IPhysicalGpuProvider(const IPhysicalGpuProvider&) = delete;
		IPhysicalGpuProvider(IPhysicalGpuProvider&&) = delete;
		IPhysicalGpuProvider& operator = (const IPhysicalGpuProvider&) = delete;
		IPhysicalGpuProvider& operator = (IPhysicalGpuProvider&&) = delete;

		/// <returns>The number of GPUs detected in the system.</returns>
		virtual int GetNumberOfGpus() = 0;

		/// <returns>An interface to the physical GPU based on the handler index.</returns>
		virtual std::shared_ptr<IPhysicalGpu> GetGpuByIndex(const int index) = 0;
	};

	class PhysicalGpuProvider : public IPhysicalGpuProvider
	{
		friend class UnitTest::PhysicalGpuProviderTester;
	public:
		PhysicalGpuProvider() = default;
		HOOKS_API virtual ~PhysicalGpuProvider();
		PhysicalGpuProvider(const PhysicalGpuProvider&) = delete;
		PhysicalGpuProvider(PhysicalGpuProvider&&) = delete;
		PhysicalGpuProvider& operator = (const PhysicalGpuProvider&) = delete;
		PhysicalGpuProvider& operator = (PhysicalGpuProvider&&) = delete;

		HOOKS_API int GetNumberOfGpus() override;
		HOOKS_API std::shared_ptr<IPhysicalGpu> GetGpuByIndex(const int index);

	private:
		/// <summary>Defaulted to -1 to indicate that the number of GPUs have not been detected.</summary>
		static const int ms_defaultNumberOfGpus = -1;

		int m_numberOfGpus{ ms_defaultNumberOfGpus };
		std::vector<NvPhysicalGpuHandle> m_physicalGpuHandles;

		void GetAllPhysicalGpuHandles();

		/// <summary>
		/// Creates a real shared pointer to the PhysicalGpu object.
		/// Static so that the unit tests can mock the object returned.
		/// </summary>
		/// <returns>An interface to the physical GPU.</returns>
		static std::shared_ptr<IPhysicalGpu> RealGetPhysicalGpu(NvPhysicalGpuHandle physicalHandle) { return std::make_shared<PhysicalGpu>(physicalHandle); }
	};
}
