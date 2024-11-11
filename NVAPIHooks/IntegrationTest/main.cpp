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

#include <GeneralApi.h>
#include <iostream>

using namespace NVAPIHooks;

/// <summary>
/// Simple integration test that just prints the first GPU properties detected by the NVAPIHooks library.
/// Ensures no issues between the wrapper functions from NVAPIHooks and the NVAPI library.
/// </summary>
int main()
{
    std::cout << "Initializing API...\n";
    GeneralApi::Initialize();
    std::cout << "Obtaining first detected GPU...\n";
    const auto physicalGpu = GeneralApi::GetAllPhysicalGpus().front();
    std::cout << "Printing various GPU information...\n";
    std::cout << "Name: " << physicalGpu->GetFullName() << std::endl;
    std::cout << "Core count: " << physicalGpu->GetCoreCount() << std::endl;
    std::cout << "Bus type: " << physicalGpu->GetBusType() << std::endl;
    std::cout << "System type: " << physicalGpu->GetSystemType() << std::endl;
    std::cout << "PCI internal ID: " << physicalGpu->GetPciInternalId() << std::endl;
    std::cout << "PCI external ID: " << physicalGpu->GetPciExternalId() << std::endl;
    std::cout << "PCI revision ID: " << physicalGpu->GetPciRevisionId() << std::endl;
    std::cout << "PCI subsystem ID: " << physicalGpu->GetPciSubsystemId() << std::endl;
    std::cout << "\n";
    std::cout << "Unloading API...\n";
    GeneralApi::Unload();

    delete physicalGpu;
    std::cout << "Successfully integrated NVAPIHooks library!";
}