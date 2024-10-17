// Copyright 2024 Anthony Alexander

#pragma once

#include <Export.h>
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	/// <summary>Container for the NVAPI library error.</summary>
	struct ApiError
	{
		const char* m_context{ nullptr };
		const NvAPI_Status m_apiStatusCode{ NvAPI_Status::NVAPI_OK };

		/// <summary>
		/// Prevents callers from initializing an instance without setting member variables.
		/// </summary>
		ApiError() = delete;

		ApiError(const char* context, const NvAPI_Status apiStatusCode)
			: m_context(context), m_apiStatusCode(apiStatusCode) {}

		/// <returns>An error message containing the context of the error and the exact NVAPI error.</returns>
		HOOKS_API std::string GetErrorMessage();
	};
}
