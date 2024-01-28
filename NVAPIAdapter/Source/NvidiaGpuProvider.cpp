#include <pch.h>

#include <NvidiaGpuProvider.h>

using namespace System;
using namespace System::Collections::Generic;

namespace NVAPIAdapter
{
	void NvidiaGpuProvider::Initialize()
	{
		if (m_initialized) return;
		InitializeApi();
		m_initialized = true;
	}

	void NvidiaGpuProvider::Unload()
	{
		if (!m_initialized) return;
		UnloadApi();
		m_initialized = false;
	}

	void NvidiaGpuProvider::AssertApiInitialized()
	{
		if (m_initialized) return;
		throw gcnew InvalidOperationException(ApiNotInitializedMessage);
	}

	int NvidiaGpuProvider::GetNumberOfGpus()
	{
		AssertApiInitialized();
		return m_physicalGpuProvider->GetNumberOfGpus();
	}

	INvidiaGpu^ NvidiaGpuProvider::GetGpuByIndex(const int index)
	{
		AssertApiInitialized();
		const int maxIndex = GetNumberOfGpus() - 1;
		if (index < 0 || index > maxIndex) 
		{
			String^ message = "Index value of " + index.ToString() + " is invalid. " 
				+ "Acceptable range is 0 - " + maxIndex.ToString() + ".";
			throw gcnew ArgumentException(message);
		}
		auto physicalGpu = m_physicalGpuProvider->GetGpuByIndex(index);
		return CreateNvidiaGpu(physicalGpu);
	}

	IEnumerable<INvidiaGpu^>^ NvidiaGpuProvider::GetAllGpus()
	{
		List<INvidiaGpu^>^ gpus = gcnew List<INvidiaGpu^>;
		const int numberOfGpus = GetNumberOfGpus();
		for (int index = 0; index < numberOfGpus; index++)
		{
			auto gpu = GetGpuByIndex(index);
			gpus->Add(gpu);
		}
		return gpus;
	}

	INvidiaGpu^ NvidiaGpuProvider::GetGpuByName(String^ name)
	{
		AssertApiInitialized();
		for each(INvidiaGpu^ gpu in GetAllGpus())
		{
			if (gpu->GetName() == name) return gpu;
		}
		String^ message = "No GPUs found with the name " + name + ".";
		throw gcnew ArgumentException(message);
	}
}