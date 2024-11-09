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

#include <pch.h>
#include <ApiTunnel.h>

namespace NVAPIHooks
{
	namespace ApiTunnel
	{
		NvAPI_Status InitializeApi()
		{
			return NvAPI_Initialize();
		}

		NvAPI_Status GetApiErrorMessage(const NvAPI_Status currentStatus, char* message)
		{
			return NvAPI_GetErrorMessage(currentStatus, message);
		}

		NvAPI_Status UnloadApi()
		{
			return NvAPI_Unload();
		}

		NvAPI_Status GetGpuCoreCount(NvPhysicalGpuHandle gpuHandle, unsigned long* coreCount)
		{
			return NvAPI_GPU_GetGpuCoreCount(gpuHandle, coreCount);
		}

		NvAPI_Status GetPhysicalGpuHandles(NvPhysicalGpuHandle* gpuHandles, unsigned long* totalGpuCount)
		{
			return NvAPI_EnumPhysicalGPUs(gpuHandles, totalGpuCount);
		}

		NvAPI_Status GetFullName(NvPhysicalGpuHandle gpuHandle, char* name)
		{
			return NvAPI_GPU_GetFullName(gpuHandle, name);
		}

		NvAPI_Status GetBusType(NvPhysicalGpuHandle gpuHandle, NV_GPU_BUS_TYPE* busType)
		{
			return NvAPI_GPU_GetBusType(gpuHandle, busType);
		}

		NvAPI_Status GetSystemType(NvPhysicalGpuHandle gpuHandle, NV_SYSTEM_TYPE* systemType)
		{
			return NvAPI_GPU_GetSystemType(gpuHandle, systemType);
		}
	}
}