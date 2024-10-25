// Copyright 2024 Anthony Alexander

#pragma once

#include <GeneralApi.h>

using namespace System;

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
#pragma endregion

	public:
		/// <summary>Initializes the NVAPI library. Must be called first before any other functions.</summary>
		static void Initialize();

		/// <summary>Unloads the NVAPI library.</summary>
		static void Unload();
	};
}
