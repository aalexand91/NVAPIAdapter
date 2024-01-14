#pragma once

#include "ApiExport.h"
#include <nvapi.h>
#include <string>

namespace NVAPIHooks
{
	namespace UnitTest
	{
		// Forward declarated so that unit tests can access private members.
		class StatusInterpreterTester;
	}

	class StatusInterpreter
	{
		friend UnitTest::StatusInterpreterTester;

	public:
		virtual ~StatusInterpreter() = default;
		StatusInterpreter(const StatusInterpreter&) = delete;
		StatusInterpreter(StatusInterpreter&&) = delete;
		StatusInterpreter& operator = (const StatusInterpreter) = delete;
		StatusInterpreter& operator = (StatusInterpreter&&) = delete;

		/// <summary>Determines the error that occured with the third party API.</summary>
		/// <param name="apiStatus">API status to determine error from.</param>
		/// <returns>A message that specifies the exact error that occurred with the API.</returns>
		HOOKS_API static std::string GetErrorMessage(NvAPI_Status apiStatus);

	private:
		StatusInterpreter() = default;
	};
}
