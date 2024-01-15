#include "pch.h"

#include "ApiError.h"
#include "ApiHooks.h"
#include "PhysicalGpuProvider.h"

namespace NVAPIHooks
{
	void PhysicalGpuProvider::Initialize()
	{
		if (m_apiInitialized) return;
		auto status = NVAPIHooks::InitializeApi();
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to initial API library.", status);
		m_apiInitialized = true;
	}

	void PhysicalGpuProvider::Unload()
	{
		if (!m_apiInitialized) return;
		auto status = NVAPIHooks::UnloadApi();
		if (status != NvAPI_Status::NVAPI_OK) throw ApiError("Failed to unload API library.", status);
		m_apiInitialized = false;
	}

	unsigned int PhysicalGpuProvider::GetNumberOfGpus()
	{
		if (!m_apiInitialized) throw std::runtime_error("API is not initialized.");
		GetNvPhysicalGpuHandles();
		return static_cast<unsigned int>(m_numberOfGpus);
	}

	void PhysicalGpuProvider::GetNvPhysicalGpuHandles()
	{
		if (m_physicalGpuHandles) return;
		auto status = NVAPIHooks::GetPhysicalGpuHandles(m_physicalGpuHandles, &m_numberOfGpus);
		if (status == NvAPI_Status::NVAPI_OK) return;
		throw ApiError("Failed to obtain physical GPU handlers.", status);
	}
}