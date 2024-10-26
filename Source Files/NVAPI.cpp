// Copyright 2024 Anthony Alexander

#include <NVAPI.h>

using namespace NVAPIHooks;
using namespace System::Collections::Generic;

namespace NVAPIAdapter
{
	void NVAPI::Initialize()
	{
		InitializeApi();
	}

	void NVAPI::Unload()
	{
		UnloadApi();
	}

	IEnumerable<INvidiaGpu^>^ NVAPI::GetAllGpus()
	{
		auto gpus = gcnew List<INvidiaGpu^>();
		for each (auto gpuAdapter in GetAllPhysicalGpus())
		{
			auto gpu = CreateNvidiaGpu(gpuAdapter);
			gpus->Add(gpu);
		}
		return gpus;
	}

	IEnumerable<IPhysicalGpuAdapter^>^ NVAPI::RealGetAllPhysicalGpus()
	{
		auto adapterCollection = gcnew List<IPhysicalGpuAdapter^>();
		auto physicalGpus = GeneralApi::GetAllPhysicalGpus();
		for (auto index = 0; index < physicalGpus.size(); index++)
		{
			auto adapter = gcnew PhysicalGpuAdapter(physicalGpus[index].get());
			adapterCollection->Add(adapter);
		}
		return adapterCollection;
	}
}
