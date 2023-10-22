#pragma once

#include <nvapi.h>
#include <string>

namespace Adapter
{
	/// <summary>
	/// Represents a general error that has occurred with the NVAPI library but can be caught as an exception.
	/// </summary>
	struct NVAPIError
	{
		const std::string m_message{ nullptr };

		NVAPIError() = delete;
		NVAPIError(const char* message) : m_message(std::string(message)) { }
		NVAPIError(std::string message) : m_message(message) { }
	};
}