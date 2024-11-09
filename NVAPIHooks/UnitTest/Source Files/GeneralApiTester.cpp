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
// SOFTWARE.

#include <pch_UnitTest.h>

#include <ApiTunnel.h>
#include <ApiError.h>
#include <GeneralApi.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NVAPIHooks
{
	namespace UnitTest
	{
		TEST_CLASS(GeneralApiTester)
		{
		public:
			TEST_METHOD_CLEANUP(Teardown)
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

				// Act
				auto act = []() -> void { GeneralApi::Initialize(); };

				// Assert
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

				// Act
				auto act = []() -> void { GeneralApi::Unload(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

			TEST_METHOD(GetAllPhysicalGpus_GivenGpus_ReturnsThem)
			{
				// Arrange
				auto handle1 = (NvPhysicalGpuHandle)1;
				auto handle2 = (NvPhysicalGpuHandle)2;
				auto handle3 = (NvPhysicalGpuHandle)3;
				const auto expectedTotal = 3ul;
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles)
					.Do([&](NvPhysicalGpuHandle* gpuHandles, unsigned long* totalGpuCount) -> NvAPI_Status 
						{
							gpuHandles[0] = handle1;
							gpuHandles[1] = handle2;
							gpuHandles[2] = handle3;
							*totalGpuCount = expectedTotal;
							return NvAPI_Status::NVAPI_OK;
						});

				// Act
				auto physicalGpus = GeneralApi::GetAllPhysicalGpus();

				// Assert
				const auto actualTotal = static_cast<unsigned long>(physicalGpus.size());
				Assert::AreEqual(expectedTotal, actualTotal);
			}

			TEST_METHOD(GetAllPhysicalGpus_OnFailure_Throws)
			{
				// Arrange
				m_mocks.OnCallFunc(ApiTunnel::GetPhysicalGpuHandles).Return(NvAPI_Status::NVAPI_ERROR);

				// Act
				auto act = []() -> std::vector<IPhysicalGpu*> { return GeneralApi::GetAllPhysicalGpus(); };

				// Assert
				Assert::ExpectException<ApiError>(act);
			}

		private:
			MockRepository m_mocks;
		};
	}
}
