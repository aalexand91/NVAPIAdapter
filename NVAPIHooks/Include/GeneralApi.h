#pragma once

#include "ApiExport.h"

namespace NVAPIHooks
{
	namespace GeneralApi
	{
		/// <summary>Initializes the NVAPI library.</summary>
		HOOKS_API void Initialize();

		/// <summary>Decrements the ref-counter until it reaches zero and then unloads the NVAPI library.</summary>
		HOOKS_API void Unload();
	}
}