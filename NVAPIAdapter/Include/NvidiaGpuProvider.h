#pragma once

#include <GeneralApi.h>
#include "NvidiaGpu.h"
#include "PhysicalGpuProviderAdapter.h"

namespace NVAPIAdapter
{
	/// <summary>Provides an interface to an Nvidia GPU detected in the system.</summary>
	public interface class INvidiaGpuProvider
	{
	public:

		/// <summary>Initializes the API for the provider.</summary>
		void Initialize();

		/// <summary>Decrements the reference counter for each provided GPU and then unloads the API.</summary>
		void Unload();

		/// <returns>The number of GPUs detected in the system.</returns>
		int GetNumberOfGpus();

		/// <summary>Provides an interface to an Nvidia GPU based on the NVAPI handler index.</summary>
		/// <returns>Interface to the Nvidia GPU.</returns>
		INvidiaGpu^ GetGpuByIndex(const int index);

		/// <summary>Detects all GPUs in the system and provides a collection of them.</summary>
		/// <returns>A collection of detected Nvidia GPUs.</returns>
		System::Collections::Generic::IEnumerable<INvidiaGpu^>^ GetAllGpus();

		/// <summary>Provides an interface to an Nvidia GPU based on the provided name.</summary>
		/// <returns>Interface to the Nvidia GPU.</returns>
		INvidiaGpu^ GetGpuByName(System::String^ name);
	};

	public ref class NvidiaGpuProvider : INvidiaGpuProvider
	{
	#pragma region Test Seams
	internal:

		delegate IPhysicalGpuProviderAdapter^ CreatePhysicalGpuProviderFunc();
		static CreatePhysicalGpuProviderFunc^ CreatePhysicalGpuProvider = gcnew CreatePhysicalGpuProviderFunc(RealPhysicalGpuProvider::CreateInstance);

		delegate void InitializeFunc();
		static InitializeFunc^ InitializeApi = gcnew InitializeFunc(NVAPIHooks::GeneralApi::Initialize);

		delegate void UnloadFunc();
		static UnloadFunc^ UnloadApi = gcnew UnloadFunc(NVAPIHooks::GeneralApi::Unload);

		delegate INvidiaGpu^ CreateNvidiaGpuFunc(IPhysicalGpuAdapter^ physicalGpu);
		static CreateNvidiaGpuFunc^ CreateNvidiaGpu = gcnew CreateNvidiaGpuFunc(NvidiaGpu::CreateInstance);

		static System::String^ ApiNotInitializedMessage = "API needs to be initialized before interfacing with GPU.";

	#pragma endregion

	public:
		NvidiaGpuProvider() { m_physicalGpuProvider = CreatePhysicalGpuProvider(); }

		/// <returns>Instance that unit tests can fake.</returns>
		static INvidiaGpuProvider^ CreateInstance() { return gcnew NvidiaGpuProvider(); }

		virtual void Initialize();
		virtual void Unload();
		virtual int GetNumberOfGpus();
		virtual INvidiaGpu^ GetGpuByIndex(const int index);
		virtual System::Collections::Generic::IEnumerable<INvidiaGpu^>^ GetAllGpus();
		virtual INvidiaGpu^ GetGpuByName(System::String^ name);

	private:
		bool m_initialized{ false };
		IPhysicalGpuProviderAdapter^ m_physicalGpuProvider;

		void AssertApiInitialized();
	};
}