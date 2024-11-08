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
// SOFTWARE.// Copyright 2024 Anthony Alexander

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
