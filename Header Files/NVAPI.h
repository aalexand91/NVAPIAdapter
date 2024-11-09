// Copyright (c) 2024 Anthony Alexander

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
