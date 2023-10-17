#pragma once

#include <nvapi.h>
#include <string>

namespace GraphicsCards
{
	/// <summary>
	/// Represents a general error that has occurred with the NVAPI library but can be caught as an exception.
	/// </summary>
	struct NvApiError
	{
		const std::string m_message{ nullptr };

		NvApiError() = delete;
		NvApiError(const char* message) : m_message(std::string(message)) { }
		NvApiError(std::string message) : m_message(message) { }
	};
}