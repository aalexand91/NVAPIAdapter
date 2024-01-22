#include "pch.h"

#include <ApiError.h>
#include <ApiTunnel.h>
#include <CppUnitTest.h>
#include <GeneralApi.h>
#include <hippomocks.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(GeneralApiTester)
		{
		public:
			TEST_METHOD_CLEANUP(CleanUpTest)
			{
				m_mocks.reset();
			}

			TEST_METHOD(Initialize_OnSuccess_Returns)
			{
				// Arrange
				m_mocks.ExpectCallFunc(ApiTunnel::InitializeApi).Return(NvAPI_Status::NVAPI_OK);

				// Act
				GeneralApi::Initialize();

				// Assert
				m_mocks.VerifyAll();
			}

			TEST_METHOD(Initialize_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::InitializeApi).Return(NvAPI_Status::NVAPI_ERROR);
				auto act = [&] { GeneralApi::Initialize(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(Unload_OnSuccess_Returns)
			{
				// Arrange
				m_mocks.ExpectCallFunc(ApiTunnel::UnloadApi).Return(NvAPI_Status::NVAPI_OK);

				// Act
				GeneralApi::Unload();

				// Assert
				m_mocks.VerifyAll();
			}

			TEST_METHOD(Unload_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::UnloadApi).Return(NvAPI_Status::NVAPI_ERROR);
				auto act = [&] { GeneralApi::Unload(); };

				// Act & Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			MockRepository m_mocks;
		};
	}
}