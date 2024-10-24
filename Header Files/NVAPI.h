// Copyright 2024 Anthony Alexander

#pragma once

#include <GeneralApi.h>

using namespace System;

namespace NVAPIAdapter 
{
	public ref class NVAPI
	{
	internal:
		delegate void InitializeApiFunc();
		static InitializeApiFunc^ InitializeApi = gcnew InitializeApiFunc(NVAPIHooks::GeneralApi::Initialize);

	public:
		/// <summary>Initializes the NVAPI library.</summary>
		static void Initialize();
	};
}
