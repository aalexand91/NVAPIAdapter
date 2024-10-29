// Copyright 2024 Anthony Alexander

#include <GeneralApi.h>
#include <iostream>

using namespace NVAPIHooks;

/// <summary>
/// Simple integration test that just prints the first GPU property detected by the NVAPIHooks library.
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
    std::cout << "\n";
    std::cout << "Unloading API...\n";
    GeneralApi::Unload();

    delete physicalGpu;
    std::cout << "Successfully integrated NVAPIHooks library!";
}