#pragma once

#include "ApiExport.h"
#include <exception>
#include <nvapi.h>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		// Forward declarated so that unit tests can access private members.
		class ApiErrorTester;
	}

	/// <summary>
	/// Extends the standard exception class to inform the user of an error that occurred with the API.
	/// </summary>
	class ApiError : public std::exception
	{
		friend UnitTest::ApiErrorTester;

	public:
		HOOKS_API ApiError(const char* message, const NvAPI_Status apiStatus) : m_message(message), m_apiStatus(apiStatus) {}
		virtual ~ApiError() = default;

		const char* what() const noexcept override;

	private:
		const char* m_message{ nullptr };
		const NvAPI_Status m_apiStatus{ NvAPI_Status::NVAPI_ERROR };
	};
}