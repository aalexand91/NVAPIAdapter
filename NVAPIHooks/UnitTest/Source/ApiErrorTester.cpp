#include "pch.h"

#include <ApiError.h>
#include "CppUnitTest.h"
#include <hippomocks.h>
#include <StatusInterpreter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(ApiErrorTester)
		{
		public:
			TEST_METHOD(Constructor_GivenParameters_SetsMembers)
			{
				// Arrange
				const char* expectedMessage = "Fake Message";
				const NvAPI_Status expectedStatus = NvAPI_Status::NVAPI_GPU_NOT_POWERED;

				// Act
				auto error = std::make_unique<ApiError>(expectedMessage, expectedStatus);

				// Assert
				Assert::AreEqual(expectedMessage, error->m_message);
				Assert::AreEqual(static_cast<unsigned>(expectedStatus), static_cast<unsigned>(error->m_apiStatus));
			}

			TEST_METHOD(What_WhenCalled_ReturnsExpectedMessage)
			{
				// Arrange
				const std::string context = "Fake context on when API failed.";
				const std::string fakeMessage = "Fake reason why API failed.";
				const NvAPI_Status fakeStatus = NvAPI_Status::NVAPI_GPU_NOT_POWERED;
				MockRepository mocks;
				mocks.OnCallFunc(StatusInterpreter::GetErrorMessage).With(fakeStatus).Return(fakeMessage);
				const auto expectedMessage = context + " " + fakeMessage;
				auto error = std::make_unique<ApiError>(context.c_str(), fakeStatus);

				// Act
				auto actualMessage = error->what();

				// Assert
				Assert::AreEqual(expectedMessage, std::string(actualMessage));
			}
		};
	}
}