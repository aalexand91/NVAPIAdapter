// Copyright 2024 Anthony Alexander

#pragma once

#include <GeneralApi.h>
#include <NvidiaGpu.h>
#include <PhysicalGpuAdapter.h>

namespace NVAPIAdapter 
{
	public ref class NVAPI
	{
#pragma region Test Seams
	internal:
		delegate void InitializeApiFunc();
		static InitializeApiFunc^ InitializeApi = gcnew InitializeApiFunc(NVAPIHooks::GeneralApi::Initialize);

		delegate void UnloadApiFunc();
		static UnloadApiFunc^ UnloadApi = gcnew UnloadApiFunc(NVAPIHooks::GeneralApi::Unload);

		delegate System::Collections::Generic::IEnumerable<IPhysicalGpuAdapter^>^ GetAllPhysicalGpusFunc();
		static GetAllPhysicalGpusFunc^ GetAllPhysicalGpus = gcnew GetAllPhysicalGpusFunc(RealGetAllPhysicalGpus);

		delegate INvidiaGpu^ CreateNvidiaGpuFunc(IPhysicalGpuAdapter^ adpater);
		static CreateNvidiaGpuFunc^ CreateNvidiaGpu = gcnew CreateNvidiaGpuFunc(NvidiaGpu::CreateInstance);
#pragma endregion

	public:
		/// <summary>Initializes the NVAPI library. Must be called first before any other functions.</summary>
		static void Initialize();

		/// <summary>Unloads the NVAPI library.</summary>
		static void Unload();

		/// <returns>A collection of all GPUs detected by the NVAPI library.</returns>
		static System::Collections::Generic::IEnumerable<INvidiaGpu^>^ GetAllGpus();

	private:
		static System::Collections::Generic::IEnumerable<IPhysicalGpuAdapter^>^ RealGetAllPhysicalGpus();
	};
}
