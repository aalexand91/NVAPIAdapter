#include "pch.h"

#include <ApiTunnel.h>
#include "CppUnitTest.h"
#include <hippomocks.h>
#include <StatusInterpreter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(StatusInterpreterTester)
		{
		public:
			TEST_METHOD(GetErrorMessage_OnSuccess_ReturnsErrorMessage)
			{
				// Arrange
				const std::string expected = "Fake API not initialized message.";
				MockRepository mocks;
				mocks.OnCallFunc(ApiTunnel::GetErrorMessage).With(m_fakeStatus, _)
					.Do([&](const NvAPI_Status, char* message) -> NvAPI_Status
						{
							const unsigned bufferSize = 256u;	// Set to the highest number of ASCII characters to ensure adequate buffer size.
							strncpy_s(message, bufferSize, expected.c_str(), bufferSize);
							return NvAPI_Status::NVAPI_OK;
						});

				// Act
				const auto actual = StatusInterpreter::GetErrorMessage(m_fakeStatus);

				// Assert
				Assert::AreEqual(expected, actual);
			}

			TEST_METHOD(GetErrorMessage_OnFailure_ReturnsFailedMessage)
			{
				// Arrange
				const std::string expected = "ERROR: Failed to get API error message for status of " + std::to_string(static_cast<unsigned>(m_fakeStatus));
				MockRepository mocks;
				mocks.OnCallFunc(ApiTunnel::GetErrorMessage).With(m_fakeStatus, _).Return(NvAPI_Status::NVAPI_ERROR);

				// Act
				const auto actual = StatusInterpreter::GetErrorMessage(m_fakeStatus);

				// Assert
				Assert::AreEqual(expected, actual);
			}

		private:
			const NvAPI_Status m_fakeStatus = NvAPI_Status::NVAPI_API_NOT_INITIALIZED;
		};
	}
}
